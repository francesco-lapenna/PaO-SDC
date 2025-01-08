#include"StartWidget.h"

#include<QFileDialog>

StartWidget::StartWidget(MainWindow *_pmw, Modello *_pm, QWidget *parent) : QWidget(parent), pmw(_pmw), pm(_pm)
{
  mainLayout = new QVBoxLayout;   // inizializzo il layout principale
  setLayout(mainLayout);          // e lo imposto come principale
  
  buttonsLayout = new QHBoxLayout;  // inizializzo il H layout
  mainLayout->addLayout(buttonsLayout);  // lo metto nel main
  
  // inizializzo gli elementi
  openButton = new QPushButton("Open file...");
  openButton->setFixedSize(150, 70);
  createButton = new QPushButton("Create new file...");
  createButton->setFixedSize(150, 70);
  
  // connetto gli elementi
  connect(openButton, &QPushButton::clicked,
          this, &StartWidget::on_openButton);
  connect(createButton, &QPushButton::clicked,
          this, &StartWidget::on_createButton);
  // TODO settare la dimensione dei QPushButton per farli quadrati
  
  // inserisco gli elementi nel layout
  buttonsLayout->addStretch();
  buttonsLayout->addWidget(openButton);
  buttonsLayout->addWidget(createButton);
  buttonsLayout->addStretch();
  
  mainLayout->addStretch();
  
  fileNotValidLabel = new QLabel("");  // il label lo setto vuoto per il momento
  mainLayout->addWidget(fileNotValidLabel);
  
}

//StartWidget::~StartWidget() {}

void StartWidget::on_openButton() {
  QString filePath = QFileDialog::getOpenFileName(nullptr, "open file", "", "csv file (*.csv)");

  if (!filePath.isEmpty()) {
    bool file_valido = pm->apri_file_esistente(filePath.toStdString());
    if (file_valido) {
      // l'apertura è andata a buon fine, torno alla mainwindow
      pmw->initSdcWidget();
    }
    else {
      fileNotValidLabel->setText("File not valid. Select a different file.");
    }
  }
}

void StartWidget::on_createButton() {
  // disattivo il pulsante createButton
  createButton->setEnabled(false);
  // inizializzo fcw
  fcw = new FileCreationWidget(pmw, pm);
  // lo aggiunge sotto i bottoni e il label
  mainLayout->addWidget(fcw);
}

























/* CODICE PRECEDENTE:
#include<QFileDialog>
#include<QDebug>
#include<QVBoxLayout>
#include<QGridLayout>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>

void StartWindow::inizializza() {
  // inizializza gli elementi di base della StartWindow
  mainLayout = new QVBoxLayout;
  setLayout(mainLayout);
  
  QHBoxLayout *apriCreaLayout = new QHBoxLayout;
  mainLayout->addLayout(apriCreaLayout);
  
  QPushButton *apriButton = new QPushButton("Apri SDC...");
  QPushButton *creaButton = new QPushButton("Crea SDC...");
  
  apriCreaLayout->addWidget(apriButton);
  apriCreaLayout->addWidget(creaButton);
  
  connect(apriButton, &QPushButton::clicked,
          this, &StartWindow::apri_file);
  connect(creaButton, &QPushButton::clicked,
          this, &StartWindow::crea_file);
}

QString StartWindow::scegli_folder_dialog() {
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::Directory);
  dialog.setViewMode(QFileDialog::Detail);  // se vuoi i dettagli
  QStringList folderPath;
  if (dialog.exec())
    { folderPath = dialog.selectedFiles(); }
  //return folderPath;
  return QString("");  // TODO temporaneo cancellare
}

void StartWindow::apri_file() {
  QString filePath = QFileDialog::getOpenFileName(nullptr, "apri file", "", "file csv (*.csv)");

  if (!filePath.isEmpty()) {
    pm->apri_file_esistente(filePath.toStdString());
    // TODO passa alla MainWindow
    //this->hide();
    //MainWindow mw(pm);
    //mw.setModal(true);
    //mw.exec();
  }
}

void StartWindow::crea_file() {
  //QFrame *creaFileFrame = new QFrame;
  QGridLayout *creazioneFileLayout = new QGridLayout;
  mainLayout->addLayout(creazioneFileLayout);
  
  QLineEdit *nomeFileLineEdit = new QLineEdit("untitled");
  
  QLabel *folderLabel = new QLabel("");
  folderLabel->setFrameShape(QFrame::StyledPanel);
  
  QPushButton *browseButton = new QPushButton("Browse...");
  
  creazioneFileLayout->addWidget(nomeFileLineEdit, 1, 0, 1, 2);
  creazioneFileLayout->addWidget(folderLabel, 2, 0, 1, 1);
  creazioneFileLayout->addWidget(browseButton, 2, 1, 1, 1);
  //if (!filePath.isEmpty()) {
    //pm->apri_file_esistente(filePath.toStdString());
    // TODO passa alla MainWindow
  //}
}

StartWindow::StartWindow(Modello* _pm, QWidget *parent) : QWidget(parent), pm(_pm) {
  inizializza();
}

StartWindow::~StartWindow() {}


TODO cancellare
QString filePath = QFileDialog::getOpenFileName(nullptr, "apri file", "", "file di testo (*.csv)");

if (!filePath.isEmpty()) {
  // inizializza il modello
  qDebug() << "hai selezionaton il file:" << filePath;
}
*/
