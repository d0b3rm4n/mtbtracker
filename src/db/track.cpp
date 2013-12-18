#include "track.h"

Track::Track(QString name, QObject *parent) :
    QObject(parent), mName(name)
{
    mTrackingPoints = new QList<TrackPoint*>();
}


Track::~Track()
{
    if ( mTrackingPoints ) {
        foreach (TrackPoint *info, *mTrackingPoints) {
            delete(info);
        }
    }
}

int Track::getPointCount()
{
    return mTrackingPoints->size();
}

TrackPoint* Track::getTrackingPoint(int pos)
{
    if ( pos < mTrackingPoints->size() ) {
        return mTrackingPoints->at(pos);
    } else {
        return 0;
    }
}

/** Add point to list of trackpoints
 * @brief Track::addPoint
 * @param point
 */
void Track::addPoint(TrackPoint *point)
{
    mTrackingPoints->append(point);
}
