#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QGuiApplication>
#include <QQuickView>
#include <sailfishapp.h>
#include "maincontroller.h"


int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc,argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    app->setOrganizationName("mtbtracker");
    app->setApplicationDisplayName("MTBTracker");
    app->setApplicationName("mtbtracker");
    view->setSource(SailfishApp::pathTo("qml/harbour-mtbtracker.qml"));
    view->show();

    MainController *controller = new MainController();

    return QGuiApplication::exec();
}

