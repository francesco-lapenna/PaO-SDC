#include<string>
#include<stdlib.h>

#include"../Headers/SensoreTemperatura.h"

// ------------------------------------------------------------------------------------- //

using std::string;

// private: ---------------------------------------------------------------------------- //

// implementazione specifica di prendi_misurazione di un sensore che misura la temperatura
int SensoreTemperatura::prendi_misurazione(int x_prec, int y_prec) const {
  int aux;
  if (x_prec == 0) { aux = 22; }  // se è la prima misurazione gli do il valore di 22 (°C)
  else {
    int offset = y_prec - 3;  // inizio del range
    int range = 7;  // ampiezza del range
    aux = offset + (rand() % range);
  }
  return aux;
}

// protected: -------------------------------------------------------------------------- //

// public: ----------------------------------------------------------------------------- //
SensoreTemperatura::SensoreTemperatura(string _nome, int _id) : SensoreAstratta(_nome, _id, "temperatura") {}

// VISITOR
void SensoreTemperatura::accept(VisitorAbstract* visitor) {
  visitor->visitSensoreTemperatura(this);
}
