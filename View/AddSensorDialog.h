#ifndef ADDSENSORDIALOG_H
#define ADDSENSORDIALOG_H

//#include<QWidget>
#include <QDialog>
#include<QWidget>
#include"../Headers/Modello.h"

#include<QVBoxLayout>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include <QComboBox>

class AddSensorDialog : public QDialog {
  Q_OBJECT
private:
  Modello *pm;
  QVBoxLayout *mainVLayout;
  QLineEdit *nameLineEdit;
  QComboBox *sensorTypeComboBox;
  QPushButton *createButton;
public slots:
  void on_nameEdited();
  void on_createButton();
public:
  AddSensorDialog(Modello *_pm);
};

# endif // ADDSENSORDIALOG_H
