#include "trackpoint.h"

TrackPoint::TrackPoint(const QGeoPositionInfo &parent) :
    QGeoPositionInfo(parent)
{
}

TrackPoint::TrackPoint(int id, const QGeoPositionInfo &parent) :
    QGeoPositionInfo(parent)
{
    mID = id;
}

int TrackPoint::getID()
{
    return mID;
}
