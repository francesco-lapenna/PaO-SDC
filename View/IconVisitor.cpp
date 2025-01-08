#include"IconVisitor.h"

IconVisitor::IconVisitor(SdcWidget* _psdcw) : psdcw(_psdcw) {}

void IconVisitor::visitSensoreTemperatura(SensoreTemperatura* e) {
  e->doNothing();  // per evitare i warning unused parameter
  // potrei usare un getter di SensoreTemperatura per avere l'icon path
  // ma a quel punto non avrebbe senso l'esistenza del visitor
  // dato che basterebbe un getter virtuale in SensoreAstratta
  psdcw->set_icon_path("assets/icons/temperature.png");
}

void IconVisitor::visitSensoreUmidita(SensoreUmidita* e) {
  e->doNothing();
  psdcw->set_icon_path("assets/icons/humidity.png");
}

void IconVisitor::visitSensoreLuminosita(SensoreLuminosita* e) {
  e->doNothing();
  psdcw->set_icon_path("assets/icons/light.png");
}
