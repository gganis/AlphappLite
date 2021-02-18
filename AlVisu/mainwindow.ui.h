/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/

#include <iostream>
#define min(a,b) (((a)<(b))?(a):(b))

void MainWindow::fileOpen()
{
    QSettings settings;
    settings.insertSearchPath( QSettings::Windows, "/ALEPH" );
    QString defaultPath = settings.readEntry("/AlVisu/workdir",QString::null);
    QString s = QFileDialog::getOpenFileName( defaultPath,
					      "",this,
					      "open file dialog"
					      "Choose the ALPHA++ code" );
    if(alphappProcess) delete alphappProcess;
    alphappProcess = new AlphappProtocol(s,theOutput->TextEdit1,
					 "ALPHA++","AlVisu",this);
    alphappProcess->addArgument("-l0");
    connect(alphappProcess,SIGNAL(processExited()),this,SLOT(alphappExited()));
    connect(alphappProcess,SIGNAL(messageReceived(int,int,QValueVector<float>,QString)),this,SLOT(handleMessageReceived(int,int,QValueVector<float>,QString)));
    connect(fileCloseProcessAction,SIGNAL(activated()),alphappProcess,SLOT(terminate()));
    if(!alphappProcess->start())
    {
	QMessageBox::warning( this, "AlVisu",
		"Could not connect to the ALPHA++ process.\n"
		"No event can be processed."
		"Please Check the application name .\n\n",
		QMessageBox::Ok,0,0 ); 
    }
    else {
	fileLaunchAction->setEnabled(FALSE);
    }
}

void MainWindow::filePrint()
{
    QPrinter* printer = new QPrinter;
    if ( printer->setup( this ) ) {
        QPainter paint( printer );
        QImage image = scene->grabFrameBuffer();
        paint.drawImage( image.width(), image.height(), image);
    }
    delete printer;
}

void MainWindow::fileExit()
{
    close();
}

void MainWindow::helpAbout()
{
    AboutBox *about= new AboutBox;
    about->exec();
}

void MainWindow::fileSavePic()
{
    QSettings settings;
    settings.insertSearchPath( QSettings::Windows, "/ALEPH" );
    QString defaultPath = settings.readEntry("/AlVisu/workdir",QString::null);
    QStringList formats = QImage::outputFormatList();
    QString formatstring;
    formatstring += "Images (*.";
    for(QStringList::iterator current = formats.begin() ;current != formats.end(); current++)
    {
	formatstring += *current;
	formatstring += " *.";
    }
    formatstring += ")";
    QString savefilename = QFileDialog::getSaveFileName(defaultPath, formatstring,
							this, "save file dialog",
							"Choose a file");
    if ( !savefilename.isEmpty() )
    {
	QString format;
	for(QStringList::iterator current = formats.begin() ;current != formats.end(); current++)
	{
	    if(savefilename.contains(*current,FALSE))
	    {
		format = *current;
		continue;
	    }
	}
	bool result = (scene->grabFrameBuffer()).save( savefilename, format );
	if ( !result )
	    QMessageBox::warning( this, "Save failed", "Error saving file" );
    }
}

void MainWindow::fileSaveTxt()
{
    QSettings settings;
    settings.insertSearchPath( QSettings::Windows, "/ALEPH" );
    QString defaultPath = settings.readEntry("/AlVisu/workdir",QString::null);
    QString savefilename = QFileDialog::getSaveFileName(defaultPath, QString::null,
							this, "save file dialog",
							"Choose a file");
    if ( !savefilename.isEmpty() )
    {
	 QFile f(savefilename);
	 if ( !f.open( IO_WriteOnly ))
	 {
	     QMessageBox::warning( this, "Save failed", "Error saving file" );
	     return;
	 }
	 QTextStream s( &f );    // we will serialize the data into file f
	 s << theOutput->TextEdit1->text();
	 f.close();
    }   
}

