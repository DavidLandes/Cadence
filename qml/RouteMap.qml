import QtQuick 2.0
import QtQuick.Controls 2.0
import QtLocation 5.11
import QtPositioning 5.0
import QtQuick.Layouts 1.12

import com.Cadence.Types 1.0

import "./common"

Rectangle {
    id: mapContainer

    property Trip trip
    signal selectTrip()

    Text {
        id: tripTitle
        visible: mapContainer.state == "widget"
        text: trip ? trip.tripName : "No trip selected"
        anchors {
            bottom: mapItem.top
            bottomMargin: 5
            left: mapContainer.left
            leftMargin: 10
        }
        font {
            pixelSize: 16
        }
    }

    IconButton {
        id: selectTripButton
        source: "qrc:/images/explore_white.png"
        width: height
        anchors {
            top: mapContainer.top
            bottom: mapItem.top
            right: enlargeMap.left
            rightMargin: 10
        }
        onClicked: {
            mapContainer.selectTrip()
        }
    }

    IconButton {
        id: enlargeMap
        source: "qrc:/images/open_in_full_white.png"
        width: height
        anchors {
            top: mapContainer.top
            bottom: mapItem.top
            right: parent.right
            rightMargin: 10
        }
        onClicked: {
            mapContainer.state = "full_screen"
        }
    }

    Map {
        id: mapItem
        z: mapContainer.z + 5
        //activeMapType: MapType.SatelliteMapDay
        plugin: Plugin {
            name: "esri"
        }
        zoomLevel: 12

        anchors {
            centerIn: parent
        }

        // TODO: create "center" button that zooms in on the beginning coordinate of the current trip.

        function updateRoute(trip) {
            if (!trip)
                return;

            var routeModel = []
            for (var i = 0; i < trip.positions.length; i++)
            {
                routeModel.push(QtPositioning.coordinate(trip.positions[i].coordinate.latitude, trip.positions[i].coordinate.longitude))
            }

            // Center to the last position recorded.
            if (i == trip.positions.length - 1)
            {
                mapItem.center = QtPositioning.coordinate(trip.positions[i].coordinate.latitude, trip.positions[i].coordinate.longitude)
            }

            return routeModel
        }

        MapPolyline {
            id: route
            z: parent.z + 10
            path: mapContainer.trip ? mapItem.updateRoute(mapContainer.trip) : null
            line {
                color: "black"
                width: 5
            }
        }
        Repeater {
            model: route.path
            MapCircle {
                center: modelData
                radius: 100//route.line.width
                color: index != 0 ? route.line.color : "green"
            }
        }
    }

    state: "widget"

    states: [
        State {
            name: "widget"
            PropertyChanges {
                target: mapContainer
                width: parent.width * .9
                height: 300
                radius: 15
                color: "lightgrey"
            }
            PropertyChanges {
                target: mapItem
                width: parent.width
                height: parent.height * .75
            }
        },
        State {
            name: "full_screen"
            PropertyChanges {
                target: mapContainer
                width: parent.width
                height: parent.height
                radius: 0
                color: "transparent"
            }
            PropertyChanges {
                target: mapItem
                width: parent.width
                height: parent.height
            }
        }
    ]
}
