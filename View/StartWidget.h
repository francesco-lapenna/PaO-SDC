#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include<QWidget>
#include"MainWindow.h"
#include"../Headers/Modello.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QLabel>
#include"FileCreationWidget.h"

class MainWindow;
class FileCreationWidget;

class StartWidget : public QWidget
{
  Q_OBJECT
private:
  MainWindow *pmw;
  Modello *pm;
  QVBoxLayout *mainLayout;
  QHBoxLayout *buttonsLayout;
  QPushButton *openButton;
  QPushButton *createButton;
  QLabel *fileNotValidLabel;
  FileCreationWidget *fcw;
private slots:
  void on_openButton();
  void on_createButton();
public:
  StartWidget(MainWindow *_pmw, Modello *_pm, QWidget *parent = nullptr);
  //~StartWidget();
};

#endif // STARTWIDGET_H
