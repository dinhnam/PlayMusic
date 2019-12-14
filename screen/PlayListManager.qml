import QtQuick 2.0
import "../component"
Item {
    Image {
        z: 2
        id: darkbg
        width: parent.width
        height: 48
        fillMode: Image.PreserveAspectFit
        source: "qrc:/imgSrc/darkbg.png"
        Text {
            anchors.centerIn: parent
            color: "white"
            font.italic: true
            text: qsTr("Play list")
            font.pixelSize: 22
            font.bold: true
        }
        ButtonMenu{
            id: btnClear
            width: 70
            height: 40
            anchors{
                right: parent.right
                verticalCenter: parent.verticalCenter
                rightMargin: 10
            }
            buttonImage: "qrc:/imgSrc/clearBtn.png"
            hoverImage: "qrc:/imgSrc/focusBtn.png"
            pressImage: "qrc:/imgSrc/btnClearPressed.png"
            onClicked: {
                MusicController.removeMusicInPlaylsit();
            }
        }
    }
    Rectangle{
        width: parent.width
        anchors{
            top: darkbg.bottom
            bottom: parent.bottom
            bottomMargin: 50
        }
        layer.enabled: true
        PlayList{
            z: 0
            anchors.fill: parent
        }
    }



}
