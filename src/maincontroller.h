#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QQuickView>

#include "common.h"
#include "gpsservice.h"
#include "db/trackingdatabase.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QQuickView &view, QObject *parent = 0);

    void makeConnections();

private:
    QQuickView &mQuickView;
    TrackingDatabase *mTrackingDatabase;
    GPSService *mGPSService;


signals:

public slots:

};

#endif // MAINCONTROLLER_H
