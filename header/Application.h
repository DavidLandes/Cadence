#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QDateTime>

class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = nullptr);

    Q_INVOKABLE double getDuration(QDateTime time1, QDateTime time2);

signals:

};

#endif // APPLICATION_H
