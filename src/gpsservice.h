#ifndef GPSSERVICE_H
#define GPSSERVICE_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QGeoCoordinate>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>

#include "db/track.h"
#include "db/trackpoint.h"

class GPSService : public QObject
{
    Q_OBJECT

    enum RecordingStatus {RECORDING_STOPPED,RECORDING_RUNNING,RECORDING_PAUSED};

public:
    explicit GPSService();

public slots:
    void startRecording(QString name);
    void pauseRecording();
    void stopRecording();

private:
    // Thread for this object
    QThread *mGPSThread;
    // GPS Positioning Source
    QGeoPositionInfoSource *mGPSSource;

    // Track object for currently recording track
    Track *mRecordingTrack;
    // Recording active
    RecordingStatus mRecordingStatus;


signals:
    void recordingFinished(Track *track);

private slots:
    void positionUpdated(const QGeoPositionInfo &info);

};

#endif // GPSSERVICE_H
