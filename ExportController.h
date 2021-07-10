#ifndef EXPORTCONTROLLER_H
#define EXPORTCONTROLLER_H

#include <QObject>
#include <QFile>
#include <QDir>

#include "misc.h"

class ExportController : public QObject
{
    Q_OBJECT
public:
    explicit ExportController(QObject *parent = nullptr);

    Q_INVOKABLE void exportDatabase();

signals:

};

#endif // EXPORTCONTROLLER_H
