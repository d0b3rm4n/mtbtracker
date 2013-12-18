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
                                 "( id integer primary key AUTOINCREMENT, "
                                 "  trackid integer, "
                                 "  longitude real,"
                                 "  latitude real,"
                                 "  height real,"
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
