import QtQuick 2.0
import QtGraphicalEffects 1.0
Item {
    property url image: "qrc:/imgSrc/CD.png"
    Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: image
    }
}


