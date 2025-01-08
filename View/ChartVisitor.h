#ifndef CHARTVISITOR_H
#define CHARTVISITOR_H

#include"VisitorAbstract.h"
#include"SdcWidget.h"

#include<QtCharts>
#include<QChartView>

#include<QLineSeries>

#include<QBarSet>
#include<QBarSeries>

class SdcWidget;

class ChartVisitor : public VisitorAbstract {
private:
  SdcWidget* psdcw;
public:
  explicit ChartVisitor(SdcWidget* _psdcw);
  void visitSensoreTemperatura(SensoreTemperatura* e) override;
  void visitSensoreUmidita(SensoreUmidita* e) override;
  void visitSensoreLuminosita(SensoreLuminosita* e) override;
};

#endif // CHARTVISITOR_H
