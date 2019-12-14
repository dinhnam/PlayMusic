import QtQuick 2.0
import "../component"
Item {
   id: mediamanage
   Navigation{
       id: navigation
       z: 2
       ButtonMenu{
           id: btnClear
           width: 70
           height: 40
           anchors{
               verticalCenter: parent.verticalCenter
           }
           buttonImage: "qrc:/imgSrc/clearBtn.png"
           hoverImage: "qrc:/imgSrc/focusBtn.png"
           pressImage: "qrc:/imgSrc/btnClearPressed.png"
           onClicked: {
               MusicController.removeItemInModel();
           }
       }
       ButtonMenu{
           id: btnAdd
           width: 100
           height: 20
           anchors{
               verticalCenter: parent.verticalCenter
               left: btnClear.right
               leftMargin: 20
           }
           buttonRectangle.visible: true
           buttonRectangle.radius: 10
           buttonText{
               text: qsTr("Add Playlist")+mytrans.emptyString
               font.pixelSize: 12
           }
           onClicked: {
               MusicController.addMusicToPlaylsit();
           }
       }
   }
   Row{
      id: listmenu
      height: children.height
      z: 2
      property var arrayTitle: [qsTr("Musics"),qsTr("Folder"),qsTr("Album"),qsTr("Artist")]
      property var arrayTotal: [MusicManager.musicTotal,MusicManager.folderTotal
                                ,MusicManager.albumTotal,MusicManager.artistTotal]
      property int currentIndex: MusicManager.currentTab
      anchors{
          top: navigation.bottom
          horizontalCenter: parent.horizontalCenter
      }
      Repeater{
          model: mytrans.emptyNumber+4
          ButtonMenu{
              width: mediamanage.width/4
              height: 40
              buttonText.text: listmenu.arrayTitle[index]+mytrans.emptyString
              buttonRectangle.visible: true
              active: listmenu.currentIndex==index && MusicModel.isSubItem
              activeImage: "qrc:/imgSrc/backtab.png";
              image.width: 16
              buttonRectangle.color: listmenu.currentIndex==index?"#e8d399":"white"
              Text {
                  anchors{
                      bottom: parent.bottom
                      bottomMargin: 1
                      horizontalCenter: parent.horizontalCenter
                  }

                  font.pixelSize: 11
                  color: "gray"
                  text: listmenu.arrayTotal[index]
              }
              onClicked: {
                  MusicController.clearSlections()
                  MusicController.openTabAt(index)
                  MusicManager.currentTab = index
              }
          }
      }
   }
   SearchBar{
       z: 2
       id: searchbar
       width: parent.width
       height: 40
       anchors{
           bottom: parent.bottom
           bottomMargin: 48
       }
   }

   ManageList{
      z: 0
      width: parent.width
      anchors{
          top: listmenu.bottom
          bottom: searchbar.top
      }
   }


}
