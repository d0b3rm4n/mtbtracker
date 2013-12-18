#include "gpsservice.h"

GPSService::GPSService(QObject *parent) :
    QObject(parent)
{   
    qRegisterMetaType<QGeoPositionInfo>("QGeoPositionInfo");
    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
    source->setPreferredPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);
    QGeoPositionInfoSource::PositioningMethods methods = source->supportedPositioningMethods();

    qDebug() << "Created location source";
    if ( source ) {
        connect(source,SIGNAL(positionUpdated(QGeoPositionInfo)),this,SLOT(positionUpdated(QGeoPositionInfo)));
        source->startUpdates();
        qDebug() << "started gps updates";
    }
}


/**
  Receives new GPS position
 * @brief GPSService::positionUpdated
 * @param info
 */
void GPSService::positionUpdated(const QGeoPositionInfo &info)
{
    qDebug() << "Position updated:"  << info;
}
