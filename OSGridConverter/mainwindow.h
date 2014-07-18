#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include "osgridref.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();

public slots:
    void convert();

private:
    QPushButton *convertButton;
    QLineEdit *gridCoordsLineEdit;
    OSGridRef gridRef;
    QLabel *latitudeResult;
    QLabel *longitudeResult;

};


#endif // MAINWINDOW_H
