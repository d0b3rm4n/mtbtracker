#include "maincontroller.h"

MainController::MainController(QObject *parent) :
    QObject(parent)
{
    // Create TrackingDatabase object for storing and loading of info
    mTrackingDatabase = new TrackingDatabase(this);
    // Open tracking db
    mTrackingDatabase->openDatabase();

    // Create GPS tracking service
    mGPSService = new GPSService(this);
}
