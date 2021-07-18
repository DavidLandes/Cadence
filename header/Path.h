#ifndef PATH_H
#define PATH_H

#include <QObject>

class Path : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(int pathId READ pathId WRITE setPathId NOTIFY pathIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    explicit Path(QObject *parent = nullptr);
    Path(int pathId, QString name);

    int pathId() const;
    QString name() const;

public slots:
    void setPathId(int pathId);
    void setName(QString name);

signals:
    void pathIdChanged(int pathId);
    void nameChanged(QString name);

private:
    int m_pathId;
    QString m_name;
};

#endif // PATH_H
