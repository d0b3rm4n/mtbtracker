#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QGeoPositionInfo>

#include "trackpoint.h"

class Track : public QObject
{
    Q_OBJECT
public:
    explicit Track(QString name,QObject *parent = 0);
    ~Track();

    int getPointCount();
    TrackPoint* getTrackingPoint(int pos);

    void addPoint(TrackPoint *point);

private:
    QString mName;
    QList<TrackPoint*> *mTrackingPoints;

signals:

public slots:

};

#endif // TRACK_H
