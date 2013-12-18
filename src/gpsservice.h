#ifndef GPSSERVICE_H
#define GPSSERVICE_H

#include <QObject>
#include <QDebug>
#include <QGeoCoordinate>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>

class GPSService : public QObject
{
    Q_OBJECT
public:
    explicit GPSService(QObject *parent = 0);

private:
    QThread *gpsThread;

signals:

private slots:
    void positionUpdated(const QGeoPositionInfo &info);

};

#endif // GPSSERVICE_H
