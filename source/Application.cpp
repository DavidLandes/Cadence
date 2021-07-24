#include "./header/Application.h"

Application::Application(QObject *parent) : QObject(parent)
{

}

double Application::getDuration(QDateTime time1, QDateTime time2)
{
    double duration = 0.0;

    if (time1 > time2)
    {
        duration = time2.time().msecsTo(time1.time());
    }
    else if (time1 < time2)
    {
        duration = time1.time().msecsTo(time2.time());
    }
    return duration;
}
