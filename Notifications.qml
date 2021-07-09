import QtQuick 2.0
import com.Cadence.Types 1.0

Item {
    property NotificationData currentAlert: notifications.currentAlert
    property NotificationData currentPopup: notifications.currentPopup

    anchors.fill: parent

    Alerts {
        id: alert
        visible: currentAlert
    }

    Popups {
        id: popup
        visible: currentPopup
    }
}
