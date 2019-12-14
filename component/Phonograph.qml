import QtQuick 2.0
import QtGraphicalEffects 1.0
import QMediaPlayer.MediaStatus 1.0
Item {
    id: phonograph
    property int mediaState: 0
    property int mediaStatus: 0
    property var mediaPosition: 0
    property var mediaDuration: 0
    property real angle: mediaDuration==0?-30:-20.0*mediaPosition/mediaDuration+11
    onMediaStateChanged: {
        console.log("state:",mediaState)
    }
    onMediaStatusChanged: {
        console.log("status:",mediaStatus)
    }

    Rectangle{
        id: markCD
        anchors.centerIn: imageCD
        width: 345
        height: 345
        radius: width/2
    }
    DropShadow {
        anchors.fill: markCD
        horizontalOffset: 12
        verticalOffset: 12
        radius: 8
        samples: 17
        color: "#aa000000"
        source: markCD
    }
    Image {
        id: imageCD
        source: "qrc:/imgSrc/CD350x350.png"
        smooth: true
    }
    RotationAnimation{
        id: spinAnimation
        target: imageCD
        from: imageCD.rotation
        to: imageCD.rotation+360
        direction: RotationAnimation.Clockwise
        duration: 2000
        loops: Animation.Infinite
        running: false
    }

    Image {
        id: imageRotor
        fillMode: Image.PreserveAspectFit
        smooth: true
        anchors{
            top: parent.top
            left: parent.right
            leftMargin: 30
        }
        source: "qrc:/imgSrc/TrackRotor.png"
    }
    Image {
        id: imageLight
        fillMode: Image.PreserveAspectFit
        smooth: true
        anchors{
            centerIn: imageRotor
        }
        rotation: imageNeedle.rotation+18
        source: "qrc:/imgSrc/RotorLight.png"
    }

    Image{
        id: imageNeedle
        fillMode: Image.PreserveAspectFit
        smooth: true
        anchors{
            centerIn: imageRotor
        }
        rotation: phonograph.angle
        source: "qrc:/imgSrc/Needle.png"
        Behavior on rotation {
            RotationAnimation{
                easing.type: Easing.OutBack
            }
        }
    }

    states: [
        State {
            name: "stoped"
            when: mediaState == QMediaPlayer.StoppedState
            PropertyChanges {
                target: imageNeedle
                rotation: -30
            }
        },
        State {
            name: "play"
            when: mediaState == QMediaPlayer.PlayingState
            PropertyChanges{
                target: spinAnimation
                running: true
            }
        }
    ]
}

