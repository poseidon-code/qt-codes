#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

#include "UnixSignal.hpp"

#include <csignal>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTimer::singleShot(10000, &app, &QCoreApplication::quit);

    UnixSignal signalWatcher;
    signalWatcher.watch(SIGINT);
    signalWatcher.watch(SIGTERM);
    QObject::connect(&signalWatcher, &UnixSignal::signaled, &app, &QCoreApplication::quit);

    app.exec();

    qInfo() << "finished";

    return 0;
}
