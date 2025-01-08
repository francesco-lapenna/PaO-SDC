#include<string>
#include<stdlib.h>

#include"../Headers/SensoreUmidita.h"

// ------------------------------------------------------------------------------------- //

using std::string;

// private: ---------------------------------------------------------------------------- //

// implementazione specifica di prendi_misurazione di un sensore che misura l'umidità
int SensoreUmidita::prendi_misurazione(int x_prec, int y_prec) const {
  int aux;
  if (x_prec == 0) { aux = 50; }  // se è la prima misurazione gli do il valore di 50 (%)
  else {
    int offset = std::min(y_prec - 5, 90);  // inizio del range (si tiene sotto il 100%)
    int range = 11;  // ampiezza del range
    aux = offset + (rand() % range);  // varia in base al valore precedente
  }
  return aux;
}

// protected: -------------------------------------------------------------------------- //

// public: ----------------------------------------------------------------------------- //
SensoreUmidita::SensoreUmidita(string _nome, int _id) : SensoreAstratta(_nome, _id, "umidità") {}

// VISITOR
void SensoreUmidita::accept(VisitorAbstract* visitor) {
  visitor->visitSensoreUmidita(this);
}