void MainWindow::alphappExited()
{
    // There should be some tests her to check if the process has exited normaly...
    fileLaunchAction->setEnabled(TRUE);
    status = 0;
    // disconnect the process
    disconnect(alphappProcess,SIGNAL(processExited()),this,SLOT(alphappExited()));
    disconnect(alphappProcess,SIGNAL(messageReceived(int,int,QValueVector<float>,QString)),this,SLOT(handleMessageReceived(int,int,QValueVector<float>,QString)));
    disconnect(fileCloseProcessAction,SIGNAL(activated()),alphappProcess,SLOT(terminate()));
    // delete the process
    delete alphappProcess;
    alphappProcess = NULL;
    // disable the tab-widget and all the pages independantly...
    display_options->setEnabled(FALSE);
    for(int tab=0;tab<(display_options->count());tab++)
	 display_options->setTabEnabled (display_options->page(tab),FALSE);
    display_options->setTabEnabled (display_options->page(2),TRUE);
    display_options->setCurrentPage(0);
    // clear the member lists
    tracklist.clear();
    leptonlist.clear();
    jetlist.clear();
    usr_functions.clear();
    userlist.clear();
    lastJetRequest.clear();
    lastUsrRequest.clear();
    // reset the scene
    prepareForNextEvent();
    // clear the user tab contents
    user_AvailableComboBox->clear();
    fillUserOptionTable();
}

void MainWindow::init()
{
    theOutput = new outputDialog();
    connect(theOutput,SIGNAL(hidden()),displayOutputAction,SLOT(toggle()));
    theVpc = new vpc();
    connect(theVpc,SIGNAL(hidden()),displayViewportControlsAction,SLOT(toggle()));
    connect(theVpc,SIGNAL(xPosChanged(int)),scene,SLOT(SetPos_x(int)));
    connect(theVpc,SIGNAL(yPosChanged(int)),scene,SLOT(SetPos_y(int)));
    connect(theVpc,SIGNAL(zPosChanged(int)),scene,SLOT(SetPos_z(int)));
    connect(theVpc,SIGNAL(xViewChanged(int)),scene,SLOT(SetViewAngle_x(int)));
    connect(theVpc,SIGNAL(yViewChanged(int)),scene,SLOT(SetViewAngle_y(int)));
    connect(theVpc,SIGNAL(zViewChanged(int)),scene,SLOT(SetViewAngle_z(int)));
    connect(theVpc,SIGNAL(zoomChanged(int)),scene,SLOT(SetScale(int)));
    connect(scene,SIGNAL(glViewChanged(int, int, int, int, int, int, int)),theVpc,SLOT(ressetall( int, int, int, int, int, int, int)));
    alphappProcess = NULL;
    tracklist.clear();
    leptonlist.clear();
    jetlist.clear();
    usr_functions.clear();
    userlist.clear();
    lastJetRequest.clear();
    lastUsrRequest.clear();
    // disable the tab-widget and all the pages independantly...
    display_options->setEnabled(FALSE);
    for(int tab=0;tab<(display_options->count());tab++)
	 display_options->setTabEnabled (display_options->page(tab),FALSE);
    display_options->setTabEnabled (display_options->page(2),TRUE);
    display_options->setCurrentPage(0);
    status = 0;  // aux code not running.
    QSettings settings;
    settings.insertSearchPath( QSettings::Windows, "/ALEPH" );
    scene->configure(QColor(settings.readNumEntry( "/AlVisu/VDETcolor",-65536)),
		     QColor(settings.readNumEntry( "/AlVisu/ITCcolor",  -256)),
		     QColor(settings.readNumEntry( "/AlVisu/TPCcolor",  -1)),
		     QColor(settings.readNumEntry( "/AlVisu/ECALcolor",  -16733696)),
		     QColor(settings.readNumEntry( "/AlVisu/HCALcolor",  -16776961)),
		     QColor(settings.readNumEntry( "/AlVisu/MUONcolor",  -1497089)),
		     QColor(settings.readNumEntry( "/AlVisu/BACKcolor",  -7517673)),
		     settings.readNumEntry( "/AlVisu/energyRadius",  50),
		     settings.readNumEntry( "/AlVisu/energyLength",  50),
		     settings.readBoolEntry( "/AlVisu/Light",  TRUE));
}

