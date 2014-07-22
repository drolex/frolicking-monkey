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

#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
