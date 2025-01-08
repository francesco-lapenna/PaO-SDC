#include"ChartVisitor.h"

ChartVisitor::ChartVisitor(SdcWidget* _psdcw) : psdcw(_psdcw) {}

// --------------------------------------------------------------------------------------------- //

void ChartVisitor::visitSensoreTemperatura(SensoreTemperatura* e) {
  // creare la serie
  e->genera_simulazione();  // e = psdcw->activeSensor
  
  QLineSeries *series = new QLineSeries();
  int i = 0;
  int minima = std::numeric_limits<int>::max();
  int massima = std::numeric_limits<int>::min();
  for (auto it = e->misurazioni_begin(); it != e->misurazioni_end(); ++it)
  {
    if (*it < minima) minima = *it;
    if (*it > massima) massima = *it;
    series->append(i, *it);
    i += 10;
  }
  
  // creare il chart
  psdcw->chart = new QChart();
  psdcw->chart->legend()->hide();
  //psdcw->chart->legend()->setVisible(true);
  //psdcw->chart->legend()->setAlignment(Qt::AlignBottom);
  psdcw->chart->addSeries(series);
  psdcw->chart->createDefaultAxes();
  psdcw->chart->setTitle("Simulation Data");  // TODO aggiungere il nome del sensore?
  psdcw->chart->setAnimationOptions(QChart::SeriesAnimations);
  psdcw->chart->setAnimationDuration(1000);  // TODO aumentare a 2000?
  psdcw->chart->setTheme(QChart::ChartThemeQt);
  
  // creare la chart view
  psdcw->chartView = new QChartView(psdcw->chart);
  psdcw->chartView->setRenderHint(QPainter::Antialiasing);
  
  // settarlo in psdcw
  psdcw->infoGLayout->addWidget(psdcw->chartView, 2, 0, 3, 6);
  
  // aggiungo info specifiche del sensore
  //delete psdcw->maxLabel;
  //delete psdcw->minLabel;
  psdcw->maxLabel->setText("max: " + QString::number(massima));
  psdcw->minLabel->setText("min: " + QString::number(minima));
  
}

// --------------------------------------------------------------------------------------------- //

void ChartVisitor::visitSensoreUmidita(SensoreUmidita* e) {
  // creare la serie
  e->genera_simulazione();  // e = psdcw->activeSensor
  
  QLineSeries *series = new QLineSeries();
  int i = 0, n = 0, somma = 0;
  for (auto it = e->misurazioni_begin(); it != e->misurazioni_end(); ++it)
  {
    series->append(i, *it);
    i += 10;
    somma += *it;
    n++;
  }
  int average = somma/n;
  
  // creare il chart
  psdcw->chart = new QChart();
  psdcw->chart->legend()->hide();
  //psdcw->chart->legend()->setVisible(true);
  //psdcw->chart->legend()->setAlignment(Qt::AlignBottom);
  psdcw->chart->addSeries(series);
  psdcw->chart->createDefaultAxes();
  psdcw->chart->setTitle("Simulation Data");  // TODO aggiungere il nome del sensore?
  psdcw->chart->setAnimationOptions(QChart::SeriesAnimations);
  psdcw->chart->setAnimationDuration(1000);  // TODO aumentare a 2000?
  psdcw->chart->setTheme(QChart::ChartThemeQt);
  
  // creare la chart view
  psdcw->chartView = new QChartView(psdcw->chart);
  psdcw->chartView->setRenderHint(QPainter::Antialiasing);
  
  // settarlo in psdcw
  psdcw->infoGLayout->addWidget(psdcw->chartView, 2, 0, 1, 6);
  
  // aggiungo info specifiche del sensore
  psdcw->avgLabel->setText("avg: " + QString::number(average));
  //psdcw->infoGLayout->addWidget(psdcw->avgLabel, 0, 4, 1, 1);
}

// --------------------------------------------------------------------------------------------- //

void ChartVisitor::visitSensoreLuminosita(SensoreLuminosita* e) {
  // creare la serie
  e->genera_simulazione();  // e = psdcw->activeSensor
  
  QBarSet *set = new QBarSet("misurazioni");
  int i = 0;
  for (auto it = e->misurazioni_begin(); it != e->misurazioni_end(); ++it)
  {
    set->append(*it);
    i += 10;
  }
  
  QBarSeries *series = new QBarSeries();
  series->append(set);
  
  // creare il chart
  psdcw->chart = new QChart();
  psdcw->chart->addSeries(series);
  psdcw->chart->setTitle("Simulation Data");  // TODO aggiungere il nome del sensore?
  psdcw->chart->setAnimationOptions(QChart::SeriesAnimations);
  psdcw->chart->setAnimationDuration(1000);  // TODO aumentare a 2000?
  psdcw->chart->setTheme(QChart::ChartThemeQt);
  
  // creare la chart view
  psdcw->chartView = new QChartView(psdcw->chart);
  //psdcw->chartView->setRenderHint(QPainter::Antialiasing);
  
  // settarlo in psdcw
  psdcw->infoGLayout->addWidget(psdcw->chartView, 2, 0, 1, 6);
}












