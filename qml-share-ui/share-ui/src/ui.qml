import Qt 4.7

Rectangle {
    id: root
    width: 640
    height: 480
    anchors.fill: parent
    color: "white"

    // these should eventually be replaced by proper models
    property bool pluginsLoaded: false
    property int  pluginsCount: 0
    property int  methodsCount: 0

    // a list of methods, should eventually be replaced by a proper model
    property variant methods

    Connections {
        target:  context_pluginLoader

        onAllPluginsLoaded: {
            console.log("ui.qml: all plugins loaded")
            root.methodsCount = context_pluginLoader.methodCount
            root.pluginsCount = context_pluginLoader.pluginCount

            root.methods = context_pluginLoader.methods
            console.log("ui.qml: methods", root.methods, root.methods.length)

            root.pluginsLoaded = true
        }
    }

    Component {
        id: methodDelegate

        Rectangle {
            id: bgrect

            // TODO: a proper model for methods and plugins
            property variant method : root.methods[model.index]

            width:  ListView.view.width
            height: 60
            color: model.index % 2 == 0 ? "lightgrey" : Qt.lighter("lightgrey")

            states: State {
                name: "pressed"
                when: mouseArea.pressed
                PropertyChanges {
                    target: bgrect
                    color: Qt.darker(bgrect.color)
                }
            }

            Column {
                anchors.fill: parent
                Text {
                    font.pointSize: 20
                    height: 20
                    text: " " + bgrect.method.title
                }
                Text {
                    font.pointSize: 15
                    height: 15
                    text: " " + bgrect.method.subtitle
                }
                Text {
                    font.pointSize: 15
                    height: 15
                    text: " " + context_pluginLoader.pluginNameForMethod(bgrect.method)
                }

            }


            MouseArea {
                id:  mouseArea
                anchors.fill: parent

                onClicked: root.methods[model.index].selected(context_itemContainer);
             }

        }
    }


    Component {
        id: itemComponent


        Rectangle {
            height: GridView.view.height / 3
            width:  height

            // TODO: a proper model for items
            property variant item: context_itemContainer.getItem(model.index)

            // TODO, can be removed once thumbnail property of shareditem is
            // properly implemented
            Connections {
                target: item
                onThumbnail: {
                    console.log("ui.qml: onThumbnail", item)
                    theImage.source = uri
                }
            }

            Row {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter

                Image {
                    id: theImage

                    source: {
                        console.log("requesting initial thumbnail from", item)
                        return item.thumbnail
                    }

                    height: GridView.view.cellHeight
                    width:  GridView.view.cellWidth
                    fillMode: Image.PreserveAspectCrop

                    clip: true

                    // TODO: remove once thumbnail property of shareditem is
                    // properly implemented
                    Component.onCompleted: {
                        item.requestThumbnail("grid")
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            // ew, item.thumbnail returns the default, smallest one
                            // much better thumbnail could be of flavor "halfscreen"
                            previewOverlay.source = item.thumbnail
                            previewOverlay.state = "visible"
                        }
                    }
                }

            }

        }
    }



    GridView {
        id: itemContainerView

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 5
        width:  480

        cellWidth: width/3
        cellHeight: cellWidth

        flow: GridView.LeftToRight

        // TODO: a proper model for items
        model: context_itemContainer.count     

        delegate: itemComponent
        clip: true
    }


    ListView {
        id: methodsView
        anchors.top:  parent.top
        anchors.left: itemContainerView.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10

        // TODO: a proper listmodel for methods
        model: root.pluginsLoaded ? root.methods.length : 0
        delegate: methodDelegate
        clip: true
    }



    Image {
        id: previewOverlay
        z: 10
        opacity: 0.0
        anchors.fill: itemContainerView
        anchors.margins: itemContainerView.cellHeight
        source: ""

        states: State {
            name: "visible"

            PropertyChanges {
                target:  previewOverlay
                opacity: 1.0
                anchors.margins: 0
            }

        }

        transitions: Transition {
            NumberAnimation {
                properties: "opacity,anchors.margins"
            }


        }

        MouseArea {
            anchors.fill: parent
            onClicked: previewOverlay.state = ""
        }
    }

}
