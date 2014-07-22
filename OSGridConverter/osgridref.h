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

#ifndef OSGRIDREF_H
#define OSGRIDREF_H

#include <QString>

class OSGridRef
{
public:
    OSGridRef();
    void convertOSGridRefToLatLon();
    void splitGridCoords();
    void parseRefToNumeric();

    void setLatitude(double lat);
    void setLongitude (double lon);
    void setEasting (int eas);
    void setNorthing(int nor);
    void setGridCoords(QString gc);

    double getLatitude();
    double getLongitude();
    int getEasting();
    int getNorthing();

private:
    QString gridcoords;
    QString gridsquare;

    int easting;
    int northing;

    int grideasting;
    int gridnorthing;

    double latitude;
    double longitude;
};

#endif // OSGRIDREF_H
