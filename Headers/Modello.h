#ifndef MODELLO_H
#define MODELLO_H

#include"SensoreAstratta.h"
#include"SensoreTemperatura.h"
#include"SensoreUmidita.h"
#include"SensoreLuminosita.h"

#include<string>
#include<list>

#include<iostream>
using std::cout;    // TODO cancella questi tre servono solo per il testing
using std::endl;

// ------------------------------------------------------------------------------------- //

using std::string;
using std::list;

// ------------------------------------------------------------------------------------- //

class Modello {
private:
  list<SensoreAstratta*> sensori;           // lista di tutti i sensori
  list<SensoreAstratta*> sensori_cercati;   // lista dei sensori da mostrare nella barra
                                            // di ricerca
  // CAMPI DATI:
  int id_da_assegnare;  // = 10000000;  // TODO salvarlo nel file e ripristinarlo
  string file_path;
  bool mostra_temperatura;
  bool mostra_umidita;                      // stabiliscono se mostrare i sensori di un
  bool mostra_luminosita;                   // dato tipo nella barra di ricerca
  string nome_target;                       // rappresenta la stringa cercata dall'utente
  // INIZIALIZZATORE:
  bool controlla_file(string file_p);
  void inizializza_modello();
  void aggiorna_sensori_cercati();
protected:
public:
  
  // COSTRUTTORI e GESTIONE FILE:
  Modello();
  bool apri_file_esistente(string file_p);
  void apri_nuovo_file(string folder_p, string nome_file);
  void salva();
  // METODI:
  // aggiungi
  void aggiungi_sensore_temperatura(string _nome, int _id = 0);
  void aggiungi_sensore_umidita(string _nome, int _id = 0);
  void aggiungi_sensore_luminosita(string _nome, int _id = 0);
  // modifica
  void modifica_nome_sensore(string nuovo_nome, SensoreAstratta* ps);
  //elimina
  void elimina_sensore(SensoreAstratta* ps);  //TODO passagli un iteratore invece del punt?
  // ricerca e filtra
  void set_mostra_temperatura(bool val);
  void set_mostra_umidita(bool val);
  void set_mostra_luminosita(bool val);
  void set_nome_target(string val);
  
  // per iterare su sensori cercati dall'esterno della classe modello:
  auto begin() { return sensori_cercati.begin(); }
  auto end() { return sensori_cercati.end(); }
  
  // TODO cancellare le seguenti funzione temporanea per testare
  void stampa_sensori() {
    cout << "        sensori: ";
    for (auto it = sensori.begin(); it != sensori.end(); ++it) {
      cout << (*it)->get_nome() << " ";
    }
    cout << endl;
  }
  void stampa_sensori_cercati() {
    cout << "sensori_cercati: ";
    for (auto it = sensori_cercati.begin(); it != sensori_cercati.end(); ++it) {
      cout << (*it)->get_nome() << " ";
    }
    cout << endl;
  }
};

#endif // MODELLO_H
