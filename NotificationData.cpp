#include "NotificationData.h"

NotificationData::NotificationData(QObject *parent) : QObject(parent)
  , m_type(Notification::Type_Alert)
  , m_alertType(AlertType::Alert_Unset)
  , m_popupType(PopupType::Popup_Unset)
  , m_data()
{

}

NotificationData::Notification NotificationData::type() const
{
    return m_type;
}

QObject *NotificationData::data() const
{
    return m_data;
}

NotificationData::AlertType NotificationData::alertType() const
{
    return m_alertType;
}

NotificationData::PopupType NotificationData::popupType() const
{
    return m_popupType;
}

void NotificationData::setType(NotificationData::Notification type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}

void NotificationData::setData(QObject *data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataChanged(m_data);
}

void NotificationData::setAlertType(NotificationData::AlertType alertType)
{
    if (m_alertType == alertType)
        return;

    m_alertType = alertType;
    emit alertTypeChanged(m_alertType);
}

void NotificationData::setPopupType(NotificationData::PopupType popupType)
{
    if (m_popupType == popupType)
        return;

    m_popupType = popupType;
    emit popupTypeChanged(m_popupType);
}
