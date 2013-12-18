#ifndef TRACKPOINT_H
#define TRACKPOINT_H

#include <QGeoPositionInfo>

class TrackPoint : public QGeoPositionInfo
{
public:
    explicit TrackPoint(const QGeoPositionInfo &parent);
    TrackPoint(int id, const QGeoPositionInfo &parent);

    int getID();

private:
    int mID;

signals:

public slots:

};

#endif // TRACKPOINT_H