void MainWindow::displayVpc(bool state)
{
    if(state) 
	theVpc->show();
    else
	theVpc->hide();
}

void MainWindow::displayOutput(bool state)
{
    if(state)
	theOutput->show();
    else
	theOutput->hide();
}

void MainWindow::setNTcolor()
{
    nColor->setPaletteForegroundColor(QColorDialog::getColor(nColor->paletteForegroundColor()));
}

void MainWindow::setMTcolor()
{
    mColor->setPaletteForegroundColor(QColorDialog::getColor(mColor->paletteForegroundColor()));
}

void MainWindow::setTMcolor()
{
    mColorTau->setPaletteForegroundColor(QColorDialog::getColor(mColorTau->paletteForegroundColor()));
}

void MainWindow::setNEcolor()
{
    mColorEl->setPaletteForegroundColor(QColorDialog::getColor(mColorEl->paletteForegroundColor()));
}

void MainWindow::setNMcolor()
{
    mColorMu->setPaletteForegroundColor(QColorDialog::getColor(mColorMu->paletteForegroundColor()));
}

void MainWindow::setPEcolor()
{
    pColorEl->setPaletteForegroundColor(QColorDialog::getColor(pColorEl->paletteForegroundColor()));
}

void MainWindow::setPMcolor()
{
    pColorMu->setPaletteForegroundColor(QColorDialog::getColor(pColorMu->paletteForegroundColor()));
}

void MainWindow::setTPcolor()
{
    pColorTau->setPaletteForegroundColor(QColorDialog::getColor(pColorTau->paletteForegroundColor()));
}

void MainWindow::setUcolor()
{
    user_color->setPaletteForegroundColor(QColorDialog::getColor(user_color->paletteForegroundColor()));
}

void MainWindow::setPTcolor()
{
    pColor->setPaletteForegroundColor(QColorDialog::getColor(pColor->paletteForegroundColor()));
}

void MainWindow::destroy()
{
    delete theOutput;
    delete theVpc;
    if(alphappProcess)
	delete alphappProcess;
}

