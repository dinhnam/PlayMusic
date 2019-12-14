import QtQuick 2.0
import "../component"
Item {
    Image {
        id: imgBg
        fillMode: Image.PreserveAspectFit
        height: parent.height
        source: "qrc:/imgSrc/bg.png"
    }
    Navigation{
        id: navigation
        z: 2
    }
    SystemBar{
        z: 3
        id: systembar
        width: parent.width
        height: 49
        anchors{
            bottom: parent.bottom
        }
    }
    ControllBar{
        id: controllbar
        width: parent.width
        height: 45
        anchors{
            bottom: systembar.top
            bottomMargin: 10
        }
    }
    PositionBar{
        id: positionbar
        width: parent.width*0.85
        anchors{
            bottom: controllbar.bottom
            bottomMargin: 55
            horizontalCenter: parent.horizontalCenter
        }
        position: PlayListModel.position
        duration: PlayListModel.duration
    }
    TextScroll{
        width: 300
        height: 48
        anchors{
            bottom: positionbar.top
            left: positionbar.left
        }
        run: true
        title{
            color: "#e6afaa"
            text: PlayListModel.musicTitle
            font.pixelSize: 17
        }
    }
    VolumeBar{
        id: volumbar
        width: 50
        height: 150
        z: 0
        anchors{
            bottom: positionbar.top
            bottomMargin: 50
            right: parent.right
        }
        volume: PlayListModel.volume

    }
    Phonograph{
        id: phonograph
        width: 345
        height: 345
        anchors{
            top: navigation.bottom
            topMargin: 10
            horizontalCenter: parent.left
            horizontalCenterOffset: 20
        }
        mediaState: PlayListModel.state
        mediaStatus: PlayListModel.mediaStatus
        mediaPosition: PlayListModel.position
        mediaDuration: PlayListModel.duration
    }

    Loader{
        id: loaderList
        z: 2
        anchors.fill: parent
        source: HMIModel.currentPopup
        onSourceChanged: {
            console.log("onSourceChanged")
            MusicController.clearSlections()
            if(HMIModel.currentPopup == "qrc:/screen/MediaManager.qml"){
                MusicController.openTabAt(MusicManager.currentTab);
            }
        }
    }
    Component.onCompleted: {
        console.log("media screen loaded")
    }
}
