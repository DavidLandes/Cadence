import QtQuick 2.0

Item {
    id: busy

    // Msecs to complete a full loop.
    property var loopDuration: 850

    // Repeat the loop continuously.
    property bool repeat: true

    // Number of samples in one full loop.
    property var samples: 50

    property bool running: tim.running

    property color primaryColor: "red"
    property color secondaryColor: "grey"

    height: 50
    width: height
    visible: running

    function start() {
        tim.start()
    }

    function stop() {
        tim.stop()
    }

    Timer {
        id: tim
        repeat: busy.repeat
        interval: busy.loopDuration / busy.samples
        onTriggered: canvas.requestPaint()
    }

    Canvas {
        id: canvas
        antialiasing: true
        width: parent.width
        height: parent.height

        property real centerWidth: width/2
        property real centerHeight: centerWidth

        property real rate: 2*Math.PI / busy.samples
        property real length: 3*Math.PI/4

        property real startAngle: 0
        property real endAngle: 2*Math.PI
        property real angle: 0

        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.save();

            ctx.clearRect(0, 0, canvas.width, canvas.height);

            // Secondary progress bar.
            ctx.beginPath();
            ctx.lineWidth = 5;
            ctx.strokeStyle = busy.secondaryColor;
            ctx.arc(canvas.centerWidth,
                    canvas.centerHeight,
                    busy.height/5,
                    canvas.startAngle,
                    canvas.endAngle);
            ctx.stroke();

            // Primary progress bar.
            ctx.beginPath();
            ctx.lineWidth = 7;
            ctx.strokeStyle = busy.primaryColor;
            ctx.arc(canvas.centerWidth,
                    canvas.centerHeight,
                    busy.height/5,
                    canvas.angle,
                    canvas.angle + canvas.length);
            ctx.stroke();

            ctx.restore();

            // Rotate the indicator.
            canvas.angle += canvas.rate
        }
    }
}