void MainWindow::handleMessageReceived( int code, int index, QValueVector<float> options, QString comment )
{
    switch(code)
    {
    case -1:
	{
	    // initialisation of functions
	    if(status) return; // must not be running
	    bool newfunct = (options[0]>0);
	    switch(newfunct)
	    {
	    case TRUE:
		{	
		    // a new function
		    if(options[1]>=500)
		    {
			// a user function
			// create a new userFunction and store it
			userFunction tmp;
			tmp.setName(comment);
			tmp.setCode(int(options[1]));
			usr_functions.push_back(tmp);
			// enable user tab
			display_options->setTabEnabled(display_options->page(6),TRUE);
			// add an entry in the combobox
			user_AvailableComboBox->insertItem(comment);
			// add a backup area for options (used to repost)
			lastUsrRequest.push_back(QValueVector<float>());
			break;
		    }
		    // a standard function (code < 500)
		    // we just have to enable the corresponding tab(s)
		    switch(int(options[1]))
		    {
		    case 100:
			{
			    display_options->setTabEnabled(display_options->page(0),TRUE);
			    display_options->setTabEnabled(display_options->page(1),TRUE);
			    break;
			}
		    case 200:
			{
			    display_options->setTabEnabled (display_options->page(3),TRUE);
			    break;
			}
		    case 300:
			{
			    display_options->setTabEnabled (display_options->page(4),TRUE);
			    break;
			}
		    case 400:
			{
			    display_options->setTabEnabled (display_options->page(5),TRUE);
			    break;
			}
		    }
		    break;
		}
	    case FALSE:
		{
		    // an option for an existing function
		    // for a default function, do nothing
		    if(options[1]<500) return;
		    // for a user function, add the option to the class
		    // first locate the function in the collection
		    userFunction* the_function = NULL;
		    for(QValueVector< userFunction >::iterator fct=usr_functions.begin(); fct<usr_functions.end(); fct++)
			if(fct->getCode()==options[1])
			    the_function = &(*fct);
		    // then add the option
		    if(the_function)
			the_function->addOption(comment,options[2]);
		    break;
		}
	    }
	    break;
	}
    case 0:
	{
	    // server ready...
	    userlist.resize(user_AvailableComboBox->count());
	    scene->setListNumber(user_AvailableComboBox->count());
	    status = 1; // running
	    display_options->setEnabled(TRUE);
	    break;
	}
    case 100:
	{
	    // next event
	    switch(index)
	    {
	    case 1:
		{
		    prepareForNextEvent();
		    event->setText(QString::number(options[0]));
		    break;
		}
	    case 2:
		{
		    run->setText(QString::number(options[0]));
		    break;
		}
	    case 3:
		{
		    if (options.size()!=6) break;
		    QDate date_tmp((int)options[0],(int)options[1],(int)options[2]);
		    QTime time_tmp((int)options[3],(int)options[4],(int)options[5]);
		    DateTimeEdit1->setDateTime(QDateTime(date_tmp,time_tmp));
		    break;
		}
	    case 4:
		{
		    classword->setText(QString::number((long unsigned int)options[0],2));
		    break;
		}
	    case 5:
		{
		    if (options.size()!=2) break;
		    msum->setText((QString::number(options[0]))+" GeV/c²");
		    esum->setText((QString::number(options[1]))+" GeV");
		    break;
		}
	    case 6:
		{
		    if (options.size()!=9) break;
		    acoplanarity->setText((QString::number(options[0]))+" °");
		    acolinearity->setText((QString::number(options[1]))+" °");
		    thrust->setText(QString::number(options[2]));
		    thrustaxis->setText("( "+(QString::number(options[3]))+", "+
					(QString::number(options[4]))+", "+
					(QString::number(options[5]))+" )");
		    aplanarity->setText(QString::number(options[6]));
		    planarity->setText(QString::number(options[7]));
		    sphericity->setText(QString::number(options[8]));
		    break;
		}
	default:
		{
		    // nothing to do
		}
	    }
	    break;
	}
    case 200:
	{
	    // redraw tracks
	    // if index == 0 call scene method to draw the objects
	    if(options.size()!=5)
	    {
		scene->makeTracks(0,pColor->paletteForegroundColor(),mColor->paletteForegroundColor(),nColor->paletteForegroundColor());
		break;
	    }
	    float *tmp = new float[5];
	    for (int i=0;i<5;i++) tmp[i] = options[i];
	    tracklist.push_back(tmp);
	    if (!index)
	    {
		scene->makeTracks(&tracklist,pColor->paletteForegroundColor(),mColor->paletteForegroundColor(),nColor->paletteForegroundColor());
		for(QValueVector<float*>::iterator track=tracklist.begin();track< tracklist.end(); track++)
		    delete[] *track;
		tracklist.clear();
	    }
	    break;
	}
    case 300:
	{
	    // redraw leptons
	    // if index == 0 call scene method to draw the objects
	    if (options.size()!=6)
	    {
		// if no lepton is requested, don't send any message, just clean the scene
		scene->makeLeptons(0,
				   pColorEl->paletteForegroundColor(),mColorEl->paletteForegroundColor(),
				   pColorMu->paletteForegroundColor(),mColorMu->paletteForegroundColor(),
				   pColorTau->paletteForegroundColor(),mColorTau->paletteForegroundColor());
		break;
	    }
	    float *tmp = new float[6];
	    for (int i=0;i<6;i++) tmp[i] = options[i];
	    leptonlist.push_back(tmp);
	    if (!index)
	    {
		scene->makeLeptons(&leptonlist,
				   pColorEl->paletteForegroundColor(),mColorEl->paletteForegroundColor(),
				   pColorMu->paletteForegroundColor(),mColorMu->paletteForegroundColor(),
				   pColorTau->paletteForegroundColor(),mColorTau->paletteForegroundColor());
		for(QValueVector<float*>::iterator track=leptonlist.begin();track< leptonlist.end(); track++)
		    delete[] *track;
		leptonlist.clear();
	    }
	    break;
	}
    case 400:
	{
	    // redraw the jets
	    // if index == 0 call scene method to draw the objects
	    if (options.size()!=4) break;
	    float *tmp = new float[4];
	    for (int i=0;i<4;i++) tmp[i] = options[i];
	    jetlist.push_back(tmp);
	    if (!index)
	    {
		QColor jetsColors[5];
		jetsColors[0] = jet_color1->paletteForegroundColor();
		jetsColors[1] = jet_color2->paletteForegroundColor();
		jetsColors[2] = jet_color3->paletteForegroundColor();
		jetsColors[3] = jet_color4->paletteForegroundColor();
		jetsColors[4] = jet_color5->paletteForegroundColor();
		scene->makeJets(&jetlist,jetsColors,5);
		for(QValueVector<float*>::iterator jet=jetlist.begin();jet< jetlist.end(); jet++)
		    delete[] *jet;
		jetlist.clear();
	    }
	    break;
	}
    case 999:
	{
	    // all events proceeded
	    display_options->setCurrentPage(0);
	    display_options->setEnabled(FALSE);
	    status = 0;
	    QTimer::singleShot( 5000, alphappProcess, SLOT(terminate()));
	    prepareForNextEvent();
	    // disable the tab-widget and all the pages independantly...
	    display_options->setEnabled(FALSE);
	    for(int tab=0;tab<(display_options->count());tab++)
		display_options->setTabEnabled (display_options->page(tab),FALSE);
	    display_options->setTabEnabled (display_options->page(2),TRUE);
	    display_options->setCurrentPage(0);
	    break;
	}
    default:
	{ 
	    // the code received is none of the default ones
	    // check that this is a user code
	    bool existing = false;
	    int position = 0;
	    for(QValueVector< userFunction >::iterator func = usr_functions.begin(); func < usr_functions.end(); func++)
	    {
		if((func->getCode())==code)
		{
		    existing = true;
		    break;
	             }
		position++;
	    }
	    if(existing)
	    {
		// handle the message
		// check the size
		uint needed = 0;
		if(options[0]==1)
		    needed = 5;
		else if(options[0]==2)
		    needed = 6;
		else if(options[0]==3)
		    needed = 7;
		else if(options[0]==4)
		    needed = 5;
		if(options.size()!=needed) break;
		// store the options in a float array
		float *tmp = new float[needed];
		for (uint i=0;i<needed;i++) tmp[i] = options[i];
		userlist[position].push_back(tmp);
		if (!index)
		{
		    QColor color = user_color->paletteForegroundColor();
		    scene->makeUserObjects(&userlist[position],position,&color,1);
		    for(QValueVector<float*>::iterator obj=userlist[position].begin();obj< userlist[position].end(); obj++)
			delete[] *obj;
		    userlist[position].clear();
		}
	    }
	    else
	    {
		// else, error:
		std::cout << "=====================" << std::endl;
		std::cout << "unknown message received" << std::endl;
		std::cout << "code: " << code << std::endl;
		std::cout << "index: " << index << std::endl;
		std::cout << "size : " << options.size() << std::endl;
		std::cout << "comment: " << comment << std::endl;
		std::cout << "=====================" << std::endl;
	    }
	    break;
	}
    }
}

