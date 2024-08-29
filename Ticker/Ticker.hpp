#ifndef TICKER_HPP
#define TICKER_HPP

#include <QObject>
#include <QThread>

class Ticker : public QThread
{
    Q_OBJECT
public:
    explicit Ticker(QObject *parent = nullptr);
    ~Ticker();

signals:
    void ticked();

protected:
    void run() override;

private slots:
    void onTick();

public slots:
    void onAboutToQuit();
};

#endif // TICKER_HPP
