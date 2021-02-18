#ifndef ALPHAPPPROTOCOL_H_
#define ALPHAPPPROTOCOL_H_

#include <qprocess.h>
#include <qvaluevector.h>
class QString;
class QTextEdit;
class QObject;

class AlphappProtocol:public QProcess
{
    Q_OBJECT
public:
    AlphappProtocol( const QString & arg0, QTextEdit * dump, const QString & inputHeader="", const QString & outputHeader="", QObject * parent = 0, const char * name = 0);
    ~AlphappProtocol() {if(isRunning()) terminate();}
public slots:
    void terminate();
    virtual void sendMessage ( int code, QValueVector<float> options, QString comment);
signals:
    virtual void messageReceived( int code, int index, QValueVector<float> options, QString comment);
private slots:
    void handleReceivedMessage();
private:
    int lastmessage;
    QTextEdit * buffer;
    QString inputH;
    QString outputH;
};

#endif
