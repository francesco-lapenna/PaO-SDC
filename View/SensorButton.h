#ifndef SENSORBUTTON_H
#define SENSORBUTTON_H

#include<QWidget>
#include<QPushButton>
#include"../Headers/SensoreAstratta.h"
#include"SdcWidget.h"

class SdcWidget;  // dichiarazione incompleta

// classe per fare i pulsanti dei sensori in SdcWidget
// sono dei normali pulsanti ma in più contengono varie informazioni:
// nome, tipo, id e puntatore al sensore a cui si riferiscono

class SensorButton : public QPushButton
{
  Q_OBJECT
private:
  string nome;
  int id;
  string tipo;
  SensoreAstratta *ps;  // puntatore al sensore
  SdcWidget *par;  // parent, puntatore al widget che li contiene
public slots:
  void on_thisClicked();  // quando premo il bottone mi inizializza il ChartWidget passandogli ps
public:
  SensorButton(string _nome, int _id, string _tipo, SensoreAstratta *_ps, SdcWidget *_par);
};

#endif // SENSORBUTTON_H


// TODO: visitor per dare un'icona al bottone in base al tipo?
