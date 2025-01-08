#ifndef SDCWIDGET_H
#define SDCWIDGET_H

#include<QWidget>
#include<string>
#include"MainWindow.h"
#include"../Headers/Modello.h"
#include"../Headers/SensoreAstratta.h"
#include"IconVisitor.h"
#include"ChartVisitor.h"

#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QScrollArea>
#include "SensorButton.h"
#include"AddSensorDialog.h"
#include"ModifySensorDialog.h"
#include <QSpacerItem>
#include <QPixmap>
#include<QtCharts>
#include<QChartView>

class MainWindow;

class SdcWidget : public QWidget
{
friend class ChartVisitor;  // ChartVisitor può settare widget senza funzioni ulteriori
  Q_OBJECT
private:
  MainWindow *pmw;
  Modello *pm;
  SensoreAstratta *activeSensor;
  //
  QVBoxLayout *mainVLayout;
  
  QFrame *searchFrame;
  QHBoxLayout *searchHLayout;
  QVBoxLayout *filtersVLayout;
  QLineEdit *sensorNameLineEdit;
  QCheckBox *lightCheckBox;
  QCheckBox *temperatureCheckBox;
  QCheckBox *umidityCheckBox;
  QScrollArea *sensorsScrollArea;
  QWidget *scrollWidget;
  QHBoxLayout *scrollHLayout;  // i pulsanti dei sensori li aggiungi a questo layout
  QPushButton *addNewSensorButton;
  
  QFrame *sensorFrame;
  QGridLayout *infoGLayout;
  QLabel *activeSensorNameLabel;
  QPushButton *modifyButton;
  QPushButton *deleteButton;
  QPushButton *simulationButton;
  string icon_path;

  QFrame *chartFrame;
  QChart *chart;
  QChartView *chartView;
  
  QLabel *maxLabel;
  QLabel *minLabel;
  QLabel *avgLabel;
  
  void initSensorFrame();
  void update_sensor_list();
  void connect_all();
public slots:
  void on_sensorNameEdited(const QString& text);
  void on_lightCheckBox();
  void on_temperatureCheckBox();
  void on_umidityCheckBox();
  void on_addNewSensorButton();
  // ----------
  void on_modifyButton();
  void on_deleteButton();
  void on_simulationButton();
public:
  SdcWidget(MainWindow *_pmw, Modello *_pm, QWidget *parent = nullptr);
  void set_activeSensor(SensoreAstratta *ps);
  void set_icon_path(string _icon_path);
};

#endif // SDCWIDGET_H
