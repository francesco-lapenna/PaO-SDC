#include"../View/MainWindow.h"
#include"../Headers/Modello.h"

#include<QApplication>

///*
int main(int argc, char *argv[]) {
  Modello m;
  
  // TODO: mettere un tema?
  QApplication app(argc, argv);
  MainWindow mw(&m);
  mw.show();
  return app.exec();
}
//*/


/*
// TESTING, TODO CANCELLA DA QUI...
#include"../Headers/Modello.h"
#include<iostream>
#include<list>
using namespace std;

int main() {
  Modello m;
  //m.apri_nuovo_file("/home/francesco/Desktop/SDC/Salvataggi", "prova05");
  m.apri_file_esistente("/home/francesco/Desktop/SDC/Salvataggi/prova05.csv");
  
  m.stampa_sensori();
  
  m.salva();
  
  
  cout << 1 << endl;
  m.stampa_sensori();
  m.stampa_sensori_cercati();
  
  m.aggiungi_sensore_temperatura("t1");
  m.aggiungi_sensore_umidita("u1");
  m.aggiungi_sensore_luminosita("l1");
  m.aggiungi_sensore_temperatura("t2");
  m.aggiungi_sensore_temperatura("t3");
  m.aggiungi_sensore_temperatura("t1abc");
  cout << 2 << endl;
  m.stampa_sensori();
  m.stampa_sensori_cercati();
  
  
    
  cout << endl << "FINE" << endl;
}

// ...A QUI
*/

