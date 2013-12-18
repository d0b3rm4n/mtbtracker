#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "common.h"
#include "gpsservice.h"
#include "db/trackingdatabase.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = 0);

private:
    TrackingDatabase *mTrackingDatabase;
    GPSService *mGPSService;


signals:

public slots:

};

#endif // MAINCONTROLLER_H
