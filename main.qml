import QtQuick 2.6
import QtQuick.Window 2.2
import QtGraphicalEffects 1.12
Window {
    id: mainWindow
    visible: true
    title: qsTr("Pro Player")
    maximumWidth: 360
    minimumWidth: maximumWidth
    maximumHeight: 582
    minimumHeight: maximumHeight
    property bool closeWindow: false
    Loader{
        id: rootloader
        anchors.fill: parent
        source: HMIModel.currentScreen
    }
    onClosing:{
        if(closeWindow == false){
            close.accepted = false
        }
        onTriggered:{
           if(closeWindow == false){
               console.log("saving..");
               MusicController.wirteFileJson()
           }
        }
    }
    Component.onCompleted: {
        MusicController.readFileJson()
    }

    Connections{
        target: JsonManager
        onWirteComplete: {
           console.log("closed")
           closeWindow = true;
           close.accepted = true
           mainWindow.close()
        }
    }

}
