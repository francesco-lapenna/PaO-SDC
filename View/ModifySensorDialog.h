#ifndef MODIFYSENSORDIALOG_H
#define MODIFYSENSORDIALOG_H

//#include<QWidget>
#include <QDialog>
#include<QWidget>
#include"../Headers/Modello.h"
#include"../Headers/SensoreAstratta.h"

#include<QVBoxLayout>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>

class ModifySensorDialog : public QDialog {
  Q_OBJECT
private:
  Modello *pm;
  SensoreAstratta *ps;
  QVBoxLayout *mainVLayout;
  QLineEdit *nameLineEdit;
  QPushButton *applyButton;
public slots:
  void on_nameEdited();
  void on_applyButton();
public:
  ModifySensorDialog(Modello *_pm, SensoreAstratta *_ps);
};

# endif // MODIFYSENSORDIALOG_H
