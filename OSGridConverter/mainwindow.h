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
    QLabel *arcLatitudeResult;
    QLabel *arcLongitudeResult;

};


#endif // MAINWINDOW_H
