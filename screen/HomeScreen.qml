import QtQuick 2.0
import "../component"
Item {

    Image {
        id: imgBg
        fillMode: Image.PreserveAspectFit
        height: parent.height
        source: "qrc:/imgSrc/bgHome.jpeg"
    }
    MouseArea{
        id: areaLoad
        anchors.centerIn: parent
        width: 150
        height: 150
        hoverEnabled: true
        Image {
            id: imgToMedia
            fillMode: Image.PreserveAspectFit
            antialiasing: true
            anchors.fill: parent
            source: "qrc:/imgSrc/play-button.png"
            opacity: 0.5
            states: [
                State {
                    name: "hover"
                    when: areaLoad.containsMouse
                    PropertyChanges {
                        target: imgToMedia
                        scale: 1.1
                    }
                }
            ]
            transitions: [
                Transition {
                    NumberAnimation {
                        property: "scale"
                        duration: 400
                    }
                }
            ]
        }
        onClicked: {
            HMIController.showScreen("qrc:/screen/MediaScreen.qml")
        }
    }
    TextScroll{
        width: parent.width
        height: 50
        anchors.bottom: parent.bottom
        run: true
        title{
            color: "#e6afaa"
            font.bold: true
            text: "If you want to play music files in just"+
                        "about any format, ProPlayer is probably your answer"
            font.pixelSize: 16
        }
    }



}
