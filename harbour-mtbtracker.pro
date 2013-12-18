# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TARGET = harbour-mtbtracker

CONFIG += sailfishapp

QT += positioning sql

SOURCES += src/harbour-mtbtracker.cpp \
    src/gpsservice.cpp \
    src/db/trackingdatabase.cpp \
    src/maincontroller.cpp \
    src/db/track.cpp \
    src/db/trackpoint.cpp

OTHER_FILES += qml/harbour-mtbtracker.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/harbour-mtbtracker.spec \
    rpm/harbour-mtbtracker.yaml \
    harbour-mtbtracker.desktop

HEADERS += \
    src/gpsservice.h \
    src/db/trackingdatabase.h \
    src/maincontroller.h \
    src/common.h \
    src/db/track.h \
    src/db/trackpoint.h