void MainWindow::requestNextEvent()
{
    QValueVector<float> options;
    options.push_back(event_preselCheckBox->isChecked());
    alphappProcess->sendMessage (100,options,"Next event, please...");
}

void MainWindow::prepareForNextEvent()
{
    QSettings settings;
    settings.insertSearchPath( QSettings::Windows, "/ALEPH" );
    bool reset = settings.readBoolEntry("/AlVisu/onnextevent", TRUE);
    // reset the scene
    scene->reset();
    // reset the GUI
    // first the 2 first tabs...
    event->setText("0");
    run->setText("0");
    QDate date_tmp(1979,5,4);
    QTime time_tmp(0,30,0);
    DateTimeEdit1->setDateTime(QDateTime(date_tmp,time_tmp));
    classword->setText("00000000000000000000");
    msum->setText("0 GeV/c²");
    esum->setText("0 GeV");
    acoplanarity->setText("180 °");
    acolinearity->setText("180 °");
    thrust->setText("0");
    thrustaxis->setText("( 0, 0, 0 )");
    aplanarity->setText("0");
    planarity->setText("0");
    sphericity->setText("0");
    // because of the scene reset we MUST setListNumber before using scene.
    if(status==1) scene->setListNumber(user_AvailableComboBox->count());
    // then the tracks and leptons (can be reposted  or reseted)
    if(reset||(!status))
    {
	// reset the interface...
	track_none->setChecked(TRUE);
	showel->setChecked(FALSE);
	showmu->setChecked(FALSE);
	showtau->setChecked(FALSE);
    }
    else
    {
	// set the status bit to 2... => repost mode
	status = 2;
	// the interface is losked and will be unlocked when everything will be reposted.
	display_options->setEnabled(FALSE);
	// connect the repost() method to the signal messageReceived
	user_AvailableComboBox->setCurrentItem(0);
	connect(alphappProcess,SIGNAL(messageReceived(int,int,QValueVector<float>,QString)),this,SLOT(repost(int,int,QValueVector<float>,QString)));
    }
}

