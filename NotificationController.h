#ifndef NOTIFICATIONCONTROLLER_H
#define NOTIFICATIONCONTROLLER_H

#include <QObject>

#include "NotificationData.h"

class NotificationController : public QObject
{
    Q_OBJECT
public:
    explicit NotificationController(QObject *parent = nullptr);
    ~NotificationController();

    Q_PROPERTY(QList<NotificationData*> alertQueue READ alertQueue NOTIFY alertQueueChanged)
    Q_PROPERTY(QList<NotificationData*> popupQueue READ popupQueue NOTIFY popupQueueChanged)
    Q_PROPERTY(NotificationData* currentAlert READ currentAlert NOTIFY currentAlertChanged)
    Q_PROPERTY(NotificationData* currentPopup READ currentPopup NOTIFY currentPopupChanged)

    Q_INVOKABLE void createNotification(int notification, int type, QObject* data=nullptr);
    Q_INVOKABLE void removeNotification(NotificationData* notification);

    QList<NotificationData*> alertQueue() const;
    QList<NotificationData*> popupQueue() const;
    NotificationData* currentAlert() const;
    NotificationData* currentPopup() const;

public slots:
    void setAlertQueue(QList<NotificationData*> alertQueue);
    void setPopupQueue(QList<NotificationData*> popupQueue);
    void setCurrentAlert(NotificationData* currentAlert);
    void setCurrentPopup(NotificationData* currentPopup);

signals:
    void alertQueueChanged(QList<NotificationData*> alertQueue);
    void popupQueueChanged(QList<NotificationData*> popupQueue);
    void currentAlertChanged(NotificationData* currentAlert);
    void currentPopupChanged(NotificationData* currentPopup);

private:
    void addAlert(NotificationData* alert);
    void addPopup(NotificationData* popup);

    void removeAlert(NotificationData* alert);
    void removePopup(NotificationData* popup);

    QList<NotificationData*> m_alertQueue;
    QList<NotificationData*> m_popupQueue;
    NotificationData* m_currentAlert;
    NotificationData* m_currentPopup;
};

#endif // NOTIFICATIONCONTROLLER_H
