#include "gpsservice.h"

GPSService::GPSService() :
    QObject(), mRecordingTrack(0)
{   

    qRegisterMetaType<QGeoPositionInfo>("QGeoPositionInfo");
    mGPSSource = QGeoPositionInfoSource::createDefaultSource(this);
    mGPSSource->setPreferredPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);

    qDebug() << "Created location source";
    if ( mGPSSource ) {
        connect(mGPSSource,SIGNAL(positionUpdated(QGeoPositionInfo)),this,SLOT(positionUpdated(QGeoPositionInfo)));
        mGPSSource->startUpdates();
        qDebug() << "started gps updates";
    }

    mGPSThread = new QThread();
    mGPSThread->start();
    moveToThread(mGPSThread);
}


/**
  Receives new GPS position
 * @brief GPSService::positionUpdated
 * @param info
 */
void GPSService::positionUpdated(const QGeoPositionInfo &info)
{
    qDebug() << "Position updated:"  << info;
    if ( mRecordingTrack && mRecordingStatus == RECORDING_RUNNING ) {
        qDebug() << "enter new point in recording track";
        // Enter new tracking point in track
        TrackPoint *point = new TrackPoint(mRecordingTrack->getPointCount(), info );
        mRecordingTrack->addPoint(point);
    }
}

void GPSService::startRecording(QString name)
{
    // Check if no track is currently recording
    if ( !mRecordingTrack ) {
        mRecordingTrack = new Track(name,this);
        mRecordingStatus = RECORDING_RUNNING;
    }
}

void GPSService::pauseRecording()
{
    if ( mRecordingTrack ) {
        mRecordingStatus = RECORDING_PAUSED;
    }
}

void GPSService::stopRecording()
{
    if ( mRecordingTrack ) {
        mRecordingStatus = RECORDING_STOPPED;
    }
    emit recordingFinished(mRecordingTrack);
    // Finalise recording and enter it in DB
}
