/**************************************************************/
/* Ordnance Survey Grid Reference coordinates conversion      */
/*                                                            */
/* Original java code by Chris Veness                         */
/* http://www.movable-type.co.uk/scripts/latlong-gridref.html */
/*                                                            */
/* Licensed under CC BY 3.0                                   */
/* http://creativecommons.org/licenses/by/3.0/                */
/*                                                            */
/* (c) Chris Veness 2005-2014                                 */
/* (c) Alexandre Bourdeu 2014                                 */
/**************************************************************/

/**************************************************************/
/* Conversion of OS Grid reference coordinates                */
/* to latitude and longitude                                  */
/**************************************************************/

#include "mainwindow.h"
#include "osgridref.h"

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>

MainWindow::MainWindow()
{
    //style
    setStyleSheet(" QGroupBox { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF); \
                        border: 2px solid gray; \
                        border-radius: 5px; \
                        margin-top: 1ex; }\
                    QGroupBox::title { subcontrol-origin: margin; \
                        subcontrol-position: top center; \
                        padding: 0 3px;} \
                    QLineEdit { border: 2px solid gray; \
                        border-radius: 5px; \
                        padding: 0 8px; \
                        background: #CFECEC; \
                        selection-background-color: darkgray; } \
                    QPushButton { border: 2px solid #8f8f91; \
                        border-radius: 5px; \
                        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF); \
                        min-width: 80px; \
                        min-height: 30px; \
                        font-weight: bold; \
                        font-size: 12pt; } \
                    QPushButton:pressed { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa);} \
                    QPushButton:flat { border: none;} \
                    QPushButton:default { border-color: navy; } ");


    //OS Grid coordinates input
    QGroupBox *gridCoordsGroup = new QGroupBox(tr("OS Grid Coordinates"));
    QLabel *gridCoordsLabel = new QLabel(tr("Grid Coordinates:"));

    gridCoordsLineEdit = new QLineEdit;
    gridCoordsLineEdit->setPlaceholderText("e.g. SK123457890");
    gridCoordsLineEdit->setFocus();

    //Conversion button
    convertButton = new QPushButton("Convert");
    connect(convertButton, SIGNAL(clicked()), this, SLOT(convert()));

    //Latitude/longitude output
    QGroupBox *latLonGroup = new QGroupBox(tr("Latitude and longitude"));
    QLabel *latitudeLabel = new QLabel(tr("Latitude:"));
    QLabel *longitudeLabel = new QLabel(tr("Longitude:"));

    latitudeResult = new QLabel("-");
    longitudeResult = new QLabel("-");

    //Layout
    QGridLayout *gridCoordsLayout = new QGridLayout;
    gridCoordsLayout->addWidget(gridCoordsLabel, 0, 0);
    gridCoordsLayout->addWidget(gridCoordsLineEdit, 0, 1);
    gridCoordsGroup->setLayout(gridCoordsLayout);

    QGridLayout *latLonLayout = new QGridLayout;
    latLonLayout->addWidget(latitudeLabel, 0, 0);
    latLonLayout->addWidget(latitudeResult, 0, 1);
    latLonLayout->addWidget(longitudeLabel, 1, 0);
    latLonLayout->addWidget(longitudeResult, 1, 1);
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
    QString string = gridCoordsLineEdit->text();
    //remove spaces
    string = string.simplified();
    string = string.replace(" ","");

    //to upper-case
    string = string.toUpper();

    bool inputisright = 1;
    //check non empty string
    if( string.isEmpty() == 1 ) inputisright = 0;
    else
    {
        //check 2 first characters are letters
        if( string.at(0).isUpper() == 0 ) inputisright = 0;
        if( string.at(1).isUpper() == 0 ) inputisright = 0;

        //check length of string is 6, 8, 10 or 12
        if( string.length() != 6 && string.length() != 8 && string.length() != 10 && string.length() != 12 )
        {
            inputisright = 0;
        }

        //check other characters are numbers
        for( int i = 2; i < string.length() ; i++ )
        {
            if( string.at(i).isNumber() == 0 ) inputisright = 0;
        }
    }

    if( inputisright == 0 )
    {
        latitudeResult->setText("NaN");
        longitudeResult->setText("NaN");
    }
    else
    {
        gridRef.setGridCoords(string);
        gridRef.parseRefToNumeric();
        gridRef.splitGridCoords();
        gridRef.convertOSGridRefToLatLon();

        QString latText = QString::number(gridRef.getLatitude());
        QString lonText = QString::number(gridRef.getLongitude());

        latitudeResult->setText(latText);
        longitudeResult->setText(lonText);
    }



    /*QString latText = QString::number(gridRef.getLatitude());
    QString lonText = QString::number(gridRef.getLongitude());

    if( gridRef.getRightInput() == 0 )
    {
        latitudeResult->setText("NaN");
        longitudeResult->setText("NaN");
    }
    else
    {
        latitudeResult->setText(latText);
        longitudeResult->setText(lonText);
    }*/
}
