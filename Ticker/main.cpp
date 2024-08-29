#include <QCoreApplication>
#include <QDebug>
#include <QObject>

#include "Ticker.hpp"

quint16 c = 0;
void tickerTicked()
{
    qInfo() << ++c;

    if (c == 10) {
        QCoreApplication::quit();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // starting the timer in a different thread
    Ticker ticker;
    QObject::connect(&ticker, &Ticker::ticked, &tickerTicked);
    QObject::connect(&ticker, &QThread::finished, &ticker, &QObject::deleteLater);
    QObject::connect(&a, &QCoreApplication::aboutToQuit, &ticker, &Ticker::onAboutToQuit);
    ticker.start();

    return a.exec();
}
