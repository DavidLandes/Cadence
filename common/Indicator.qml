import QtQuick 2.0

Item {
    id: progressIndicator

    property color primaryColor: "red"
    property color secondaryColor: "grey"

    property real primaryLineWidth: 7
    property real secondaryLineWidth: primaryLineWidth - 2

    property string text: currentValue
    property color textColor: primaryColor
    property string suffix: "mph"
    property color suffixTextColor: secondaryColor

    property real minimumValue: 0
    property real maximumValue: 100
    property real currentValue: maximumValue/2

    width: 240
    height: 240

    onPrimaryColorChanged: canvas.requestPaint()
    onSecondaryColorChanged: canvas.requestPaint()
    onMinimumValueChanged: canvas.requestPaint()
    onMaximumValueChanged: canvas.requestPaint()
    onCurrentValueChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        antialiasing: true

        property real centerWidth: parent.width / 2
        property real centerHeight: parent.height / 2
        property real radius: (Math.min(canvas.width, canvas.height) - calculateLineWidth()) / 2

        // Multiply the precentage of angle with the distance between the startAngle & endAngle
        property real angle: calculateAngle()

        // Note: Make sure to adjust the angle if the startAngle or endAngle changes.
        property real startAngle: 3*Math.PI/4
        property real endAngle: Math.PI/4

        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.save();

            ctx.clearRect(0, 0, canvas.width, canvas.height);

            // Secondary progress bar.
            ctx.beginPath();
            ctx.lineWidth = progressIndicator.secondaryLineWidth;
            ctx.strokeStyle = progressIndicator.secondaryColor;
            ctx.arc(canvas.centerWidth,
                    canvas.centerHeight,
                    canvas.radius,
                    canvas.startAngle,
                    canvas.endAngle);
            ctx.stroke();

            // Primary progress bar.
            ctx.beginPath();
            ctx.lineWidth = progressIndicator.primaryLineWidth;
            ctx.strokeStyle = progressIndicator.primaryColor;
            ctx.arc(canvas.centerWidth,
                    canvas.centerHeight,
                    canvas.radius,
                    canvas.startAngle,
                    canvas.startAngle + canvas.angle);
            ctx.stroke();

            ctx.restore();
        }

        function calculateLineWidth() {
            var greaterWidth = primaryLineWidth > secondaryLineWidth ? primaryLineWidth * 2 : secondaryLineWidth * 2
            return greaterWidth
        }

        function calculateAngle() {
            // If the angle overshooting the upper bound..
            if ((progressIndicator.currentValue - progressIndicator.minimumValue) / (progressIndicator.maximumValue - progressIndicator.minimumValue) > 1)
            {
                // Return the upper limit.
                return 3*Math.PI/2
            }
            else
            {
                // Return the actual value.
                return (progressIndicator.currentValue - progressIndicator.minimumValue) / (progressIndicator.maximumValue - progressIndicator.minimumValue) * (3*Math.PI/2)
            }
        }

        Text {
            id: mainText
            text: progressIndicator.text.toString()
            color: progressIndicator.textColor
            anchors {
                centerIn: parent
                verticalCenterOffset: -20
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font {
                pixelSize: 40
                weight: Font.Bold
            }
        }
        Text {
            id: suffixText
            text: progressIndicator.suffix.toString()
            color: progressIndicator.suffixTextColor
            opacity: .6
            anchors {
                top: mainText.bottom
                horizontalCenter: mainText.horizontalCenter
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font {
                pixelSize: 20
                weight: Font.Medium
            }
        }
    }
}