void MainWindow::redrawDetector()
{
    int detectorDisplayStatus = 0;
    detectorDisplayStatus += (( vdetCheckBox->isChecked() )<<0);
    detectorDisplayStatus += (( itcCheckBox->isChecked() )<<1);
    detectorDisplayStatus += (( tpcCheckBox->isChecked() )<<2);
    detectorDisplayStatus += (( ecalCheckBox->isChecked() )<<3);
    detectorDisplayStatus += (( hcalCheckBox->isChecked() )<<4);
    detectorDisplayStatus += (( muonCheckBox->isChecked() )<<5);
    detectorDisplayStatus += (( ecalECCheckBox->isChecked() )<<6);
    detectorDisplayStatus += (( hcalECCheckBox->isChecked() )<<7);
    detectorDisplayStatus += (( muECCheckBox->isChecked() )<<8);
    scene->makeDetector(detectorDisplayStatus);
}

void MainWindow::redrawTracks()
{
    QValueVector<float> options;
    if(track_none->isChecked())
    {
	// if no track is requested, don't send the message
	scene->makeTracks(0,pColor->paletteForegroundColor(),mColor->paletteForegroundColor(),nColor->paletteForegroundColor());
	// but if we are is repost mode, explicitely call repost.
	if(status==2) repost(200,0,options,"tracks");
	return;
    }
    // build and send a message.
    options.push_back( (track_tracks->isChecked())+((track_eflows->isChecked())*2) );
    options.push_back( (track_energy->value())/100. );
    options.push_back( (track_costheta->value())/100. );
    options.push_back( track_sanityCheckBox->isChecked() );
    alphappProcess->sendMessage (200,options,"tracks");
}

void MainWindow::redrawLeptons()
{
    QValueVector<float> options;
    int value = (showel->isChecked())+2*(showmu->isChecked())+4*(showtau->isChecked());
    if(!value)
    {
	// if no lepton is requested, don't send any message, just clean the scene
	scene->makeLeptons(0,
			   pColorEl->paletteForegroundColor(),mColorEl->paletteForegroundColor(),
			   pColorMu->paletteForegroundColor(),mColorMu->paletteForegroundColor(),
			   pColorTau->paletteForegroundColor(),mColorTau->paletteForegroundColor());
	// but in repost mode we must explicitely call repost
	if(status==2) repost(300,0,options,"leptons");
	return;
    }
    // build and send a message.
    options.push_back( value );
    alphappProcess->sendMessage (300,options,"leptons");
}

