import QtQuick 2.0
import QtQuick.Controls 2.0

// TODO: Implement smooth transitions between components.
Item {
    id: travelPaneItem
    anchors.fill: parent

    SwipeView {
        id: view
        interactive: true
        anchors.fill: parent
//        ManagePath {
//            height: travelPaneItem.height
//            width: travelPaneItem.width
//            selectedPath: travelController.currentPath
//        }
//        ManageTrip {
//            height: travelPaneItem.height
//            width: travelPaneItem.width
//            selectedTrip: travelController.currentTrip
//        }

        Loader {
            sourceComponent: determineList()
            height: travelPaneItem.height
            width: travelPaneItem.width

            function determineList() {
                if (travelController.currentPath) {
                    return trips
                }
                else {
                    return paths
                }
            }

            Component {
                id: paths
                PathList {
                }
            }

            Component {
                id: trips
                TripList {
                }
            }
        }

        BeginTrip {
            height: travelPaneItem.height
            width: travelPaneItem.width
        }
    }

    PageIndicator {
        currentIndex: view.currentIndex
        count: view.count
        anchors {
            bottom: view.bottom
            horizontalCenter: view.horizontalCenter
        }
    }
}
