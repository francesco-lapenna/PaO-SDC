#include"../Headers/Modello.h"

#include<string>
#include<list>
#include<sstream>
#include<fstream>

// ------------------------------------------------------------------------------------- //

using std::string;
using std::list;
using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::stoi;
using std::to_string;
using std::isdigit;

// funzione esterna: ------------------------------------------------------------------- //
bool is_number(string s) {
  if (s.empty()) return false;
  for (long unsigned int i = 0; i < s.size(); ++i) {
    if ( !isdigit(s[i]) ) return false;
  }
  return true;
}

// private: ---------------------------------------------------------------------------- //

bool Modello::controlla_file(string file_p) {
  // apro il file in modallità lettura
  ifstream file(file_p);
  // controllare id_da_assegnare
  string id_string;
  file >> id_string;
  if (!is_number(id_string)) return false;
  // controllare i sensori salvati
  string vs[3] = { "", "", "" };
  string line;
  int vc = 0, sn = 0;
  file >> line;
  while (!file.eof()) {
    // leggo i dati, in line ci deve essere: stringa,int,stringa
    vs[0] = ""; vs[1] = ""; vs[2] = "";
    vc = 0, sn = 0;
    for (long unsigned int i = 0; i < line.size(); ++i) {
      if (line[i] == *",") { vc++; sn++; }
      else { vs[sn] = line[i]; }
    }
    if (vc != 2) return false;
    if (vs[0] == "" || vs[1] == "" || vs[2] == "") return false;
    if (!is_number(vs[1])) return false;
    // passo alla riga successiva
    file >> line;
  }
  // chiudo il file
  file.close();
  return true;
}

void Modello::inizializza_modello() {
  // apro il file in modallità lettura
  ifstream file(file_path);
  // settare id_da_assegnare
  string id_string;
  file >> id_string;
  id_da_assegnare = stoi(id_string);  // safe dato che ho già eseguito controlla_modello
  // creare i sensori salvati
  string _nome, _id, _tipo, line;
  file >> line;
  while (!file.eof()) {
    // leggo i dati
    stringstream ss(line);
    getline(ss, _nome, ',');
    getline(ss, _id, ',');
    getline(ss, _tipo, ',');
    // creo il sensore (get_tipo inevitabile)
    if (_tipo == "temperatura") { aggiungi_sensore_temperatura(_nome, stoi(_id)); }
    else if (_tipo == "umidità") { aggiungi_sensore_umidita(_nome, stoi(_id)); }
    else if (_tipo == "luminosità") { aggiungi_sensore_luminosita(_nome, stoi(_id)); }
    // passo alla riga successiva
    file >> line;
  }
  // chiudo il file
  file.close();
}

void Modello::aggiorna_sensori_cercati() {
  sensori_cercati.clear();
  long unsigned int pos; string nome_ogg;
  for (auto it = sensori.begin(); it != sensori.end(); ++it) {
    nome_ogg = (*it)->get_nome();
    pos = nome_ogg.find(nome_target);
    if ( pos != string::npos ) {
      if (mostra_temperatura && dynamic_cast<SensoreTemperatura*>(*it))
        { sensori_cercati.push_back(*it); }
        // il push_back mantiene l'ordine di sensori
      else if (mostra_umidita && dynamic_cast<SensoreUmidita*>(*it))
        { sensori_cercati.push_back(*it); }
      else if (mostra_luminosita && dynamic_cast<SensoreLuminosita*>(*it))
        { sensori_cercati.push_back(*it); }
    }
  }
  // TODO se stai chiamando questa funzione vuol dire che hai potenzialmente modificato la
  // lista dei sensori cercati, quindi può essere questa l'unica funzione nel codice ad
  // aggiornare l'observer a sensori cercati.
  // il costo computazionale aumenta ma la complessità del codice diminuisce 
}

// protected: -------------------------------------------------------------------------- //

// public: ----------------------------------------------------------------------------- //

Modello::Modello() : mostra_temperatura(true), mostra_umidita(true),
                     mostra_luminosita(true), nome_target("") {}

bool Modello::apri_file_esistente(string file_p) {
  bool file_valido = controlla_file(file_p);
  if (file_valido) {
    // setta il file_path al percorso del file che si vuole aprire
    file_path = file_p;
    // inizializzo id_da_assegnare e creo i sensori specificati nel file
    inizializza_modello();
  }
  return file_valido;  // per sapere se l'apertura del file è andata a buon fine
}

void Modello::apri_nuovo_file(string folder_p, string nome_file) {
  // assegno a file_path il percorso completo:
  file_path = folder_p + "/" + nome_file + ".csv";
  // apro il file e scrivo solo l'id precedente al primo id da assegnare
  // (per ora non ci sono ancora sensori)
  ofstream file(file_path);
  file << "10000000" << endl;
  file.close();
  // inizializzo id_da_assegnare
  inizializza_modello();
}

void Modello::salva() {
  // apro il file in modalità scrittura (quindi cancella il contenuto)
  ofstream file(file_path);
  // salvo il prossimo id da assegnare
  file << to_string(id_da_assegnare) << endl;
  //per ogni sensore salvo le informazioni
  for (auto it = sensori.begin(); it != sensori.end(); ++it) {
    string info = (*it)->get_nome() + "," + to_string((*it)->get_id()) + "," + (*it)->get_tipo(); 
    file << info << endl;
  }
  file.close();
}

// Metodi Aggiungi
void Modello::aggiungi_sensore_temperatura(string _nome, int _id) {
  if (_id == 0) { _id = id_da_assegnare++; }
  SensoreAstratta *psa = new SensoreTemperatura(_nome, _id);
  sensori.push_front(psa);
  aggiorna_sensori_cercati();
}

void Modello::aggiungi_sensore_umidita(string _nome, int _id) {
  if (_id == 0) { _id = id_da_assegnare++; }
  SensoreAstratta *psa = new SensoreUmidita(_nome, _id);
  sensori.push_front(psa);
  aggiorna_sensori_cercati();
}

void Modello::aggiungi_sensore_luminosita(string _nome, int _id) {
  if (_id == 0) { _id = id_da_assegnare++; }
  SensoreAstratta *psa = new SensoreLuminosita(_nome, _id);
  sensori.push_front(psa);
  aggiorna_sensori_cercati();
}

// Metodi Modifica ed Elimina
void Modello::modifica_nome_sensore(string nuovo_nome, SensoreAstratta* ps) {
  ps->set_nome(nuovo_nome);
  aggiorna_sensori_cercati();  // che a sua volta aggiorna l'observer a sensori_cercati
  // TODO aggiornare l'observer a sensore modificato (farlo nella set_nome?)
}

// TODO al posto di passagli un sensore gli passi un iteratore? per diminuire la compless.?
void Modello::elimina_sensore(SensoreAstratta* ps) {
  for (auto it = sensori.begin(); it != sensori.end(); ++it) {
    if ((*it) == ps) { it = sensori.erase(it); }
  }
  aggiorna_sensori_cercati();
}

// Metodi Ricerca
void Modello::set_mostra_temperatura(bool val) {
  // setta mostra_temperatura al valore val indicato
  mostra_temperatura = val;
  // aggiorna la lista dei sensori cercati in base alle nuove informazioni
  aggiorna_sensori_cercati();
}

void Modello::set_mostra_umidita(bool val) {
  mostra_umidita = val;
  aggiorna_sensori_cercati();
}

void Modello::set_mostra_luminosita(bool val) {
  mostra_luminosita = val;
  aggiorna_sensori_cercati();
}

void Modello::set_nome_target(string val) {
  nome_target = val;
  aggiorna_sensori_cercati();
}


