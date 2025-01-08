#ifndef SENSOREUMIDITA_H
#define SENSOREUMIDITA_H

#include"../View/VisitorAbstract.h"
#include"SensoreAstratta.h"

#include<string>

// ------------------------------------------------------------------------------------- //

using std::string;

// ------------------------------------------------------------------------------------- //

class SensoreUmidita : public SensoreAstratta {
private:
  int prendi_misurazione(int x_prec, int y_prec) const override;
protected:
public:
  SensoreUmidita(string _nome, int _id);
  void accept(VisitorAbstract* visitor) override;
};

#endif // SENSOREUMIDITA_H
