# Progetto Programmazione ad Oggetti
Progetto svolto per il corso "Programmazione ad oggetti" del corso di Laurea in Informatica all'Università degli Studi di Padova.
Anno Accademico 2023/24.

Progetto sviluppato in C++ e Qt con tema: applicazione di gestione di un sistema di sensori.

## Valutazione del Professore
Feedback Progetto di Programmazione ad Oggetti
Studente: Lapenna Francesco
Valutazione del progetto: Ottimo

Vincoli obbligatori
+ Soddisfatti


Orientamento ad oggetti
+ Incapsulamento
+ Modularità (modello logico e la GUI sono separati)
+ Estensibilità ed evolvibilità, polimorfismo
+ Efficienza e robustezza


Funzionalità
+ Funzionalità di ricerca e filtro
+ Ricerca in tempo reale
+ Filtro sul tipo di sensore
- Migliorabile consentendo di impostare e modificare i parametri
  dei sensori, come valori minimo e massimo, media, ecc.


GUI
+ Visualizza i diversi tipi di dato in maniera opportuna
+ Usabile e intuitiva
+ Robusta, gestisce ridimensionamento
+ Utilizza icone
+ Utilizza immagini
- Migliorabile la visualizzazione dei widget dei sensori, attualmente mostrati
  come semplici pulsanti
- Migliorabile attraverso l'utilizzo di colori e stili grafici


Relazione
+ Adeguata


Suggerimenti non collegati alla valutazione
Nessuno.


## Istruzioni per la compilazione
Compilare con:
```bash
sudo apt install qmake6 make qtbase5-dev qtchooser libqt5charts5-dev

cd build
qmake6 ..
make
```

Clean rebuild
```bash
rm -rf build
mkdir build
cd build
qmake6 ..
make
```
