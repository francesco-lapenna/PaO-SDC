#include"SdcWidget.h"

// TODO cancellare
#include<iostream>
using std::cout;
using std::endl;
//

// ---------- UTILITY ------------------------------------------------------------------------- //

void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

// ---------- COSTRUTTORI E INIZIALIZZATORI --------------------------------------------------- //

SdcWidget::SdcWidget(MainWindow *_pmw, Modello *_pm, QWidget *parent) : QWidget(parent), pmw(_pmw), pm(_pm) {
  pmw->initMenuBar();

  this->setMinimumSize(750, 650);
  
  mainVLayout = new QVBoxLayout;
  setLayout(mainVLayout);
  
  // SEARCH FRAME
  searchFrame = new QFrame;
  searchFrame->setFrameShape(QFrame::StyledPanel);
  searchFrame->setFrameShadow(QFrame::Raised);
  mainVLayout->addWidget(searchFrame);
  
  searchHLayout = new QHBoxLayout(searchFrame);
  searchFrame->setFixedHeight(180);
  filtersVLayout = new QVBoxLayout;
  searchHLayout->addLayout(filtersVLayout);
  filtersVLayout->addWidget(new QLabel("Search:"));
  sensorNameLineEdit = new QLineEdit();
  sensorNameLineEdit->setFixedWidth(170);
  sensorNameLineEdit->setPlaceholderText("Insert sensor name:");
  filtersVLayout->addWidget(sensorNameLineEdit);
  filtersVLayout->addWidget(new QLabel("Filters:"));
  
  lightCheckBox = new QCheckBox("light");
  temperatureCheckBox = new QCheckBox("temperature");
  umidityCheckBox = new QCheckBox("umidity");
  lightCheckBox->setChecked(true);
  temperatureCheckBox->setChecked(true);
  umidityCheckBox->setChecked(true);
  filtersVLayout->addWidget(lightCheckBox);
  filtersVLayout->addWidget(temperatureCheckBox);
  filtersVLayout->addWidget(umidityCheckBox);
  
  // SCROLL AREA
  sensorsScrollArea = new QScrollArea();
  searchHLayout->addWidget(sensorsScrollArea);
  
  scrollWidget = new QWidget;
  scrollHLayout = new QHBoxLayout();
  scrollWidget->setLayout(scrollHLayout);
  
  sensorsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  sensorsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  sensorsScrollArea->setWidgetResizable(true);
  
  sensorsScrollArea->setWidget(scrollWidget);
  
  addNewSensorButton = new QPushButton("Add");
  addNewSensorButton->setFixedSize(50, 50);
  searchHLayout->addWidget(addNewSensorButton);
  
  // SENSOR FRAME
  sensorFrame = new QFrame;
  sensorFrame->setFrameShape(QFrame::StyledPanel);
  sensorFrame->setFrameShadow(QFrame::Raised);
  mainVLayout->addWidget(sensorFrame);
  
  infoGLayout = new QGridLayout(sensorFrame);
  
  // connetto tutti i pulsanti / checkbox / linedit
  connect_all();
  
  // creo i bottoni dei sensori
  update_sensor_list();
}

// ---------- PRIVATE FUNCTIONS --------------------------------------------------------------- //

void SdcWidget::initSensorFrame() {
  clearLayout(infoGLayout);
  
  if ( activeSensor != nullptr ) {
    // INFO LABELS
    QString nome = QString::fromStdString(activeSensor->get_nome());
    QString id = QString::fromStdString(std::to_string(activeSensor->get_id()));
    QString tipo = QString::fromStdString(activeSensor->get_tipo());
    
    activeSensorNameLabel = new QLabel("Nome: " + nome);
    
    infoGLayout->addWidget( activeSensorNameLabel , 0, 0, 1, 1);
    infoGLayout->addWidget( new QLabel("ID: " + id) , 0, 1, 1, 1);
    infoGLayout->addWidget( new QLabel("Tipo: " + tipo) , 0, 2, 1, 1);
    
    QSpacerItem *spcr = new QSpacerItem(100, 25, QSizePolicy::Expanding);
    infoGLayout->addItem(spcr, 0, 3, 1, 1);
    
    // ICON LABEL
    IconVisitor *iv = new IconVisitor(this);
    activeSensor->accept(iv);  // chiama set_icon_path
    
    QLabel *iconLabel = new QLabel;
    infoGLayout->addWidget(iconLabel, 0, 5, 2, 1);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setFixedSize(50, 50);

    // prima: QPixmap pixmap(QString::fromStdString(activeSensor->get_iconPath()));
    QPixmap pixmap(QString::fromStdString(icon_path));
    pixmap = pixmap.scaled(iconLabel->size(), Qt::KeepAspectRatio);
    iconLabel->setPixmap(pixmap);
    
    // BUTTONS
    modifyButton = new QPushButton("Modify");
    deleteButton = new QPushButton("Delete");
    simulationButton = new QPushButton("Simulation");
    
    modifyButton->setFixedSize(180, 25);
    deleteButton->setFixedSize(180, 25);
    simulationButton->setFixedSize(180, 25);
    
    infoGLayout->addWidget(modifyButton, 1, 0, 1, 1);
    infoGLayout->addWidget(deleteButton, 1, 1, 1, 1);
    infoGLayout->addWidget(simulationButton, 1, 2, 1, 1);
    
    // connections
    connect(modifyButton, &QPushButton::clicked,
            this, &SdcWidget::on_modifyButton);
    connect(deleteButton, &QPushButton::clicked,
            this, &SdcWidget::on_deleteButton);
    connect(simulationButton, &QPushButton::clicked,
            this, &SdcWidget::on_simulationButton);
    
    // EMPTY CHART
    chart = new QChart();
    chart->createDefaultAxes();
    chart->setTitle("Simulation Data Chart\n(click 'Simulation' button to populate)");
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    infoGLayout->addWidget(chartView, 2, 0, 1, 6);
    
    maxLabel = new QLabel("");
    minLabel = new QLabel("");
    avgLabel = new QLabel("");
    
    infoGLayout->addWidget(maxLabel, 0, 4, 1, 1);
    infoGLayout->addWidget(minLabel, 1, 4, 1, 1);
    infoGLayout->addWidget(avgLabel, 0, 4, 1, 1);
  }
}

