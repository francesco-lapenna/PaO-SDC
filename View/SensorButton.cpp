#include"SensorButton.h"


SensorButton::SensorButton(string _nome, int _id, string _tipo, 
                           SensoreAstratta *_ps, SdcWidget *_par) {
  nome = _nome;
  id = _id;
  tipo = _tipo;
  ps = _ps;
  par = _par;
  string text = "name: " + nome+
                "\ntype: " + tipo+
                "\nid: " + std::to_string(id);
  this->setText(QString::fromStdString(text));
  this->setFixedSize(180, 100);
}

// --------------------------------------------------------------------------------------------- //

void SensorButton::on_thisClicked() {
  par->set_activeSensor(ps);
}
