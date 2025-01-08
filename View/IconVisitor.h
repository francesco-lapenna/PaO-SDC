#ifndef ICONVISITOR_H
#define ICONVISITOR_H

#include"VisitorAbstract.h"
#include"SdcWidget.h"
class SdcWidget;

class IconVisitor : public VisitorAbstract {
private:
  SdcWidget* psdcw;
public:
  explicit IconVisitor(SdcWidget* _psdcw);
  void visitSensoreTemperatura(SensoreTemperatura* e) override;
  void visitSensoreUmidita(SensoreUmidita* e) override;
  void visitSensoreLuminosita(SensoreLuminosita* e) override;
};

#endif // ICONVISITOR_H
