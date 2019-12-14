import QtQuick 2.0
import QtGraphicalEffects 1.0
Item {
    id: positionbar
    property var position: 0
    property var duration: 0
    Rectangle{
        anchors{
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width
        height: 8
        radius: height/2
        color: "black"
        Image {
            anchors.fill: parent
            source: "qrc:/imgSrc/status-bar.png"
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: parent
            }
        }
        Rectangle{
            height: 6
            anchors.verticalCenter: parent.verticalCenter
            width: positionbar.duration!=0?parent.width * positionbar.position/positionbar.duration
                                          : 0
            color: "#c1e065"
            radius: height/2
        }
        MouseArea{
            id: areaPosition
            anchors.fill: parent
            onPressed: {
                positionChange(mouseX)
            }

            onPositionChanged: {
                if(areaPosition.pressed && mouseX <= parent.width
                        && mouseX >= 0)
                {
                    positionChange(mouseX)
                }
            }
        }
    }
    Text {
        id: timeleft
        anchors{
            bottom: parent.bottom
            left: parent.left
            bottomMargin: 10
        }
        font.pixelSize: 12
        color: "white"
        text: "00:00"
    }
    Text {
        id: timeduration
        anchors{
            bottom: parent.bottom
            right: parent.right
            bottomMargin: 10
        }
        font.pixelSize: 12
        color: "white"
        text: "00:00"
    }
    onDurationChanged: {
        timeduration.text = convertMillisecond(positionbar.duration)
    }
    onPositionChanged: {
        timeleft.text = convertMillisecond(positionbar.position)
    }
    function convertMillisecond(milisecond){
        var timetxt = "00:00"
        if(milisecond>0){
            var seconds = Math.floor((milisecond / 1000) % 60)
            var minutes = Math.floor((milisecond / (1000 * 60)) % 60)
            seconds = (seconds<10)?"0"+seconds:seconds
            minutes = (minutes<10)?"0"+minutes:minutes
            return timetxt = String(minutes)+":"+String(seconds)
        }else{
            return timetxt;
        }
    }

    function positionChange(mousex){
        var position = positionbar.duration*mousex/positionbar.width
        MusicController.setMusicPosition(position);
    }
}
