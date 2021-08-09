#include "./header/NotificationController.h"

#include <QDebug>

NotificationController::NotificationController(QObject *parent) : QObject(parent)
  , m_alertQueue()
  , m_popupQueue()
  , m_currentAlert()
  , m_currentPopup()
{

}

NotificationController::~NotificationController()
{
    for (NotificationData* item : m_popupQueue)
    {
        delete item;
    }
    for (NotificationData* item : m_alertQueue)
    {
        delete item;
    }
}

QList<NotificationData *> NotificationController::alertQueue() const
{
    return m_alertQueue;
}

QList<NotificationData *> NotificationController::popupQueue() const
{
    return m_popupQueue;
}

NotificationData *NotificationController::currentAlert() const
{
    return m_currentAlert;
}

NotificationData *NotificationController::currentPopup() const
{
    return m_currentPopup;
}

NotificationData::Response NotificationController::lastPopupResponse() const
{
    return m_lastPopupResponse;
}

void NotificationController::setAlertQueue(QList<NotificationData *> alertQueue)
{
    if (m_alertQueue == alertQueue)
        return;

    m_alertQueue = alertQueue;
    emit alertQueueChanged(m_alertQueue);
}

void NotificationController::setPopupQueue(QList<NotificationData *> popupQueue)
{
    if (m_popupQueue == popupQueue)
        return;

    m_popupQueue = popupQueue;
    emit popupQueueChanged(m_popupQueue);
}

void NotificationController::setCurrentAlert(NotificationData *currentAlert)
{
    if (m_currentAlert == currentAlert)
        return;

    m_currentAlert = currentAlert;
    emit currentAlertChanged(m_currentAlert);
}

void NotificationController::setCurrentPopup(NotificationData *currentPopup)
{
    if (m_currentPopup == currentPopup)
        return;

    m_currentPopup = currentPopup;
    emit currentPopupChanged(m_currentPopup);
}

void NotificationController::setLastPopupResponse(NotificationData::Response lastPopupResponse)
{
    if (m_lastPopupResponse == lastPopupResponse)
        return;

    m_lastPopupResponse = lastPopupResponse;
    emit lastPopupResponseChanged(m_lastPopupResponse);
}

void NotificationController::addAlert(NotificationData *alert)
{
    if (alert == nullptr)
    {
        qDebug() << "NotificationController::addAlert() - Cannot add alert.";
    }

    m_alertQueue.append(alert);
    emit alertQueueChanged(m_alertQueue);

    if (!m_alertQueue.isEmpty())
    {
        setCurrentAlert(m_alertQueue.first());
    }
    else
    {
        setCurrentAlert(nullptr);
    }
}

void NotificationController::addPopup(NotificationData *popup)
{
    if (popup == nullptr)
    {
        qDebug() << "NotificationController::addPopup() - Cannot add popup.";
    }

    m_popupQueue.append(popup);
    emit popupQueueChanged(m_popupQueue);

    if (!m_popupQueue.isEmpty())
    {
        setCurrentPopup(m_popupQueue.first());
    }
    else
    {
        setCurrentPopup(nullptr);
    }
}

void NotificationController::removeAlert(NotificationData *alert)
{
    if (alert == nullptr)
        return;

    for (NotificationData* data : m_alertQueue)
    {
        if (data == alert)
        {
            // Remove the alert.
            int index = m_alertQueue.indexOf(alert);
            NotificationData* itemToRemove = m_alertQueue.takeAt(index);
            delete itemToRemove;

            if (!m_alertQueue.isEmpty())
            {
                setCurrentAlert(m_alertQueue.first());
            }
            else
            {
                setCurrentAlert(nullptr);
            }
            emit alertQueueChanged(m_alertQueue);
            return;
        }
    }
}

void NotificationController::removePopup(NotificationData *popup)
{
    if (popup == nullptr)
        return;

    for (NotificationData* data : m_popupQueue)
    {
        if (data == popup)
        {
            // Remove the popup.
            int index = m_popupQueue.indexOf(popup);
            NotificationData* itemToRemove = m_popupQueue.takeAt(index);
            setLastPopupResponse(itemToRemove->response());
            delete itemToRemove;

            if (!m_popupQueue.isEmpty())
            {
                setCurrentPopup(m_popupQueue.first());
            }
            else
            {
                setCurrentPopup(nullptr);
            }
            emit popupQueueChanged(m_popupQueue);
            return;
        }
    }
}

void NotificationController::createNotification(int notification, int type, QObject* data)
{

    NotificationData* np = new NotificationData();
    np->setType((NotificationData::Notification)notification);
    np->setData(data);

    switch((NotificationData::Notification)notification)
    {
    case NotificationData::Notification::Type_Alert:
        np->setAlertType(NotificationData::AlertType(type));
        addAlert(np);
        break;
    case NotificationData::Notification::Type_Popup:
        np->setPopupType(NotificationData::PopupType(type));
        addPopup(np);
        break;
    }
}

void NotificationController::removeNotification(NotificationData* notification)
{
    if (notification != nullptr)
    {
        switch (notification->type())
        {
        case NotificationData::Notification::Type_Alert:
            removeAlert(notification);
            break;
        case NotificationData::Notification::Type_Popup:
            removePopup(notification);
            break;
        }
    }
}
