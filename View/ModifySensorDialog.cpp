#include"ModifySensorDialog.h"

ModifySensorDialog::ModifySensorDialog(Modello *_pm, SensoreAstratta *_ps) : pm(_pm), ps(_ps) {
  mainVLayout = new QVBoxLayout;
  setLayout(mainVLayout);
  
  // LINE EDIT
  mainVLayout->addWidget(new QLabel("Insert sensor name (max 15 chars):"));
  
  nameLineEdit = new QLineEdit;
  nameLineEdit->setFixedWidth(170);
  nameLineEdit->setInputMask("Nnnnnnnnnnnnnnn");  // per evitare troppi controlli setto una mask
  mainVLayout->addWidget(nameLineEdit);
  
  // BUTTON
  applyButton = new QPushButton("apply");
  applyButton->setIcon(QIcon::fromTheme("emblem-default"));
  applyButton->setEnabled(false);
  mainVLayout->addWidget(applyButton);
  
  // connessioni
  connect(nameLineEdit, &QLineEdit::textEdited,
          this, &ModifySensorDialog::on_nameEdited);
  connect(applyButton, &QPushButton::clicked,
          this, &ModifySensorDialog::on_applyButton);
  
}

// ---------- PUBLIC SLOTS --------------------------------------------------------------------- //

void ModifySensorDialog::on_nameEdited() {
  if (nameLineEdit->hasAcceptableInput()) {
    applyButton->setEnabled(true);
  }
  else {
    applyButton->setEnabled(false);
  }
}

void ModifySensorDialog::on_applyButton() {
  // modifico il nome del sensore
  string nuovo_nome = (nameLineEdit->text()).toStdString();
  pm->modifica_nome_sensore(nuovo_nome, ps);
  // chiudo il dialog
  this->close();
}







