#ifndef OSGRIDREF_H
#define OSGRIDREF_H

class OSGridRef
{
public:
    OSGridRef();
    void convertOSGridRefToLatLon();

private:
    int easting;
    int northing;

    double latitude;
    double longitude;
};

#endif // OSGRIDREF_H
