#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include"../Headers/Modello.h"
#include"StartWidget.h"
#include"SdcWidget.h"

class StartWidget;
class SdcWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  Modello *pm;
  StartWidget *psw;
  SdcWidget *psdcw;
  // MENUS:
  QMenu *fileMenu;
  // ACTIONS:
  QAction *saveAction;
  QAction *quitAction;
public:
  MainWindow(Modello *_pm, QWidget *parent = nullptr);
  //~MainWindow();
  void initMenuBar();
  void initStartWidget();
  void initSdcWidget();
public slots:
  void on_saveAction();
  void on_quitAction();
};

#endif // MAINWINDOW_H
