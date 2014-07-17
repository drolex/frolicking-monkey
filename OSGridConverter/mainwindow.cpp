#include "mainwindow.h"
#include "osgridref.h"

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>

MainWindow::MainWindow()
{

    //OS Grid coordinates input
    QGroupBox *gridCoordsGroup = new QGroupBox(tr("OS Grid Coordinates"));
    QLabel *gridCoordsLabel = new QLabel(tr("Grid Square:"));

    QLineEdit *gridCoordsLineEdit = new QLineEdit;
    gridCoordsLineEdit->setPlaceholderText("Placeholder Text");
    gridCoordsLineEdit->setFocus();

    //Conversion button
    convertButton = new QPushButton("Convert");
    connect(convertButton, SIGNAL(clicked()),this, SLOT(convert()));


    //Latitude/longitude output
    QGroupBox *latLonGroup = new QGroupBox(tr("Latitude and longitude"));
    QLabel *latitudeLabel = new QLabel(tr("Latitude:"));
    QLabel *longitudeLabel = new QLabel(tr("Longitude:"));

    QLineEdit *latitudeLineEdit = new QLineEdit;
    latitudeLineEdit->setPlaceholderText("Placeholder Text");
    latitudeLineEdit->setFocus();
    QLineEdit *longitudeLineEdit = new QLineEdit;
    longitudeLineEdit->setPlaceholderText("Placeholder Text");
    longitudeLineEdit->setFocus();

    //Layout
    QGridLayout *gridCoordsLayout = new QGridLayout;
    gridCoordsLayout->addWidget(gridCoordsLabel, 0, 0);
    gridCoordsLayout->addWidget(gridCoordsLineEdit, 0, 1);
    gridCoordsGroup->setLayout(gridCoordsLayout);

    QGridLayout *latLonLayout = new QGridLayout;
    latLonLayout->addWidget(latitudeLabel, 0, 0);
    latLonLayout->addWidget(latitudeLineEdit, 0, 1);
    latLonLayout->addWidget(longitudeLabel, 1, 0);
    latLonLayout->addWidget(longitudeLineEdit, 1, 1);
    latLonGroup->setLayout(latLonLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(gridCoordsGroup, 0, 0);
    layout->addWidget(convertButton, 1, 0);
    layout->addWidget(latLonGroup, 2, 0);
    setLayout(layout);

    setWindowTitle(tr("OS Grid Conversion"));
}

void MainWindow::convert()
{
    OSGridRef gridRef;

    gridRef.convertOSGridRefToLatLon();
}