void MainWindow::redrawJets()
{
    QValueVector<float> options;
    options.push_back(jet_Durham->isChecked());
    options.push_back(jet_escheme->isChecked());
    options.push_back(jet_ycut->text().toFloat());
    float value = jet_ecustom->isChecked() ? jet_ecustom_edit->text().toFloat() : (-(jet_qelep->isChecked()));
    options.push_back(value);
    alphappProcess->sendMessage (400,options,"jets");
    // save the options, so that it can be used for a repost
    lastJetRequest = options;
}

void MainWindow::removeJets()
{
    scene->makeJets(NULL,NULL,0);
    lastJetRequest.clear();
}

void MainWindow::setJcolor1()
{
    jet_color1->setPaletteForegroundColor(QColorDialog::getColor(jet_color1->paletteForegroundColor()));
}

void MainWindow::setJcolor2()
{
    jet_color2->setPaletteForegroundColor(QColorDialog::getColor(jet_color2->paletteForegroundColor()));
}

void MainWindow::setJcolor3()
{
    jet_color3->setPaletteForegroundColor(QColorDialog::getColor(jet_color3->paletteForegroundColor()));
}

void MainWindow::setJcolor4()
{
    jet_color4->setPaletteForegroundColor(QColorDialog::getColor(jet_color4->paletteForegroundColor()));
}

void MainWindow::setJcolor5()
{
    jet_color5->setPaletteForegroundColor(QColorDialog::getColor(jet_color5->paletteForegroundColor()));
}

void MainWindow::displayOptions()
{
    optionsDialog *mydialog = new optionsDialog(this);
    mydialog->exec();
    delete mydialog;
    QSettings settings;
    settings.insertSearchPath( QSettings::Windows, "/ALEPH" );
    scene->configure(QColor(settings.readNumEntry( "/AlVisu/VDETcolor",-65536)),
		     QColor(settings.readNumEntry( "/AlVisu/ITCcolor",  -256)),
		     QColor(settings.readNumEntry( "/AlVisu/TPCcolor",  -1)),
		     QColor(settings.readNumEntry( "/AlVisu/ECALcolor",  -16733696)),
		     QColor(settings.readNumEntry( "/AlVisu/HCALcolor",  -16776961)),
		     QColor(settings.readNumEntry( "/AlVisu/MUONcolor",  -1497089)),
		     QColor(settings.readNumEntry( "/AlVisu/BACKcolor",  -7434539)),
		     settings.readNumEntry( "/AlVisu/energyRadius",  500),
		     settings.readNumEntry( "/AlVisu/energyLength",  40),
		     settings.readBoolEntry( "/AlVisu/Light",  TRUE),
		     true);
}

void MainWindow::displayCustomMessage()
{
    bool ok = FALSE;
    QString text = QInputDialog::getText ( "Custom message to ALPHA++", "Message to send to ALPHA++: ", QLineEdit::Normal, QString::null, &ok, this );
    if (( ok && !text.isEmpty() )&&(alphappProcess!=NULL))
	alphappProcess->writeToStdin(text);
}

