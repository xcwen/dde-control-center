import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import DBus.Com.Deepin.Daemon.Audio 1.0
import Deepin.Widgets 1.0

Item {
    anchors.fill: parent

    property var audioId: Audio {}

    property int contentLeftMargin: 22
    property int contentHeight: 60
    property int sliderWidth: 170

    Column {
        anchors.top: parent.top
        width: parent.width

        DssTitle {
            text: dsTr("Sound")
        }

        DBaseLine {
            leftLoader.sourceComponent: DssH2 {
                text: dsTr("Speaker")
                font.bold: true
            }
        }

        DSeparatorHorizontal {}

        DSwitchButtonHeader {
            text: dsTr("Enable Speaker")
            active: true
            leftMargin: contentLeftMargin

            onClicked: {

            }
        }

        DSeparatorHorizontal {}

        DBaseExpand {
            id: outputChoose
            property int currentIndex: -1
            property string currentTimezoneLabel

            header.sourceComponent: DDownArrowHeader {
                text: dsTr("Output Port")
                leftMargin: contentLeftMargin
                onClicked: {
                    outputChoose.expanded = !outputChoose.expanded
                }
            }
            content.sourceComponent: Item {
                width: parent.width
                height: outputList.count * 30

                ListView {
                    id: outputList
                    anchors.fill: parent
                    focus: true
                    currentIndex: 0

                    model: ListModel {
                        ListElement { name: "Inner" }
                        ListElement { name: "Headset" }
                    }

                    delegate: Item {
                        anchors.left: parent.left
                        anchors.leftMargin: contentLeftMargin
                        width: parent.width
                        height: 30

                        Row {
                            spacing: 5
                            anchors.verticalCenter: parent.verticalCenter
                            
                            Image {
                                id: nameImage
                                anchors.verticalCenter: parent.verticalCenter
                                source: "images/select.png"
                                opacity: outputList.currentIndex == index ? 1 : 0
                            }
                            
                            DssH3 {
                                id: nameText
                                anchors.verticalCenter: parent.verticalCenter
                                text: name 
                                color: outputList.currentIndex == index ? Qt.rgba(0, 144/255, 1, 1.0) :dconstants.fgColor
                                font.pixelSize: 12
                            }
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: { 
                                parent.ListView.view.currentIndex = index
                            }
                        }
                    }
                }
            }
        }

        DBaseLine {
            height: contentHeight
            leftMargin: contentLeftMargin
            leftLoader.sourceComponent: DssH2 {
                text: dsTr("Output Volume")
            }
            rightLoader.sourceComponent: DSliderRect {
                width: sliderWidth
                leftLabel: dsTr("-")
                rightLabel: dsTr("+")

                value: 0.47
                onValueChanged: {
                }
            }
        }

        DSeparatorHorizontal {}

        DBaseLine {
            height: contentHeight
            leftMargin: contentLeftMargin
            leftLoader.sourceComponent: DssH2 {
                text: dsTr("Balance")
            }
            rightLoader.sourceComponent: DSliderRect {
                width: sliderWidth
                leftLabel: dsTr("Left")
                rightLabel: dsTr("Right")

                value: 0.5
                onValueChanged: {
                }
            }
        }

        DSeparatorHorizontal {}

        DBaseLine {
            leftLoader.sourceComponent: DssH2 {
            }
        }

        DBaseLine {
            leftLoader.sourceComponent: DssH2 {
                text: dsTr("Microphone")
                font.bold: true
            }
        }

        DSeparatorHorizontal {}

        DSwitchButtonHeader {
            text: dsTr("Enable Microphone")
            active: true
            leftMargin: contentLeftMargin

            onClicked: {

            }
        }

        DSeparatorHorizontal {}

        DBaseExpand {
            id: inputChoose

            header.sourceComponent: DDownArrowHeader {
                text: dsTr("Input Port")
                leftMargin: contentLeftMargin
                onClicked: {
                    outputChoose.expanded = !outputChoose.expanded
                }
            }
            content.sourceComponent: Item {
                width: parent.width
                height: inputList.count * 30

                ListView {
                    id: inputList
                    anchors.fill: parent
                    focus: true
                    currentIndex: 0

                    model: ListModel {
                        ListElement { name: "Inner" }
                        ListElement { name: "Headset" }
                    }

                    delegate: Item {
                        anchors.left: parent.left
                        anchors.leftMargin: contentLeftMargin
                        width: parent.width
                        height: 30

                        Row {
                            spacing: 5
                            anchors.verticalCenter: parent.verticalCenter
                            
                            Image {
                                id: nameImage
                                anchors.verticalCenter: parent.verticalCenter
                                source: "images/select.png"
                                opacity: inputList.currentIndex == index ? 1 : 0
                            }
                            
                            DssH3 {
                                id: nameText
                                anchors.verticalCenter: parent.verticalCenter
                                text: name 
                                color: inputList.currentIndex == index ? Qt.rgba(0, 144/255, 1, 1.0) :dconstants.fgColor
                                font.pixelSize: 12
                            }
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: { 
                                parent.ListView.view.currentIndex = index
                            }
                        }
                    }
                }
            }
        }

        DBaseLine {
            height: contentHeight
            leftMargin: contentLeftMargin
            leftLoader.sourceComponent: DssH2 {
                text: dsTr("Input Volume")
            }
            rightLoader.sourceComponent: DSliderRect {
                width: sliderWidth
                leftLabel: dsTr("-")
                rightLabel: dsTr("+")

                value: 0.47
                onValueChanged: {
                }
            }
        }

        DSeparatorHorizontal {}

        DBaseLine {
            height: contentHeight
            leftMargin: contentLeftMargin
            leftLoader.sourceComponent: DssH2 {
                text: dsTr("Input Level")
            }
            rightLoader.sourceComponent: DSliderRect {
                width: sliderWidth

                value: 0.5
                onValueChanged: {
                }
            }
        }

        DSeparatorHorizontal {}

    }
}
