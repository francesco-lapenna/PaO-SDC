#ifndef SENSORELUMINOSITA_H
#define SENSORELUMINOSITA_H

#include"../View/VisitorAbstract.h"
#include"SensoreAstratta.h"

#include<string>

// ------------------------------------------------------------------------------------- //

using std::string;

// ------------------------------------------------------------------------------------- //

class SensoreLuminosita : public SensoreAstratta {
private:
  int prendi_misurazione(int x_prec, int y_prec) const override;
protected:
public:
  SensoreLuminosita(string _nome, int _id);
  void accept(VisitorAbstract* visitor) override;
};

#endif // SENSORELUMINOSITA_H
