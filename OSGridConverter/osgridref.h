#ifndef OSGRIDREF_H
#define OSGRIDREF_H

#include <QString>

class OSGridRef
{
public:
    OSGridRef();
    void convertOSGridRefToLatLon();
    void splitGridCoords();

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

    double latitude;
    double longitude;
};

#endif // OSGRIDREF_H
