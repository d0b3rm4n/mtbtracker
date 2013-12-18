#include "trackingdatabase.h"

TrackingDatabase::TrackingDatabase(QObject *parent) :
    QObject(parent)
{



}

bool TrackingDatabase::openDatabase()
{
    /* Create database if not existent
     * open if it exists */
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) +
            DATABASE_NAME;

    qDebug() << "Trying to open database: " << dbPath;
    QDir dir;
    dir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    mDB = QSqlDatabase::addDatabase("QSQLITE");
    mDB.setDatabaseName(dbPath);

    // Open database and check status
    bool dbOpen = mDB.open();
    if ( !dbOpen ) {
        return false;
    }

    // Get tables from db and create if some are nonexistent
    QStringList dbTables = mDB.tables(QSql::Tables);
    // Track table is missing create it
    if ( !dbTables.contains("dbinfo") ) {
        QSqlQuery query;
        bool retVal = query.exec( "CREATE TABLE dbinfo"
                                  "(id integer primary key, "
                                  " dbversion integer, "
                                  " creationdate text)");
        if ( retVal ) {
            qDebug() << "Database table dbinfo created successfully";
        } else {
            qDebug() << "Database table dbinfo not created";
            return false;
        }
        // Create version table entry
        retVal = query.exec("INSERT INTO dbinfo (id, dbversion, creationdate) VALUES (0," + QString::number(DATABASE_VERSION) +
                   ", \""  + QDateTime::currentDateTime().toString(Qt::ISODate) +"\" )");
        if ( !retVal ) {
            return false;
        }
    }
    if ( !dbTables.contains("tracks") ) {
        QSqlQuery query;
        bool retVal = query.exec("CREATE TABLE tracks"
                                 "( id integer primary key, "
                                 "  trackname text, "
                                 "  finished integer, "
                                 "  date text )");
        if ( retVal ) {
            qDebug() << "Database table tracks created successfully";
        } else {
            qDebug() << "Database table tracks not created";
            return false;
        }
    }

    if ( !dbTables.contains("trackingdata") ) {
        QSqlQuery query;
        bool retVal = query.exec("CREATE TABLE trackingdata"
                                 "( globalid integer primary key AUTOINCREMENT, "
                                 "  trackid integer, "
                                 "  pointid integer, "
                                 "  longitude real,"
                                 "  latitude real,"
                                 "  altitude real,"
                                 "  groundspeed real,"
                                 "  verticalaccuracy integer,"
                                 "  horizontalaccuracy integer"
                                 ")");
        if ( retVal ) {
            qDebug() << "Database table trackingdata created successfully";
        } else {
            qDebug() << "Database table trackingdata not created";
            return false;
        }
    }
    return true;
}


/**
  Saves track, if already in database updates it
 * @brief TrackingDatabase::saveTrack
 * @param track
 */
void TrackingDatabase::saveTrack(Track *track)
{
    qDebug() << "Writing track to SQL database";
    int trackID = getNewTrackID();
    // iterate over all waypoints and save the track
    for ( int i = 0; i < track->getPointCount(); i++ ) {
        QSqlQuery query;
        TrackPoint *point = track->getTrackingPoint(i);
        bool retVal = query.prepare("INSERT INTO trackingdata (trackid, pointid, "
                      "longitude, latitude, altitude, groundspeed, "
                      "verticalaccuracy, horizontalaccuracy ) "
                      "VALUES ("
                      ":trackid, :pointid, "
                      ":longitude, :latitude, :altitude, :groundspeed, "
                      ":verticalaccuracy, :horizontalaccuracy )");
        qDebug() << "Query prepared: " << retVal;
        query.bindValue(":trackid", trackID );
        query.bindValue(":pointid", point->getID() );
        query.bindValue(":longitude", point->coordinate().longitude());
        query.bindValue(":latitude", point->coordinate().latitude());
        query.bindValue(":altitude", point->coordinate().altitude());
        query.bindValue(":groundspeed", point->attribute(QGeoPositionInfo::GroundSpeed));
        query.bindValue(":verticalaccuracy", point->attribute(QGeoPositionInfo::VerticalAccuracy));
        query.bindValue(":horizontalaccuracy", point->attribute(QGeoPositionInfo::HorizontalAccuracy));

        qDebug() << query.lastQuery();

        // Execute the query with all values
        query.exec();
    }
    delete(track);
}

int TrackingDatabase::getNewTrackID()
{
    // FIXME
    return 1;
}
