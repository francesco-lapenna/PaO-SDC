#ifndef SENSOREASTRATTA_H
#define SENSOREASTRATTA_H

#include<string>
#include<list>
//#include"../View/VisitorAbstract.h"
class VisitorAbstract;

// ------------------------------------------------------------------------------------- //

using std::string;
using std::list;

// ------------------------------------------------------------------------------------- //

class SensoreAstratta {
private:
  // CAMPI DATI:
  string nome;
  int id;
  string tipo;
  list<int> misurazioni;
  // METODI:
  virtual int prendi_misurazione(int x_prec, int y_prec) const = 0;
protected:
public:
  // COSTRUTTORI:
  SensoreAstratta(string _nome, int _id, string _tipo);
  
  // VISITOR:
  virtual void accept(VisitorAbstract* visitor) = 0;
  
  // METODI:
  string get_nome();
  int get_id();
  string get_tipo();
  void set_nome(string nuovo_nome);
  void genera_simulazione();
  std::list<int>::iterator misurazioni_begin();
  std::list<int>::iterator misurazioni_end();
  void doNothing() const;
};

#endif // SENSOREASTRATTA_H

