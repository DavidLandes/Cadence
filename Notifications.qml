import QtQuick 2.0
import com.Cadence.Types 1.0

Item {
    property NotificationData currentAlert: notifications.currentAlert
    property NotificationData currentPopup: notifications.currentPopup

    anchors.fill: parent

    AlertTemplate {
        id: alert
        visible: true/*currentAlert*/
    }

    PopupTemplate {
        id: popup
        visible: currentPopup
        anchors.fill: parent
    }
}
