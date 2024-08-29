#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

#include "Ticker.hpp"

Ticker::Ticker(QObject *parent)
    : QThread{parent}
{
    qInfo() << this << "Constructed";
}

Ticker::~Ticker()
{
    qInfo() << this << "Destroyed";
}

void Ticker::run()
{
    QTimer timer;
    timer.setTimerType(Qt::TimerType::PreciseTimer);
    timer.setInterval(40);
    timer.start();
    this->connect(&timer, &QTimer::timeout, this, &Ticker::onTick);
    this->exec();
    timer.stop();
}

void Ticker::onTick()
{
    emit ticked();
}

void Ticker::onAboutToQuit()
{
    this->quit();
    this->wait();
}
