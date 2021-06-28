import QtQuick 2.14
import QtQuick.Controls 2.0
import QtQuick.Window 2.14
import QtBluetooth 5.0

import com.Cadence.BluetoothController 1.0
import "./common"

/*
  TODO: Create Database to store trips, then store the data catagorized by each trip
  TODO: Create GPS positioning class
  Read and log the coordinates & current speed


  */
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Cadence")

    SwipeView {
        anchors.fill: parent

        DevicePane {
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
    }
}
