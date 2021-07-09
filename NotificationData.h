#ifndef NOTIFICATIONDATA_H
#define NOTIFICATIONDATA_H

#include <QObject>

class NotificationData : public QObject
{
    Q_OBJECT
public:
    explicit NotificationData(QObject *parent = nullptr);

    Q_PROPERTY(Notification type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(AlertType alertType READ alertType WRITE setAlertType NOTIFY alertTypeChanged)
    Q_PROPERTY(PopupType popupType READ popupType WRITE setPopupType NOTIFY popupTypeChanged)
    Q_PROPERTY(QObject* data READ data WRITE setData NOTIFY dataChanged)

    enum class Notification {
        Type_Alert,
        Type_Popup
    };
    Q_ENUM(Notification);

    enum class AlertType {
        Alert_Unset,
        Alert_Test,
        Alert_Test2
    };
    Q_ENUM(AlertType);

    enum class PopupType {
        Popup_Unset
    };
    Q_ENUM(PopupType);

    Notification type() const;
    QObject* data() const;
    AlertType alertType() const;
    PopupType popupType() const;

public slots:
    void setType(Notification type);
    void setData(QObject* data);
    void setAlertType(AlertType alertType);
    void setPopupType(PopupType popupType);

signals:
    void typeChanged(Notification type);
    void dataChanged(QObject* data);
    void alertTypeChanged(AlertType alertType);
    void popupTypeChanged(PopupType popupType);

private:
    Notification m_type;
    QObject* m_data;
    AlertType m_alertType;
    PopupType m_popupType;
};

#endif // NOTIFICATIONDATA_H
