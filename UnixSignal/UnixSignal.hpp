#pragma once

#include <QList>
#include <QObject>
#include <QSocketNotifier>

class UnixSignal : public QObject
{
    Q_OBJECT

public:
    explicit UnixSignal(QObject *parent = nullptr);
    ~UnixSignal();

    void watch(int signal);
    static void handler(int signal);

signals:
    void signaled(int signal);

private slots:
    void onActivated(int spfd);

private:
    QList<int> watchedSignals;
    QSocketNotifier *notifier;
    static int sp[2];
};
