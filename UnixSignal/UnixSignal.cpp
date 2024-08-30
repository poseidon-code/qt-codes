#include <QDebug>
#include <QList>
#include <QObject>
#include <QSocketNotifier>

#include <csignal>
#include <sys/socket.h>
#include <unistd.h>

#include "UnixSignal.hpp"

int UnixSignal::sp[2];

UnixSignal::UnixSignal(QObject *parent)
{
    ::socketpair(AF_UNIX, SOCK_STREAM, 0, UnixSignal::sp);
    this->notifier = new QSocketNotifier(UnixSignal::sp[1], QSocketNotifier::Read);
    connect(this->notifier, &QSocketNotifier::activated, this, &UnixSignal::onActivated);
    this->notifier->setEnabled(true);

    qInfo() << this << "Constructed";
}

UnixSignal::~UnixSignal()
{
    delete this->notifier;
    ::close(UnixSignal::sp[0]);
    ::close(UnixSignal::sp[1]);

    qInfo() << this << "Destructed";
}

void UnixSignal::watch(int signal)
{
    if (this->watchedSignals.contains(signal)) {
        return;
    }

    struct sigaction sigact;
    sigact.sa_handler = handler;
    sigact.sa_flags = 0;
    ::sigemptyset(&sigact.sa_mask);
    sigact.sa_flags |= SA_RESTART;
    ::sigaction(signal, &sigact, NULL);

    this->watchedSignals.append(signal);
}

void UnixSignal::handler(int signal)
{
    ::write(UnixSignal::sp[0], &signal, sizeof(signal));
}

void UnixSignal::onActivated(int spfd)
{
    int signal;
    ::read(spfd, &signal, sizeof(signal));
    emit this->signaled(signal);
}
