#include"FileCreationWidget.h"

FileCreationWidget::FileCreationWidget(MainWindow *_pmw, Modello* _pm, QWidget *parent) : QWidget(parent), pmw(_pmw), pm(_pm)
{
  mainVLayout = new QVBoxLayout;
  setLayout(mainVLayout);
  
  externalFrame = new QFrame;
  externalFrame->setFrameShape(QFrame::StyledPanel);
  externalFrame->setFrameShadow(QFrame::Raised);
  //externalFrame->setLineWidth(3);  // TODO cancellare, non serve
  mainVLayout->addWidget(externalFrame);
  
  internalGLayout = new QGridLayout(externalFrame);
  
  fileNameLineEdit = new QLineEdit("untitled");
  file_name = "untitled";
  fileNameLineEdit->setPlaceholderText("Insert file name:");
  folderLabel = new QLabel("");
  folderLabel->setFrameShape(QFrame::StyledPanel);
  folderLabel->setFrameShadow(QFrame::Raised);
  browseButton = new QPushButton("Browse...");
  browseButton->setFixedWidth(80);
  
  internalGLayout->addWidget(fileNameLineEdit, 0, 0, 1, 2);
  internalGLayout->addWidget(folderLabel, 1, 0, 1, 1);
  internalGLayout->addWidget(browseButton, 1, 1, 1, 1);
  
  createHLayout = new QHBoxLayout;
  mainVLayout->addLayout(createHLayout);
  createHLayout->addStretch();
  createButton = new QPushButton("Create");
  createButton->setIcon(QIcon::fromTheme("emblem-default"));
  createButton->setFixedWidth(80);
  createButton->setEnabled(false);
  createHLayout->addWidget(createButton);
  
  // connetto browseButton con una funzione che mi apre un file dialog
  connect(browseButton, &QPushButton::clicked,
          this, &FileCreationWidget::on_browseButton);
  // connetto il lineEdit quando viene editato con una fun che blocca il createButton
  connect(fileNameLineEdit, &QLineEdit::textEdited,
          this, &FileCreationWidget::on_fileNameEdited);
  // connetto il createButton alla funzione del modello che crea effettivamente il file
  connect(createButton, &QPushButton::clicked,
          this, &FileCreationWidget::on_createButton);
}

// ------------------------------------------------------------------------------------- //

void FileCreationWidget::on_browseButton() {
  // apri un file dialog che faccia scegliere il folder_path
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::Directory);
  dialog.setViewMode(QFileDialog::Detail);  // se vuoi i dettagli
  QStringList folderList;
  if (dialog.exec()) folderList = dialog.selectedFiles();
  // salvalo
  folder_path = folderList[0].toStdString();
  // scrivilo in folderLabel
  folderLabel->setText(folderList[0]);
  // sblocca il pulsante createButton
  createButton->setEnabled(true);
}


void FileCreationWidget::on_fileNameEdited(const QString& text) {
  // ogni volta che il lineEdit viene modificato da utente:
  // viene salvato in file_name
  file_name = text.toStdString();
  // se non c'è testo ("") viene bloccato il pulsante create
  if (text == "") { createButton->setEnabled(false); }
  // altrimenti viene sbloccato / tenuto sbloccato
  else { if (folder_path != "") createButton->setEnabled(true); }
}


void FileCreationWidget::on_createButton() {
  // TODO controllare se il file con quel nome esiste già
    // TODO avvisarlo che il file verrà sovrascitto oppure dirgli di cambiare nome
  pm->apri_nuovo_file(folder_path, file_name);
  // passo all'SdcWidget
  pmw->initSdcWidget();
}
