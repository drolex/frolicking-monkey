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

#include "osgridref.h"
#include "math.h"

#define PI 3.1415926

OSGridRef::OSGridRef()
{
    easting = 0;
    northing = 0;

    latitude = 0;
    longitude = 0;

    //gridcoords.resize(12);
    //gridsquare.resize(2);
}

//where the actual calculation takes place
//converts numerical grid reference
//to decimal longitude and latitude
void OSGridRef::convertOSGridRefToLatLon()
{
    double N = northing;
    double E = easting;

    //bunch of constants
    // Airy 1830 major & minor semi-axes
    double a = 6377563.396;
    double b = 6356256.909;
    // NatGrid scale factor on central meridian
    double F0 = 0.9996012717;
    // NatGrid true origin
    double phi0 = 49*PI/180;
    double lambda0 = -2*PI/180;
    // northing & easting of true origin, metres
    double N0 = -100000;
    double E0 = 400000;
    // eccentricity squared
    double e2 = 1 - (b*b)/(a*a);
    // n, n², n³
    double n = (a-b)/(a+b);
    double n2 = n*n;
    double n3 = n*n*n;       // n, n², n³

    double phi = phi0;
    double M = 0;

    while( N - N0 - M >= 0.00001 )   // ie until < 0.01mm
    {
        phi = (N - N0 - M)/(a*F0) + phi;

        double Ma = (1.0 + n + (5/4)*n2 + (5.0/4.0)*n3) * (phi-phi0);
        double Mb = (3.0*n + 3*n*n + (21.0/8.0)*n3) * sin(phi-phi0) * cos(phi+phi0);
        double Mc = ((15.0/8.0)*n2 + (15.0/8.0)*n3) * sin(2.0*(phi-phi0)) * cos(2.0*(phi+phi0));
        double Md = (35.0/24.0)*n3 * sin(3.0*(phi-phi0)) * cos(3.0*(phi+phi0));
        M = b * F0 * (Ma - Mb + Mc - Md);                // meridional arc
    }

    double cosphi = cos(phi);
    double sinphi = sin(phi);
    double nu = a*F0/sqrt(1.0-e2*sinphi*sinphi);             // nu = transverse radius of curvature
    double rho = a*F0*(1.0-e2)/pow(1.0-e2*sinphi*sinphi, 1.5); // rho = meridional radius of curvature
    double eta2 = nu/rho-1.0;                                      // eta = ?

    double tanphi = tan(phi);
    double tan2phi = tanphi*tanphi;
    double tan4phi = tan2phi*tan2phi;
    double tan6phi = tan4phi*tan2phi;
    double secphi = 1.0/cosphi;
    double nu3 = nu*nu*nu;
    double nu5 = nu3*nu*nu;
    double nu7 = nu5*nu*nu;
    double VII = tanphi/(2.0*rho*nu);
    double VIII = tanphi/(24.0*rho*nu3)*(5.0+3.0*tan2phi+eta2-9.0*tan2phi*eta2);
    double IX = tanphi/(720.0*rho*nu5)*(61.0+90.0*tan2phi+45.0*tan4phi);
    double X = secphi/nu;
    double XI = secphi/(6.0*nu3)*(nu/rho+2*tan2phi);
    double XII = secphi/(120.0*nu5)*(5.0+28.0*tan2phi+24.0*tan4phi);
    double XIIA = secphi/(5040.0*nu7)*(61.0+662.0*tan2phi+1320.0*tan4phi+720.0*tan6phi);

    double dE = (E-E0), dE2 = dE*dE, dE3 = dE2*dE, dE4 = dE2*dE2, dE5 = dE3*dE2, dE6 = dE4*dE2, dE7 = dE5*dE2;
    phi = phi - VII*dE2 + VIII*dE4 - IX*dE6;
    double lambda = lambda0 + X*dE - XI*dE3 + XII*dE5 - XIIA*dE7;

    latitude = phi * 180.0 / PI;
    longitude = lambda * 180.0 / PI;
}

//split the numerical OS grid (e.g. 31233456)
//in eastings and northings
void OSGridRef::splitGridCoords()
{
    QString e, n;

    //split depending on the size of the string
    if ( gridcoords.length() == 8 )
    {
        gridsquare = gridcoords;
        gridsquare.truncate(2);

        e = gridcoords.mid(2,3);
        n = gridcoords.mid(5,3);

    }

    if ( gridcoords.length() == 10 )
    {
        gridsquare = gridcoords;
        gridsquare.truncate(2);

        e = gridcoords.mid(2,4);
        n = gridcoords.mid(6,4);
    }

    if ( gridcoords.length() == 12 )
    {
        gridsquare = gridcoords;
        gridsquare.truncate(2);

        e = gridcoords.mid(2,5);
        n = gridcoords.mid(7,5);
    }

    bool ok;
    easting = e.toInt(&ok, 10);
    northing = n.toInt(&ok, 10);

    // append numeric part of references to grid index:
    // normalise to 1m grid, rounding up to centre of grid square:
    switch(gridcoords.length())
    {
    case 12:
        easting += grideasting * 100000;
        northing += gridnorthing * 100000;
        break;
    case 10:
        easting = easting * 10 + grideasting * 100000 + 5;
        northing = northing * 10 + gridnorthing * 100000 + 5;
        break;
    case 8:
        easting = easting * 100 + grideasting * 100000 + 50;
        northing = northing * 100 + gridnorthing * 100000 + 50;
        break;
    case 6:
        easting = easting * 1000 + grideasting * 100000 + 500;
        northing = northing * 1000 + gridnorthing * 100000 + 500;
        break;
    }

}

//convert grid letters to numerical
//e.g. SJ123456 -> 31233456
void OSGridRef::parseRefToNumeric()
{
    //take first 2 characters e.g. "SJ"
    //converts to numbers
    //A->0, B->1 ... H->8
    //I is removed
    //J->9 ... Z->25

    int n1 = gridcoords.at(0).toLatin1() - 65;
    int n2 = gridcoords.at(1).toLatin1() - 65;

    if( n1 > 8 )
    {
        n1--;
    }

    if( n2 > 8 )
    {
        n2--;
    }

    // convert grid letters into 100km-square indexes from false origin (grid square SV):
    grideasting = ((n1-2)%5)*5 + (n2%5);
    gridnorthing = (19 - floor(double(n1)/5)*5) - floor(double(n2)/5);
}

//sets/gets
void OSGridRef::setLatitude(double lat)
{
    latitude = lat;
}

void OSGridRef::setLongitude(double lon)
{
    longitude = lon;
}

void OSGridRef::setEasting(int eas)
{
    easting = eas;
}

void OSGridRef::setNorthing(int nor)
{
    northing = nor;
}

void OSGridRef::setGridCoords(QString gc)
{
    gridcoords = gc;
}


double OSGridRef::getLatitude()
{
    return latitude;
}

double OSGridRef::getLongitude()
{
    return longitude;
}

int OSGridRef::getEasting()
{
    return easting;
}

int OSGridRef::getNorthing()
{
    return northing;
}
