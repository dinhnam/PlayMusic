import QtQuick 2.0

Rectangle {
    Image {
          anchors.fill: parent
          source: "qrc:/imgSrc/system-bar.png"
    }
    Row{
          height: childrenRect.height
          anchors{
            centerIn: parent
          }
          spacing: 70
          ButtonMenu{
              width: 33
              height: 18
              buttonImage: "qrc:/imgSrc/backBtn.png"
              hoverImage: "qrc:/imgSrc/focusBtn.png"
              onClicked: {
                  HMIController.exitScreen()
              }
          }
          ButtonMenu{
              width: 33
              height: 18
              buttonImage: "qrc:/imgSrc/homeBtn.png"
              hoverImage: "qrc:/imgSrc/focusBtn.png"
              onClicked: {
                  HMIController.exitAllScreen("qrc:/screen/HomeScreen.qml")
              }
          }
          ButtonMenu{
              width: 33
              height: 18
              buttonImage: "qrc:/imgSrc/recentBtn.png"
              hoverImage: "qrc:/imgSrc/focusBtn.png"
              onClicked: {

              }
          }
    }
}
