// -------------------------------------------------------------------------------------------------
//
// Copyright (C) Juniarto Saputra (juniarto.wongso@gmail.com). All rights reserved.
//
// This software, including documentation, is protected by copyright controlled by
// the contributor(s). All rights are reserved. Copying, including reproducing, storing,
// adapting or translating, any or all of this material requires the prior written
// consent of the contributor(s).
//
// -------------------------------------------------------------------------------------------------

import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtCharts 2.2

import LogViewer 1.0

Item {

    FileDialog {
        id: _fileDialog
        title: qsTr("Please choose a log (*.json) file")
        nameFilters: ["Json files (*.json)", "All files (*)"]
        selectFolder: false
        selectMultiple: false
        onAccepted: {
            _logViewer.logFilePath = _fileDialog.fileUrl;
            root.title = _logViewer.logFilePath;
        }
    }

    function loadSeries() {
        _seriesTemperature.clear();
        _seriesHeight.clear();

        for (var data in _logViewer.sensorDataList) {

            _seriesTemperature.append(_logViewer.sensorDataList[data].timestamp,
                                      _logViewer.sensorDataList[data].temperature);
            _seriesHeight.append(_logViewer.sensorDataList[data].timestamp,
                                 _logViewer.sensorDataList[data].height);
        }
    }

    Timer {
        id: _timer
        interval: 500
        running: false
        repeat: false
        onTriggered: {
            if (!_logViewer.loaded && _logViewer.logFilePath.length > 0) {
                _logViewer.parse( );
            }
        }
    }


    LogViewer {
        id: _logViewer

        onLoadedChanged: {

            if (!loaded) {
                _busyIndicator.running = true;
                _timer.start();
            }
            else {
                loadSeries();

                // Default range 10% of data count
                var defaultEnd = _logViewer.count * 0.1;

                _seriesTemperature.axisY.max = _logViewer.maxTemperatureRange(0, defaultEnd);
                _seriesTemperature.axisY.min = _logViewer.minTemperatureRange(0, defaultEnd);
                _seriesTemperature.axisX.max = _logViewer.maxTimestampRange(0, defaultEnd);
                _seriesTemperature.axisX.min = _logViewer.minTimestampRange(0, defaultEnd);
                _seriesHeight.axisY.max = _logViewer.maxHeightRange(0, defaultEnd);
                _seriesHeight.axisY.min = _logViewer.minHeightRange(0, defaultEnd);

                _seriesTemperature.axisY.applyNiceNumbers();
                _seriesHeight.axisY.applyNiceNumbers();
                _busyIndicator.running = false;
            }
        }

        Window {
            id: root
            visible: true
            title: qsTr("LogViewer")
            visibility: Window.Maximized

            Button {
                id: _openFile
                width: parent.width - 400
                anchors.top: parent.top
                anchors.left: parent.left
                text: qsTr("Open a log (*.json) file")
                onClicked: {
                    _fileDialog.visible = true;
                }
            }

            ComboBox {
                id: _comboBoxSerie
                currentIndex: 0
                textRole: "text"
                model: ListModel {
                    id: _serieItems
                    ListElement { text: qsTr("Temperature"); type: 0 }
                    ListElement { text: qsTr("Height"); type: 1 }
                    ListElement { text: qsTr("Both"); type: 2 }
                }
                width: 200
                anchors.top: parent.top
                anchors.left: _openFile.right
            }

            ComboBox {
                id: _comboBoxRange
                currentIndex: 0
                textRole: "text"
                model: ListModel {
                    id: _rangeItems
                    ListElement { text: qsTr("Data range: 10%"); zoom: 0.1 }
                    ListElement { text: qsTr("Data range: 25%"); zoom: 0.25 }
                    ListElement { text: qsTr("Data range: 50%"); zoom: 0.5 }
                    ListElement { text: qsTr("Data range: 75%"); zoom: 0.75 }
                    ListElement { text: qsTr("Data range: 100%"); zoom: 1 }
                }
                width: 200
                anchors.right: parent.right
                onCurrentIndexChanged: {

                    if (_logViewer.loaded) {
                        var zoomLvl = _rangeItems.get(currentIndex).zoom;
                        var endIdx = _logViewer.count * zoomLvl;
                        _seriesTemperature.axisY.max = _logViewer.maxTemperatureRange(0, endIdx);
                        _seriesTemperature.axisY.min = _logViewer.minTemperatureRange(0, endIdx);
                        _seriesTemperature.axisX.max = _logViewer.maxTimestampRange(0, endIdx);
                        _seriesTemperature.axisX.min = _logViewer.minTimestampRange(0, endIdx);
                        _seriesHeight.axisY.max = _logViewer.maxHeightRange(0, endIdx);
                        _seriesHeight.axisY.min = _logViewer.minHeightRange(0, endIdx);

                        _seriesTemperature.axisY.applyNiceNumbers();
                        _seriesHeight.axisY.applyNiceNumbers();
                    }
                }
            }

            ChartView {
                id: _chartView
                width: parent.width
                height: parent.height - _openFile.height
                anchors.top: _openFile.bottom
                title: _logViewer.loaded ? qsTr("Drag and drop to move/scroll the data range") :
                                           qsTr("Please open a log file")
                antialiasing: true
                theme: ChartView.ChartThemeDark

                ToolTip.delay: 100
                ToolTip.timeout: 5000

                MouseArea {
                    id: _mouseArea
                    anchors.fill: parent
                    property int lastX: 0
                    property int lastY: 0
                    onPressed: {
                        lastX = mouse.x;
                        lastY = mouse.y;
                    }

                    onPositionChanged: {
                        if (lastX !== mouse.x) {
                            _chartView.scrollRight(lastX - mouse.x);
                            lastX = mouse.x;
                        }
                        if (lastY !== mouse.y) {
                            _chartView.scrollDown(lastY - mouse.y);
                            lastY = mouse.y;
                        }
                    }
                }

                DateTimeAxis {
                    id: _timeAxisX
                    titleText: qsTr("Time")
                    format: "hh:mm:ss"
                    tickCount: 20
                }

                ValueAxis {
                    id: _temperatureAxisY
                    titleText: qsTr("Temperature")
                    tickCount: 8
                    visible: _comboBoxSerie.currentIndex === 0 ||
                             _comboBoxSerie.currentIndex === 2
                }

                ValueAxis {
                    id: _heightAxisY
                    titleText: qsTr("Height")
                    tickCount: 8
                    visible: _comboBoxSerie.currentIndex === 1 ||
                             _comboBoxSerie.currentIndex === 2
                }

                ScatterSeries {
                    id: _seriesTemperature
                    name: "Temperature"
                    axisX: _timeAxisX
                    axisY: _temperatureAxisY
                    visible: _comboBoxSerie.currentIndex === 0 ||
                             _comboBoxSerie.currentIndex === 2
                    markerSize: {
                        switch (_comboBoxRange.currentIndex) {
                        case 0:
                            return 15.0;
                        case 1:
                            return 10.0;
                        case 2:
                            return 5.0;
                        default:
                            return 3.0;
                        }
                    }
                    borderWidth: 0

                    onHovered: {
                        if (state) {
                            _chartView.ToolTip.show("Time: " +
                                                    _logViewer.msEpochToString(point.x) +
                                                    "\nTemperature: " + point.y);
                        }
                        else {
                            _chartView.ToolTip.hide();
                        }

                    }
                }

                LineSeries {
                    id: _seriesHeight
                    name: "Height"
                    axisX: _timeAxisX
                    axisY: _heightAxisY
                    visible: _comboBoxSerie.currentIndex === 1 ||
                             _comboBoxSerie.currentIndex === 2

                    onHovered: {
                        if (state) {
                            _chartView.ToolTip.show("Time: " +
                                                    _logViewer.msEpochToString(point.x) +
                                                    "\nHeight: " + point.y);
                        }
                        else {
                            _chartView.ToolTip.hide();
                        }
                    }
                }
            }

            BusyIndicator {
                id: _busyIndicator
                anchors.centerIn: parent
                running: false
            }
        }
    }
}
