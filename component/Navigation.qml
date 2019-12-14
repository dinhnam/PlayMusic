import QtQuick 2.0
import QtQuick.Controls 2.5
import MyLang 1.0
Item {
   width: parent.width
   height: 48
   Image {
       id: darkbg
       width: parent.width
       fillMode: Image.PreserveAspectFit
       source: "qrc:/imgSrc/darkbg.png"
   }
   Row{
       height: childrenRect.height
       anchors{
           right: parent.right
           rightMargin: 5
           verticalCenter: parent.verticalCenter
       }
       spacing: 15
       ButtonMenu{
           width: 30
           height: 30
           buttonImage: "qrc:/imgSrc/playlist.png"
           hoverImage: "qrc:/imgSrc/focusBtn2.png"
           onClicked: {
                MusicController.clearSlections()
                MusicController.showPlayList()
                HMIController.showPopup("qrc:/screen/PlayListManager.qml")
           }
       }
       ButtonMenu{
           width: 30
           height: 30
           buttonImage: "qrc:/imgSrc/RoundedRect.png"
           hoverImage: "qrc:/imgSrc/focusBtn2.png"
           onClicked: {
                MusicController.clearSlections()
                MusicController.openTabAt(MusicManager.currentTab);
                HMIController.showPopup("qrc:/screen/MediaManager.qml")
           }
       }
       ButtonMenu{
           id: btnSetting
           width: 30
           height: 30
           buttonImage: "qrc:/imgSrc/settingBtn.png"
           hoverImage: "qrc:/imgSrc/focusBtn2.png"
           Menu {
               id: menuTrans
               width: 120
               y: btnSetting.height
               MenuItem {
                   height: 30
                   text: "English"
                   onClicked: {
                       mytrans.updateLanguage(MyLang.EN)
                   }
               }
               MenuItem {
                   height: 30
                   text: "Vietnam"
                   onClicked: {
                       mytrans.updateLanguage(MyLang.VI)
                   }
               }
           }
           onClicked: {
               menuTrans.open()
           }
       }
       ButtonMenu{
           id: menuBtn
           width: 14
           height: 28
           buttonImage: "qrc:/imgSrc/MenuBtn.png"
           hoverImage: "qrc:/imgSrc/focusBtn2.png"
           Menu {
               id: menuFolder
               width: 120
               y: menuBtn.height
               MenuItem {
                   height: 30
                   text: qsTr("ADD FOLDER")+mytrans.emptyString
                   onClicked: {
                       MusicController.openDialogFolder()
                   }
               }
               MenuItem {
                   height: 30
                   text: qsTr("ADD MUSICS")+mytrans.emptyString
                   onClicked: {
                       MusicController.openSelectFiles()
                   }
               }
           }
           onClicked: {
                menuFolder.open()
           }
       }
   }

}
