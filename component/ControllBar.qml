import QtQuick 2.0
import QMediaPlayer.MediaStatus 1.0
Item {
    Timer{
        id: perTimer
        interval: 100
        repeat: true
        running: btnPre.presshold
        onTriggered: {
           MusicController.setMusicPosition(PlayListModel.position-500)
        }
    }
    Timer{
        id: nextTimer
        interval: 100
        repeat: true
        running: btnnext.presshold
        onTriggered: {
            MusicController.setMusicPosition(PlayListModel.position+500)
        }
    }

    Row{
        height: childrenRect.height
        anchors{
          centerIn: parent
        }
        spacing: 25
        ButtonMenu{
            width: 45
            height: 45
            buttonImage: "qrc:/imgSrc/shuffle.png"
            hoverImage: "qrc:/imgSrc/focusBtn.png"
            activeImage: "qrc:/imgSrc/shuffle_2.png"
            active: PlayListModel.playRule&4
            onClicked: {
                MusicController.setMusicRule(4)
            }
        }
        ButtonMenu{
            id: btnPre
            width: 45
            height: 45
            buttonImage: "qrc:/imgSrc/preBtn.png"
            hoverImage: "qrc:/imgSrc/focusBtn.png"
            pressImage: "qrc:/imgSrc/preBtnPressed.png"
            onClicked: {
                MusicController.setMusicPosition(0);
            }
            onDoubleClicked: {
                 MusicController.next(-1)
            }
            onPressAndHold: {

            }

        }
        ButtonMenu{
            id: btnPlay
            width: 45
            height: 45
            buttonImage: "qrc:/imgSrc/playBtn.png"
            hoverImage: "qrc:/imgSrc/focusBtn.png"
            activeImage: "qrc:/imgSrc/pauseBtn.png"
            active: PlayListModel.state == QMediaPlayer.PlayingState
            onClicked: {
                MusicController.play()
            }
        }
        ButtonMenu{
            id: btnnext
            width: 45
            height: 45
            buttonImage: "qrc:/imgSrc/nextBtn.png"
            hoverImage: "qrc:/imgSrc/focusBtn.png"
            pressImage: "qrc:/imgSrc/nextBtnPressed.png"
            onClicked: {
                MusicController.next(1)
            }
        }
        ButtonMenu{
            width: 45
            height: 45
            buttonImage: "qrc:/imgSrc/RepeatBtn.png"
            hoverImage: "qrc:/imgSrc/focusBtn.png"
            activeImage: "qrc:/imgSrc/RepeatBtn_2.png"
            Text {
                anchors{
                    right: parent.right
                    rightMargin: 5
                    top: parent.top
                    topMargin: 5
                }

                color: "white"
                text: (3&PlayListModel.playRule) == 3?"1":"";
                font.pixelSize: 12
            }
            active: (3&PlayListModel.playRule) > 1
            onClicked: {
                if((3&PlayListModel.playRule) == 1){
                    MusicController.setMusicRule(2)
                }else
                if((3&PlayListModel.playRule) == 2){
                    MusicController.setMusicRule(3)
                }else{
                    MusicController.setMusicRule(1)
                }
            }
        }
    }
}
