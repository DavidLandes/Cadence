import QtQuick 2.0
import QtQml 2.0

import com.Cadence.Types 1.0

Item {
    id: template

    Loader {
        sourceComponent: if (notifications.currentPopup) {
             switch(notifications.currentPopup.popupType)
             {
             case NotificationData.Popup_Test:
             default:
                 return undefined
             }
         }
         else
         {
             return undefined
         }
    }
}
