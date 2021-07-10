#include "ExportController.h"

#include <QDebug>

ExportController::ExportController(QObject *parent) : QObject(parent)
{

}

void ExportController::exportDatabase()
{
    QFile* from = new QFile(DATABASE_PATH);
    from->setPermissions(QFile::Permission::ExeUser | QFile::Permission::ReadUser | QFile::Permission::WriteUser);
    qDebug() << (from->exists() ? "FROM FILE EXISTS" : "FROM FILE NOT EXISTS");
    QDir* to = new QDir(QString(EXTERNAL_STORAGE_PATH) + "/cadence_exports/");
    qDebug() << (to->exists() ? "TO DIR EXISTS" : "TO DIR NOT EXISTS");
    if (!to->exists())
    {
        qDebug() << (to->mkpath(".") ? to->absolutePath() + "mk path Success" : to->absolutePath() + "mk path Fail");
    }
    qDebug() << to->entryList();
    // TODO: Figure out why I can't copy files to external storage.

    qDebug() << (from->copy(to->absolutePath() + "/CadenceGps") ? "Export Success" : "Export Failed: " + from->errorString());
//    qDebug() << (from->copy("./copyDb") ? "Export Success" : "Export Failed: " + from->errorString());
}
