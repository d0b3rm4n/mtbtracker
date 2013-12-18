#include "maincontroller.h"

MainController::MainController(QQuickView &view, QObject *parent) :
    QObject(parent), mQuickView(view)
{
    // Create TrackingDatabase object for storing and loading of info
    mTrackingDatabase = new TrackingDatabase(this);
    // Open tracking db
    mTrackingDatabase->openDatabase();

    // Create GPS tracking service
    mGPSService = new GPSService();
}

void MainController::makeConnections()
{
    connect(mGPSService,SIGNAL(recordingFinished(Track*)),mTrackingDatabase,SLOT(saveTrack(Track*)));

    // Qml<->C++ Connections
    QObject *item = (QObject *)mQuickView.rootObject();
    connect(item,SIGNAL(startRecording(QString)), mGPSService,SLOT(startRecording(QString)));
    connect(item,SIGNAL(stopRecording()), mGPSService,SLOT(stopRecording()));
}
