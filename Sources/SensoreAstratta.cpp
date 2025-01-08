#include"../Headers/SensoreAstratta.h"

#include<string>
#include<list>

// ------------------------------------------------------------------------------------- //

using std::string;
using std::list;

// private: ---------------------------------------------------------------------------- //

// protected: -------------------------------------------------------------------------- //

// public: ----------------------------------------------------------------------------- //

SensoreAstratta::SensoreAstratta(string _nome, int _id, string _tipo) : nome(_nome), id(_id), tipo(_tipo) {}

string SensoreAstratta::get_nome() { return nome; }

int SensoreAstratta::get_id() { return id; }

string SensoreAstratta::get_tipo() { return tipo; }

void SensoreAstratta::set_nome(string nuovo_nome) { nome = nuovo_nome; }

// raccoglie dato ogni 10 minuti (cioè 144 misurazioni in 24 ore)
void SensoreAstratta::genera_simulazione() {
  misurazioni.clear();
  int val = prendi_misurazione(0, 0); // prima misurazione, valore precedente arbitrario
  misurazioni.push_back(val);
  for (int i = 1; i < 144; ++i) {
    val = prendi_misurazione(i, val);  // metodo polimorfo, ogni sensore usa il suo
    misurazioni.push_back(val);
  }
}

std::list<int>::iterator SensoreAstratta::misurazioni_begin() { return misurazioni.begin(); }

std::list<int>::iterator SensoreAstratta::misurazioni_end() { return misurazioni.end(); }

void SensoreAstratta::doNothing() const {}
