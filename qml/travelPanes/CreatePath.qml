import QtQuick 2.0
import "../common"

TitleTemplate {
    titleText: "Create a New Path"
    RoundedTextInput {
        id: pathName
        title: "Path Name:"
        titleColor: "#001256"
        color: "#e9e9e9"
        textColor: "#001256"
        anchors {
            top: title.bottom
            topMargin: 30
            horizontalCenter: parent.horizontalCenter
        }
    }

}