void MainWindow::fillUserOptionTable()
{
    // first clear the table
    for(int i=0; i<(user_parametersTable->numRows());i++)
    {
	user_parametersTable->setText(i, 0, "");
	user_parametersTable->setText(i, 1, "");
    }
    // look at the combobox to see which option list is needed
    QString currentFunction = user_AvailableComboBox->currentText();
    // find the corresponding option list
    QValueVector< QPair<QString, float> > options;
    for(QValueVector< userFunction >::iterator func = usr_functions.begin(); func < usr_functions.end(); func++)
	if((func->getName())==currentFunction) 
	{
	    options = func->getOptions();
	    break;
	}
    // fill the table
    user_parametersTable->setNumRows(options.size());
    int cnt = 0;
    for(QValueVector< QPair<QString, float> >::iterator opt = options.begin(); opt< options.end(); opt++)
    {
	user_parametersTable->setText( cnt, 0, opt->first);
	user_parametersTable->setText( cnt++, 1, QString::number(opt->second));
    }
    user_parametersTable->setColumnReadOnly(0, TRUE);
}

void MainWindow::redrawUser()
{
    // ask for the user function
    // first retreive the function info
    userFunction theFunction;
    QString currentFunction = user_AvailableComboBox->currentText();
    for(QValueVector< userFunction >::iterator func = usr_functions.begin(); func < usr_functions.end(); func++)
	if((func->getName())==currentFunction) 
	{
	    theFunction = *func;
	    break;
	}
    // retreive the options
    QValueVector<float> options;
    for(int i=0; i<(user_parametersTable->numRows());i++)
	options.push_back(user_parametersTable->text(i,1). toFloat());
    // send the command
    alphappProcess->sendMessage (theFunction.getCode(),options,theFunction.getName());
    // save the options to be able to repost them
    lastUsrRequest[user_AvailableComboBox->currentItem()] = options;
}

void MainWindow::removeUser()
{
    // remove objects related to the current user function
    // first retreive the function info
    userFunction theFunction;
    QString currentFunction = user_AvailableComboBox->currentText();
    int position = 0;
    for(QValueVector< userFunction >::iterator func = usr_functions.begin(); func < usr_functions.end(); func++)
    {
	if((func->getName())==currentFunction) 
	{	
	    theFunction = *func;
	    break;
	}
	position++;
    }
    // remove the corresponding objects from the scene
    scene->makeUserObjects(NULL,position,NULL,0);
    // clear the last request
    lastUsrRequest[user_AvailableComboBox->currentItem()].clear();
}

void MainWindow::repost( int code, int index, QValueVector<float> options, QString comment )
{
    bool done = false;
    if((code==100)&&(index==6)) {redrawTracks(); return; }
    if((code==200)&&(index==0)) {redrawLeptons(); return; }
    if((code==300)&&(index==0)) 
    {
	if (lastJetRequest.size()) {alphappProcess->sendMessage (400,lastJetRequest,"jets"); return; }
	else code=400;
    }
    if((code>=400)&&(index==0))
    {
	int j=0;
	for(QValueVector<QValueVector<float> >::iterator i = lastUsrRequest.begin(); i<lastUsrRequest.end(); i++)
	{
	    // look for the first non-zero options backup
	    if(i->size())
	    {
		// check that it has a not been reposted yet
		if(j<(user_AvailableComboBox->currentItem())) {j++; continue; }
		// if found, retreive the code and send the message.
		user_AvailableComboBox->setCurrentItem(min(j+1,(user_AvailableComboBox->count())-1));
		QString currentFunction = user_AvailableComboBox->text(j);
		userFunction theFunction;
		for(QValueVector< userFunction >::iterator func = usr_functions.begin(); func < usr_functions.end(); func++)
		{
		    if((func->getName())==currentFunction) 
		    {
			theFunction = *func;
			break;
		    }
		}
		// send the command
		alphappProcess->sendMessage(theFunction.getCode(),*i,theFunction.getName());
		if((j+1)==(user_AvailableComboBox->count())) break; else return;
	    }
	    j++;
	}
	done = true;
    }
    // if done, return to running mode.
    if (done)
    {
	// disconnect the function
	disconnect(alphappProcess,SIGNAL(messageReceived(int,int,QValueVector<float>,QString)),this,SLOT(repost(int,int,QValueVector<float>,QString)));
	// unlock the interface
	display_options->setEnabled(TRUE);
	// set status to running
	status = 1;
    }
}
