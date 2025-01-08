#ifndef SENSORETEMPERATURA_H
#define SENSORETEMPERATURA_H

#include"../View/VisitorAbstract.h"
#include"SensoreAstratta.h"

#include<string>

// ------------------------------------------------------------------------------------- //

using std::string;

// ------------------------------------------------------------------------------------- //

class SensoreTemperatura : public SensoreAstratta {
private:
  int prendi_misurazione(int x_prec, int y_prec) const override;
protected:
public:
  SensoreTemperatura(string _nome, int _id);
  void accept(VisitorAbstract* visitor) override;
};

#endif // SENSORETEMPERATURA_H
