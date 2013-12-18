#ifndef TRACKINGDATABASE_H
#define TRACKINGDATABASE_H

#include <QObject>
#include <QDir>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>

#include "../common.h"

#define DATABASE_NAME "/tracking.sqlite"
#define DATABASE_VERSION 1

class TrackingDatabase : public QObject
{
    Q_OBJECT
public:
    explicit TrackingDatabase(QObject *parent = 0);

    bool openDatabase();

private:
    QSqlDatabase mDB;

signals:

public slots:

};

#endif // TRACKINGDATABASE_H
