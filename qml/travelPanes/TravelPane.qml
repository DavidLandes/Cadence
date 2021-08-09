import QtQuick 2.0
import QtQuick.Controls 2.0

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
            id: listLoader
            height: travelPaneItem.height
            width: travelPaneItem.width
            sourceComponent: paths

            Connections {
                target: travelController
                function onCurrentPathChanged(currentPath) {
                    listLoader.transition((currentPath ? trips : paths), !currentPath)
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

            function transition(newComponent, rightToLeft) {
                slideAnimation.rightToLeft = rightToLeft
                slideAnimation.initialX = listLoader.x
                slideAnimation.newComponent = newComponent
                slideAnimation.restart()
            }

            SequentialAnimation {
                id: slideAnimation
                property bool rightToLeft: true
                property var initialX: 0
                property var duration: 650
                property var offsetX: 50
                property Component newComponent

                ParallelAnimation {
                    id: slideOut
                    NumberAnimation {
                        target: listLoader
                        property: "x"
                        from: slideAnimation.initialX
                        to: slideAnimation.rightToLeft ? slideAnimation.initialX - slideAnimation.offsetX : slideAnimation.initialX + slideAnimation.offsetX
                        duration: slideAnimation.duration / 2
                    }
                    NumberAnimation {
                        target: listLoader
                        property: "opacity"
                        from: 1
                        to: 0
                        duration: slideAnimation.duration / 2
                    }
                }
                ScriptAction {
                    script: {
                        listLoader.sourceComponent = slideAnimation.newComponent
                    }
                }
                ParallelAnimation {
                    id: slideIn
                    NumberAnimation {
                        target: listLoader
                        property: "x"
                        from: slideAnimation.rightToLeft ? slideAnimation.initialX + slideAnimation.offsetX : slideAnimation.initialX - slideAnimation.offsetX
                        to: slideAnimation.initialX
                        duration: slideAnimation.duration / 2
                    }
                    NumberAnimation {
                        target: listLoader
                        property: "opacity"
                        from: 0
                        to: 1
                        duration: slideAnimation.duration / 2
                    }
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
