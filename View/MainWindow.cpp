#include"MainWindow.h"

// ---------- PRIVATE ------------------------------------------------------------------------- //

// ---------- CONSTRUCTOR --------------------------------------------------------------------- //
MainWindow::MainWindow(Modello *_pm, QWidget *parent) : QMainWindow(parent), pm(_pm) {
  initStartWidget();  // la StartWindow è la schermata iniziale
}

//MainWindow::~MainWindow() {}

// ---------- PUBLIC -------------------------------------------------------------------------- //
void MainWindow::initMenuBar() {
  fileMenu = menuBar()->addMenu("File");

  saveAction = new QAction("Save");
  saveAction->setShortcut(QKeySequence("Ctrl+S"));
  fileMenu->addAction(saveAction);
  
  quitAction = new QAction("Quit");
  quitAction->setShortcut(QKeySequence("Ctrl+Q"));
  fileMenu->addAction(quitAction);
  
  // CONNECTIONS
  connect(saveAction, &QAction::triggered,
          this, &MainWindow::on_saveAction);;
  connect(quitAction, &QAction::triggered,
          this, &MainWindow::on_quitAction);
  
  // TODO AGGIUNGERE PIÙ ACTIONS...
  // new, open, close...
}

// Le successive due funzioni permettono di cambiare il central widget della MainWindow
void MainWindow::initStartWidget() {
  psw = new StartWidget(this, pm);
  setCentralWidget(psw);
}

void MainWindow::initSdcWidget() {
  psdcw = new SdcWidget(this, pm, this);
  setCentralWidget(psdcw);  // setta quello nuovo
}
// ---------- PUBLIC SLOTS -------------------------------------------------------------------- //

void MainWindow::on_saveAction() {
  pm->salva();
}

void MainWindow::on_quitAction() {
  // TODO aprire una finestra di dialogo per chiedere se salvare
  this->close();
}