void SdcWidget::update_sensor_list() {
  // chiama questa funzione ogni volta che sensori_cercati viene potenzialmente modificata
  clearLayout(scrollHLayout);  // elimina i pulsanti esistenti
  for (auto it = pm->begin(); it != pm->end(); ++it) {  // itera su sensori_cercati
    // crea un pulsante per ogni sensore da mostrare
    SensorButton *b = new SensorButton((*it)->get_nome(), (*it)->get_id(), (*it)->get_tipo(), *it, this);
    connect(b, &QPushButton::clicked,
            b, &SensorButton::on_thisClicked);
    scrollHLayout->addWidget(b);
  }
  scrollHLayout->addStretch();
}

void SdcWidget::connect_all() {

  connect(sensorNameLineEdit, &QLineEdit::textEdited,
          this, &SdcWidget::on_sensorNameEdited);
          
  connect(lightCheckBox, &QPushButton::clicked,
          this, &SdcWidget::on_lightCheckBox);
  
  connect(temperatureCheckBox, &QPushButton::clicked,
          this, &SdcWidget::on_temperatureCheckBox);
  
  connect(umidityCheckBox, &QPushButton::clicked,
          this, &SdcWidget::on_umidityCheckBox);
  
  connect(addNewSensorButton, &QPushButton::clicked,
          this, &SdcWidget::on_addNewSensorButton);

}

// ---------- PUBLIC SLOTS -------------------------------------------------------------------- //

void SdcWidget::on_sensorNameEdited(const QString& text) {
  pm->set_nome_target( text.toStdString() );  // modifico il modello
  update_sensor_list();  // aggiorno la vista
}

void SdcWidget::on_lightCheckBox() {
  bool state = lightCheckBox->isChecked();
  pm->set_mostra_luminosita(state);
  update_sensor_list();
}

void SdcWidget::on_temperatureCheckBox() {
  bool state = temperatureCheckBox->isChecked();
  pm->set_mostra_temperatura(state);
  update_sensor_list();
}

void SdcWidget::on_umidityCheckBox() {
  bool state = umidityCheckBox->isChecked();
  pm->set_mostra_umidita(state);
  update_sensor_list();
}

void SdcWidget::on_addNewSensorButton() {
  AddSensorDialog asDialog(pm);
  asDialog.setModal(true);
  asDialog.exec();
  update_sensor_list(); 
}

// ----------

void SdcWidget::on_modifyButton() {
  // apro una finestra di dialogo per far inserire il nuovo nome
  // e chiamo Modello::modifica_nome_sensore()
  ModifySensorDialog msDialog(pm, activeSensor);
  msDialog.setModal(true);
  msDialog.exec();
  // aggiorno il sensorFrame
  QString nome = QString::fromStdString(activeSensor->get_nome());
  activeSensorNameLabel->setText("Nome: " + nome);
  // aggiorno la sensor list
  update_sensor_list();
}

void SdcWidget::on_deleteButton() {
  // setto activeSensor a nullptr
  SensoreAstratta *temp = activeSensor;
  activeSensor = nullptr;
  // aggiorno il sensorFrame
  initSensorFrame();
  // elimino il sensore dal modello
  pm->elimina_sensore(temp);
  // aggiorno la sensor list
  update_sensor_list();
}  // TODO chiedergli se è sicuro con una finestra di dialogo?

void SdcWidget::on_simulationButton() {
  // ChartVisitor si occupa di creare un grafico e info diverse per ogni sensore
  // e di settarlo nella window principale
  ChartVisitor *cv = new ChartVisitor(this);
  activeSensor->accept(cv);
}

// ---------- PUBLIC -------------------------------------------------------------------------- //

void SdcWidget::set_activeSensor(SensoreAstratta *ps) {
  // setto il sensore da mostrare
  activeSensor = ps;
  // inizializzo il widget del sensore
  initSensorFrame();
}

void SdcWidget::set_icon_path(string _icon_path) {
  icon_path = _icon_path;
}






