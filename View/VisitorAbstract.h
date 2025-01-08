#ifndef VISITORABSTRACT_H
#define VISITORABSTRACT_H

//#include"../Headers/SensoreTemperatura.h"
//#include"../Headers/SensoreUmidita.h"
//#include"../Headers/SensoreLuminosita.h"
class SensoreTemperatura;
class SensoreUmidita;
class SensoreLuminosita;

class VisitorAbstract {
private:
public:
  virtual void visitSensoreTemperatura(SensoreTemperatura* e) = 0;
  virtual void visitSensoreUmidita(SensoreUmidita* e) = 0;
  virtual void visitSensoreLuminosita(SensoreLuminosita* e) = 0;
};

#endif // VISITORABSTRACT_H
