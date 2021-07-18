#include "./header/Path.h"

Path::Path(QObject *parent) : QObject(parent)
  , m_pathId(-1)
  , m_name("")
{

}

Path::Path(int pathId, QString name)
{
    setPathId(pathId);
    setName(name);
}

int Path::pathId() const
{
    return m_pathId;
}

QString Path::name() const
{
    return m_name;
}

void Path::setPathId(int pathId)
{
    if (m_pathId == pathId)
        return;

    m_pathId = pathId;
    emit pathIdChanged(m_pathId);
}

void Path::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}
