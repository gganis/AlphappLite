/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/

void optionsDialog::init()
{
    settings.insertSearchPath( QSettings::Windows, "/ALEPH" );
    splashBox->setChecked(settings.readBoolEntry("/AlVisu/splash", TRUE));
    workdir->setText(settings.readEntry( "/AlVisu/workdir", "/home" ));
    reset->setChecked(settings.readBoolEntry("/AlVisu/onnextevent", TRUE));
    repost->setChecked(!settings.readBoolEntry("/AlVisu/onnextevent", TRUE));
    langagebox->insertItem("English");
    langagebox->setCurrentItem(settings.readNumEntry( "/AlVisu/language",  0));
    energyLength->setValue(settings.readNumEntry( "/AlVisu/energyLength",  50));
    energyRadius->setValue(settings.readNumEntry( "/AlVisu/energyRadius",  50));
    simplifiedDetector->setChecked(settings.readBoolEntry("/AlVisu/simpleDet", TRUE));
    detailledDetector->setChecked(!settings.readBoolEntry("/AlVisu/simpleDet", TRUE));
    lightingBox->setChecked(settings.readBoolEntry("/AlVisu/Light", FALSE));
    VDETcolor->setPaletteForegroundColor(QColor(settings.readNumEntry( "/AlVisu/VDETcolor",  VDETcolor->paletteForegroundColor().rgb())));
    ITCcolor->setPaletteForegroundColor(QColor(settings.readNumEntry( "/AlVisu/ITCcolor",  ITCcolor->paletteForegroundColor().rgb())));
    TPCcolor->setPaletteForegroundColor(QColor(settings.readNumEntry( "/AlVisu/TPCcolor",  TPCcolor->paletteForegroundColor().rgb())));
    ECALcolor->setPaletteForegroundColor(QColor(settings.readNumEntry( "/AlVisu/ECALcolor",  ECALcolor->paletteForegroundColor().rgb())));
    HCALcolor->setPaletteForegroundColor(QColor(settings.readNumEntry( "/AlVisu/HCALcolor",  HCALcolor->paletteForegroundColor().rgb())));
    MUONcolor->setPaletteForegroundColor(QColor(settings.readNumEntry( "/AlVisu/MUONcolor",  MUONcolor->paletteForegroundColor().rgb())));
    BACKcolor->setPaletteForegroundColor(QColor(settings.readNumEntry( "/AlVisu/BACKcolor",  BACKcolor->paletteForegroundColor().rgb())));
}

void optionsDialog::confirm()
{
    settings.writeEntry("/AlVisu/splash", splashBox->isChecked());
    settings.writeEntry("/AlVisu/workdir", workdir->text());
    settings.writeEntry("/AlVisu/onnextevent", reset->isChecked());
    settings.writeEntry("/AlVisu/language", langagebox->currentItem());
    settings.writeEntry("/AlVisu/energyLength", energyLength->value());
    settings.writeEntry("/AlVisu/energyRadius", energyRadius->value());
    settings.writeEntry("/AlVisu/simpleDet", simplifiedDetector->isChecked());
    settings.writeEntry("/AlVisu/Light", lightingBox->isChecked());
    settings.writeEntry("/AlVisu/VDETcolor",  (int)VDETcolor->paletteForegroundColor().rgb());
    settings.writeEntry("/AlVisu/ITCcolor",  (int)ITCcolor->paletteForegroundColor().rgb());
    settings.writeEntry("/AlVisu/TPCcolor",  (int)TPCcolor->paletteForegroundColor().rgb());
    settings.writeEntry("/AlVisu/ECALcolor",  (int)ECALcolor->paletteForegroundColor().rgb());
    settings.writeEntry("/AlVisu/HCALcolor", (int)HCALcolor->paletteForegroundColor().rgb());
    settings.writeEntry("/AlVisu/MUONcolor",  (int)MUONcolor->paletteForegroundColor().rgb());
    settings.writeEntry("/AlVisu/BACKcolor",  (int)BACKcolor->paletteForegroundColor().rgb());
    accept();
}

void optionsDialog::browse()
{
    QString dir = QFileDialog::getExistingDirectory(
                    workdir->text(),
                    this, "get working directory",
                    "Choose a directory", TRUE );
    if(!dir.isEmpty())
	workdir->setText(dir);
}

void optionsDialog::setBACKcolor()
{
    BACKcolor->setPaletteForegroundColor(QColorDialog::getColor(BACKcolor->paletteForegroundColor()));
}

void optionsDialog::setECALcolor()
{
    ECALcolor->setPaletteForegroundColor(QColorDialog::getColor(ECALcolor->paletteForegroundColor()));
}

void optionsDialog::setHCALcolor()
{
    HCALcolor->setPaletteForegroundColor(QColorDialog::getColor(HCALcolor->paletteForegroundColor()));
}

void optionsDialog::setITCcolor()
{
    ITCcolor->setPaletteForegroundColor(QColorDialog::getColor(ITCcolor->paletteForegroundColor()));
}

void optionsDialog::setMUONcolor()
{
    MUONcolor->setPaletteForegroundColor(QColorDialog::getColor(MUONcolor->paletteForegroundColor()));
}

void optionsDialog::setTPCcolor()
{
    TPCcolor->setPaletteForegroundColor(QColorDialog::getColor(TPCcolor->paletteForegroundColor()));
}

void optionsDialog::setVDETcolor()
{
    VDETcolor->setPaletteForegroundColor(QColorDialog::getColor(VDETcolor->paletteForegroundColor()));
}
