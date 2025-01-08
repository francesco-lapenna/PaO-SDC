#include<string>
#include<stdlib.h>
#include<cmath>

#include<iostream>  // TODO cancellare

#include"../Headers/SensoreLuminosita.h"

// ------------------------------------------------------------------------------------- //

using std::string;
using std::pow;

// private: ---------------------------------------------------------------------------- //

// implementazione specifica di prendi_misurazione di un sensore che misura la temperatura
int SensoreLuminosita::prendi_misurazione(int x_prec, int y_prec) const {
  int aux;
  if (x_prec == 0) { aux = 22; }  // se è la prima misurazione gli do il valore di 22 (°C)
  else {
    int offset = y_prec - 50;  // inizio del range
    int range = 100;  // ampiezza del range
    aux = offset + (rand() % range);
  }
  return aux;
}
/*
int SensoreLuminosita::prendi_misurazione(int x_prec, int y_prec) const {
  int aux;
  if (x_prec == 0) { aux = 2; return aux; }  // se è la prima misurazione gli do il valore di 2 (LUX)
  else {
    x_prec -= 72;
    float e(2.7), a(100), b(0), c(30);
    int aux = static_cast<int>( a * pow(e, -pow( (x_prec-b) / c, 2 )) );
    int noise = y_prec / 10;
    aux += noise;
    return aux;
  }
}
*/

// protected: -------------------------------------------------------------------------- //

// public: ----------------------------------------------------------------------------- //
SensoreLuminosita::SensoreLuminosita(string _nome, int _id) : SensoreAstratta(_nome, _id, "luminosità") {}

// VISITOR
void SensoreLuminosita::accept(VisitorAbstract* visitor) {
  visitor->visitSensoreLuminosita(this);
}





