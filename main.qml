import QtQuick 2.14
import QtQuick.Controls 2.0
import QtQuick.Window 2.14
import QtBluetooth 5.0

import com.Cadence.BluetoothController 1.0
import com.Cadence.Types 1.0
import "./common"


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Cadence")

    Notifications { id:notificationsOverlay; z: parent.z + 100 }

    SwipeView {
        anchors.fill: parent

        DevicePane {
            Button {
                property bool toggle: false
                anchors.centerIn: parent
                height: 50
                width: 100
                text: "test notification"
                onClicked: {
                    if (toggle)
                        notifications.createNotification(NotificationData.Type_Alert, NotificationData.Alert_Test)
                    else
                        notifications.createNotification(NotificationData.Type_Alert, NotificationData.Alert_Test2)
                    toggle = !toggle
                }
            }
        }
        Item {
            id: mphContainer
            Indicator {
                id: mphIndicator
                width: parent.width * .7
                height: width
                primaryColor: "red"
                secondaryColor: "grey"
                minimumValue: 0
                maximumValue: 40
                currentValue: Math.round(cadenceInterface.mph)
                anchors.centerIn: parent
            }
        }
        TripPane {

        }
    }
}
