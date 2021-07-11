import QtQuick 2.0
import QtQuick.Controls 2.0
import QtLocation 5.11
import QtPositioning 5.0

import com.Cadence.Types 1.0

Item {
    property bool locked: false
    Map {
        id: mapItem
        width: parent.width
        height: parent.height
        //activeMapType: MapType.SatelliteMapDay
        plugin: Plugin {
            name: "esri"
        }
        zoomLevel: 10
        center: QtPositioning.coordinate(geoController.currentTrip.positions[0].coordinate.latitude, geoController.currentTrip.positions[0].coordinate.longitude)

        function updateRoute(trip) {
            if (!trip)
                return;

            var routeModel = []
            for (var i = 0; i < trip.positions.length; i++)
            {
                routeModel.push(QtPositioning.coordinate(trip.positions[i].coordinate.latitude, trip.positions[i].coordinate.longitude))
            }
            return routeModel
        }

        MapPolyline {
            id: route
            z: parent.z + 10
            path: mapItem.updateRoute(geoController.currentTrip)
            line {
                color: "black"
                width: 5
            }
        }
    }
    Button {
        id: lock
        height: 50
        width: 200
        anchors {
            bottom: parent.bottom /*settrip.top*/
            horizontalCenter: parent.horizontalCenter
        }
        text: "Screen " + (locked ? "Locked" : "Unlocked")
        onClicked: {
            locked = !locked
        }
    }
//    Button {
//        id: settrip
//        height: 50
//        width: 100
//        anchors {
//            bottom: parent.bottom
//            horizontalCenter: parent.horizontalCenter
//        }
//        text: "Set trip"
//        onClicked: {
//            //geoController.currentTrip = geoController.trips[geoController.trips.length - 1]
//        }
//    }
}
