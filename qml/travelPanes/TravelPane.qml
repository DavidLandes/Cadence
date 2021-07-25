import QtQuick 2.0
import QtQuick.Controls 2.0

// TODO: Implement smooth transitions between components.
Item {
    id: travelPaneItem
    anchors.fill: parent
//    SwipeView {
//        id: view
//        interactive: false
//        currentIndex: 1

//        function goBackTo(component) {
//            prev.sourceComponent = component
//            view.setCurrentIndex(0)


//        }

//        function goForwardTo(component) {

//        }

//        Loader {
//            id: prev
//        }
//        Loader {
//            id: current

//        }
//        Loader {
//            id: next
//        }
//    }

//    Component {
//        id: paths
//        PathList {
//            onLeftButtonClicked: {
//                // Navigate to create new path pane.
//            }
//            onListItemClicked: {
//                // use listItem's pathId to set current path & generate Trips. then navigate to trip pane.
//            }
//        }
//    }
    SwipeView {
        id: view
        interactive: true
        anchors.fill: parent
        BeginTrip {
            height: travelPaneItem.height
            width: travelPaneItem.width
        }
        PathList {
            height: travelPaneItem.height
            width: travelPaneItem.width
        }
//        TripList {
//            height: travelPaneItem.height
//            width: travelPaneItem.width
//        }
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
