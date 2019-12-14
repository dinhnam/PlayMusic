import QtQuick 2.0
import QtGraphicalEffects 1.0
Item {
    id: volumebar
    property int volume: 100
   Item{
       id: bar
       height: parent.height
       width: 10
       Image {
           width: parent.height
           height: parent.width
           anchors.centerIn: parent
           source: "qrc:/imgSrc/VolumeBar.png"
           rotation: 90
       }
       Image {
           id: imagevol
           width: parent.width
           anchors.horizontalCenter: parent.horizontalCenter
           anchors.bottom: parent.bottom
           anchors.top: areavolbutton.verticalCenter
           source: "qrc:/imgSrc/status-volume-ver.png"
       }
       MouseArea{
           anchors.fill: parent
           onPressed: {
               areavolbutton.y = mouseY - 15
           }
       }

       MouseArea{
           id: areavolbutton
           width: 25
           height: 25
           anchors.horizontalCenter: parent.horizontalCenter
           Image {
               source: "qrc:/imgSrc/VolumnButton.png"
               anchors.fill: parent
           }
           drag.axis: Drag.YAxis
           drag.maximumY: parent.height-15
           drag.minimumY: -15
           drag.target: areavolbutton
           onYChanged: {
               var vol = 100*(parent.height -areavolbutton.y-15)/parent.height
               MusicController.setMusicVolume(vol);
           }
       }
   }
   Column{
       spacing: 9
       anchors{
           left: parent.left
           leftMargin: 20
           verticalCenter: parent.verticalCenter
       }
       Repeater{
           model: 10
           Rectangle{
              width: 6
              height: 6
              radius: 3
              color: index>=(volume/10)?"black":"green"
           }
       }
      rotation: 180
   }
   Component.onCompleted: {
       areavolbutton.y = (bar.height-volumebar.volume*bar.height/100)-15
   }
}
