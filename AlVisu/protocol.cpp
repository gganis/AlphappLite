#include "protocol.h"
#include <qstring.h>
#include <qtextedit.h>
#include <qobject.h>
#include <qtimer.h>

AlphappProtocol::AlphappProtocol( const QString & arg0, QTextEdit * dump, const QString & inputHeader, const QString & outputHeader, QObject * parent, const char * name):QProcess(arg0,parent,name)
{
    lastmessage=0;
    buffer=dump;
    connect(this,SIGNAL(readyReadStdout()),this,SLOT(handleReceivedMessage()));
    inputH=inputHeader;
    outputH=outputHeader;
}

void AlphappProtocol::terminate()
{
    if(!isRunning()) return;
    //first send a terminate message internally
    QValueVector<float> dummy;
    dummy.push_back(0);
    sendMessage(999,dummy,"terminate");
    //then send a terminate message via the OS
    QTimer::singleShot( 5000, this, SLOT( tryTerminate() ) );
    // finaly send a kill signal.
    QTimer::singleShot( 10000, this, SLOT( kill() ) );
}

void AlphappProtocol::sendMessage( int code,  QValueVector<float> options, QString comment)
{
    if(!isRunning()) return;
    //serialize the header
    QString tmp(outputH);
    tmp.append("><");
    //serialize the code
    tmp.append(QString::number(code));
    tmp.append("><");
    //serialize the options
    for(QValueVector<float>::iterator i = options.begin();i<options.end();i++)
    {
	tmp.append(QString::number(*i));
	tmp.append("><");
    }
    //serialize the comment
    tmp.append(comment);
    //add the endl
    tmp.append("\n");
    //send it
    buffer->append(tmp);
    writeToStdin(tmp);    
    lastmessage = code;
}

void AlphappProtocol::handleReceivedMessage()
{
    while(canReadLineStdout())
  {
	// if one line is ready, read all lines.
	// readLineStdout() is what we need, but is seems too slow
	// and QProcess hangs...
	// We'll need to divide into lines by the hand
	QString tmpfull = readStdout();
	//QString tmp = readLineStdout();
	int fullsections = tmpfull.contains ( "\n" ) + 1;
	for(int line=0;line<fullsections;line++)
	{
	QString tmp = tmpfull.section( "\n", line, line );
	buffer->append(tmp);
	int code;
	int index;
	QValueVector<float> options;
	QString comment;
	//determine the number of sections in the string
	int sections = tmp.contains ( "><" ) + 1;
	if(sections<3) continue;
	//extract the header
	QString s = tmp.section( "><", 0, 0 );
	if (s!=inputH) continue;
	//extract the code
	code =  tmp.section( "><", 1, 1 ).toInt();
	if((code!=lastmessage)&&(code!=(lastmessage-1))&&(code!=999)) continue;
	//extract the index
	index = int(tmp.section( "><", 2, 2 ).toFloat());
	//extract options
	for(int i=3;i<(sections-1);i++)
	{
	    options.push_back(tmp.section( "><", i, i ).toFloat());
	}	
	//extract the comment
	comment = tmp.section( "><", -1, -1 );
	//emit the signal
	emit messageReceived(code,index,options,comment);
	}
    }
}
