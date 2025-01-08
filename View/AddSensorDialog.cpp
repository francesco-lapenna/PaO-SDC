#include"AddSensorDialog.h"

AddSensorDialog::AddSensorDialog(Modello *_pm) : pm(_pm) {
  mainVLayout = new QVBoxLayout;
  setLayout(mainVLayout);
  
  // LINE EDIT
  mainVLayout->addWidget(new QLabel("Insert sensor name (max 15 chars):"));
  
  nameLineEdit = new QLineEdit;
  nameLineEdit->setFixedWidth(170);
  //nameLineEdit->setPlaceholderText("name...");
  nameLineEdit->setInputMask("Nnnnnnnnnnnnnnn");  // per evitare troppi controlli setto una mask
  mainVLayout->addWidget(nameLineEdit);
  
  // COMBO BOX
  mainVLayout->addWidget(new QLabel("Choose sensor type:"));
  
  sensorTypeComboBox = new QComboBox;
  mainVLayout->addWidget(sensorTypeComboBox);

  sensorTypeComboBox->addItem("Temperatura");
  sensorTypeComboBox->addItem("Umidità");
  sensorTypeComboBox->addItem("Luminosità");
  
  // BUTTON
  createButton = new QPushButton("create");
  createButton->setIcon(QIcon::fromTheme("emblem-default"));
  createButton->setEnabled(false);
  mainVLayout->addWidget(createButton);
  
  // CONNESSIONI
  connect(nameLineEdit, &QLineEdit::textEdited,
          this, &AddSensorDialog::on_nameEdited);
  connect(createButton, &QPushButton::clicked,
          this, &AddSensorDialog::on_createButton);
  
}

// ---------- PUBLIC SLOTS --------------------------------------------------------------------- //

void AddSensorDialog::on_nameEdited() {
  if (nameLineEdit->hasAcceptableInput()) {
    createButton->setEnabled(true);
  }
  else {
    createButton->setEnabled(false);
  }
}

void AddSensorDialog::on_createButton() {
  // creo il sensore
  string name = (nameLineEdit->text()).toStdString();
  
  if (sensorTypeComboBox->currentText() == "Temperatura") {
    pm->aggiungi_sensore_temperatura(name);
  }
  else if (sensorTypeComboBox->currentText() == "Umidità") {
    pm->aggiungi_sensore_umidita(name);
  }
  else if (sensorTypeComboBox->currentText() == "Luminosità") {
    pm->aggiungi_sensore_luminosita(name);
  }
  
  // chiudo il dialog
  this->close();
}







