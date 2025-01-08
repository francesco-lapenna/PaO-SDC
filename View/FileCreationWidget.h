#ifndef FILECREATIONWIDGET_H
#define FILECREATIONWIDGET_H

#include<QWidget>
#include"MainWindow.h"
#include"../Headers/Modello.h"
#include<QFrame>
#include<QGridLayout>
#include<QLineEdit>
#include<QLabel>
#include<QPushButton>
#include<QFileDialog>

class MainWindow;

class FileCreationWidget : public QWidget
{
  Q_OBJECT
private:
  MainWindow *pmw;
  Modello *pm;
  QVBoxLayout *mainVLayout;       // layout principale contenente un
  QFrame *externalFrame;          // frame contenente un
  QGridLayout *internalGLayout;   // grid layout
  QLineEdit *fileNameLineEdit;
  QLabel *folderLabel;
  QPushButton *browseButton;
  QHBoxLayout *createHLayout;
  QPushButton *createButton;
  string folder_path;
  string file_name;
public slots:
  void on_browseButton();
  void on_fileNameEdited(const QString& text);
  void on_createButton();
public:
  FileCreationWidget(MainWindow *_pmw, Modello* _pm, QWidget *parent = nullptr);
};

#endif // FILECREATIONWIDGET_H
