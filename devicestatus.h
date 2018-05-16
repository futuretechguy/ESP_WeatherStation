#ifndef PAGE_DeviceStatusPage_H
#define PAGE_DeviceStatusPage_H

const char PAGE_DeviceStatusPage[] = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Weather Station</title>
    <script src="https://canvas-gauges.com/download/latest/all/gauge.min.js"></script>

    <style id="style4589">
        .imgtemp {
            stroke-width: 0.99999988;
            fill: #035cbe;
        }

        .deviceimagegrid {
            display: grid;
            grid-template-columns: 1fr 1fr 1fr 1fr 1fr;
            grid-template-rows: .25fr 1fr 1fr .125fr;
            grid-template-areas: ". dtitle dtitle dtitle ." ". tempgauge uvgauge visgauge ." ". humigauge irgauge proxgauge ." ". dfoot dfoot dfoot .";
            grid-auto-rows: 20%;
            grid-gap: 5px;
        }

        .deviceimagegrid>dev {
            border: violet 1px solid;
        }

        .dtitle {
            grid-area: dtitle;
            background: rgb(191, 228, 245);
        }

        .htitle {
            font-weight: bold;
            font-size: 25px;
            color: black;
        }

        .tempgauge {
            grid-area: tempgauge;
            background: rgb(191, 228, 245);
        }

        .uvgauge {
            grid-area: uvgauge;
            background: rgb(191, 228, 245);
        }

        .visgauge {
            grid-area: visgauge;
            background: rgb(191, 228, 245);
        }

        .humigauge {
            grid-area: humigauge;
            background: rgb(191, 228, 245);
        }

        .irgauge {
            grid-area: irgauge;
            background: rgb(191, 228, 245);
        }

        .proxgauge {
            grid-area: proxgauge;
            background: rgb(191, 228, 245);
        }

        .dfoot {
            grid-area: dfoot;
            background: rgb(191, 228, 245);
        }

        @keyframes dash {
            from {
                stroke-dashoffset: 290;
            }
            to {
                stroke-dashoffset: 0;
            }
        }

        .proxpath {
            display: none;
        }


        .proxpath {
            stroke-dasharray: 290;
            stroke-dashoffset: 130;
            /*animation: dash 1.5s 0s forwards infinite;*/
            stroke-width: 5px;
            stroke-linecap: round;
            stroke-linejoin: round;
        }

        /*svg:hover .clprox {
            transform: scale(.5);

        }*/

        @media screen and (max-width: 736px) {
            .deviceimagegrid {
                display: grid;
                grid-template-columns: 1fr;
                grid-template-rows: 25px 1fr 1fr 1fr 1fr 1fr 1fr 25px;
                grid-template-areas: "dtitle" "tempgauge" "humigauge" "uvgauge" "irgauge" "visgauge" "proxgauge" "dfoot";
                grid-gap: 2px;
            }
            .htitle {
                font-weight: bold;
                font-size: 16px;
                color: black;
            }
        }
    </style>
</head>

<body>

    <div align="center" class="deviceimagegrid">
        <div class="dtitle">
            <text class="htitle">Weather Station</text>
        </div>

        <div class="tempgauge">
            <canvas id="Cn_Temp_Img" </canvas>
        </div>
        <div class="uvgauge">
            <canvas id="Cn_UV_Img"></canvas>
        </div>
        <div class="visgauge">
            <canvas id="Cn_Vis_Img"></canvas>
        </div>
        <div class="humigauge">
            <canvas id="Cn_Humid_Img"></canvas>
        </div>
        <div class="irgauge">
            <canvas id="Cn_IR_Img"></canvas>
        </div>
        <div class="proxgauge">
            <svg id="PulseSvg" version="1.1" height="200" width="195" class="svgpulse">
                <path id="Prox_Pulse" class="proxpath" d="M9 70 L 70 70, 90 30, 110 90, 120 50, 130 70, 190 70" stroke="#045cbe" fill="transparent"></path>
                <path style="display:inline;opacity:1;fill:#035cbe;fill-opacity:1;fill-rule:nonzero;stroke:#045cbe;stroke-width:2.0650003;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1"
                    d="m 4.940178,106.70156 a 92.894294,92.894276 0 0 0 92.691007,87.13736 92.894294,92.894276 0 0 0 92.030765,-80.97528 v -6.16208 z m 93.081404,9.4598 a 33.841541,33.841536 0 0 1 33.840728,33.84237 33.841541,33.841536 0 0 1 -33.840728,33.84101 33.841541,33.841536 0 0 1 -33.842096,-33.84101 33.841541,33.841536 0 0 1 33.842096,-33.84237 z"
                    id="Cir_Bot" />
                <path style="display:inline;opacity:0.9;fill:none;fill-opacity:1;fill-rule:nonzero;stroke:#045cbe;stroke-width:2.0650003;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1"
                    d="M 97.631185,8.0491712 A 92.894294,92.894276 0 0 0 4.736667,100.94372 92.894294,92.894276 0 0 0 4.940178,106.70156 H 189.66195 v 6.16208 A 92.894294,92.894276 0 0 0 190.5258,100.94372 92.894294,92.894276 0 0 0 97.631185,8.0491712 Z"
                    id="Cir_Top"></path>
                <path id="Cir_MotMan" d="m 88.123169,185.95343 c -15.03766,-3.31995 -26.077875,-13.87606 -30.248064,-28.92172 -1.207343,-4.35605 -1.207343,-14.56011 0,-18.91615 2.027398,-7.31464 5.340251,-13.06922 10.441407,-18.1372 5.194301,-5.16054 10.887114,-8.43416 18.171616,-10.44949 4.360006,-1.20623 14.573362,-1.20623 18.933372,0 7.2845,2.01533 12.97732,5.28895 18.17162,10.44949 5.10116,5.06798 8.41401,10.82256 10.44141,18.1372 1.20735,4.35604 1.20735,14.5601 0,18.91615 -3.97806,14.35251 -14.40808,24.76259 -28.61303,28.55835 -4.39487,1.17435 -12.822998,1.35142 -17.298331,0.36337 z m 4.298156,-11.2991 c 0.732644,-0.59271 0.943834,-1.41143 1.419681,-5.50342 0.30745,-2.64396 0.811817,-5.41175 1.120844,-6.15067 0.748947,-1.79086 5.29301,-8.77576 5.70911,-8.77576 0.56071,0 0.66881,0.46085 1.13912,4.85628 0.25443,2.37805 0.75151,4.8433 1.12202,5.56483 0.89346,1.73992 8.86999,8.35768 10.07371,8.35768 1.13165,0 2.1366,-1.35665 2.1366,-2.88438 0,-0.90842 -0.65096,-1.80099 -3.14628,-4.31418 -2.08757,-2.10251 -3.27057,-3.62957 -3.51569,-4.53812 -0.20322,-0.75313 -0.55621,-3.83405 -0.78449,-6.84651 -0.22825,-3.0124 -0.58153,-6.09332 -0.78497,-6.84645 -0.20348,-0.75311 -1.43789,-3.20109 -2.74319,-5.43999 -1.30531,-2.23888 -2.31977,-4.35149 -2.25437,-4.69469 0.15778,-0.82793 1.66787,-1.0049 3.61125,-0.42321 1.06433,0.31862 2.30285,1.22958 3.81069,2.80298 1.96559,2.05103 2.38964,2.31605 3.53098,2.20656 1.05399,-0.10093 1.317,-0.30774 1.40327,-1.10251 0.14629,-1.34785 -3.32383,-7.01488 -4.83564,-7.89701 -1.37965,-0.80503 -13.128909,-3.44846 -15.327284,-3.44846 -0.830587,0 -2.293078,0.39612 -3.249982,0.88025 -1.560141,0.78933 -1.973888,1.32472 -4.006049,5.1837 -1.246421,2.36692 -2.659445,4.60767 -3.140052,4.97944 -0.495877,0.38358 -1.568361,0.6797 -2.479625,0.68463 -3.572087,0.0188 -5.474314,1.76565 -3.862091,3.5455 0.593132,0.65479 1.214203,0.76633 4.255938,0.76412 4.149246,-0.002 4.778693,-0.30025 7.243591,-3.42064 2.281425,-2.88816 2.777932,-2.75102 4.494663,1.24152 0.779347,1.81249 1.416991,3.84318 1.416991,4.51266 0,0.74223 -1.081784,3.31088 -2.772442,6.583 -3.071745,5.945 -3.709609,8.01056 -4.073319,13.19025 -0.135967,1.93658 -0.341847,4.07667 -0.457467,4.75588 -0.413877,2.43096 2.852685,3.86898 4.944483,2.17672 z m -0.382317,-46.22069 c 2.342555,-1.65659 2.651735,-4.76786 0.685264,-6.89573 -3.073502,-3.32577 -8.125362,-1.30233 -8.125362,3.25449 0,3.75406 4.302783,5.85986 7.440098,3.64124 z"
                    style="display:inline;fill:#035cbe;fill-opacity:1;stroke-width:1" />
                <circle style="display:inline;opacity:1;fill:#035cbe;fill-opacity:1;fill-rule:nonzero;stroke:#045cbe;stroke-width:0.66499996;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1"
                    id="Cir_NoMot" cx="95.446678" cy="147.04906" r="36.709167" />
                <path style="display:inline;fill:none;stroke:#feffff;stroke-width:0.79374999;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1"
                    d="m 103.45669,105.44045 33.85742,80.4346" id="Right_Line" />
                <path style="fill:none;stroke:#ffffff;stroke-width:0.79374999;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1"
                    d="m 91.001584,105.70659 -33.845229,80.16812 v 0" id="Left_Line" />
                <text id="Prox_Value" style="font-style:bold;font-weight:bold;font-size:14px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#045cbe;fill-opacity:1;stroke:none;stroke-width:0.26458332"
                    x="85" y="104.91247">
                </text>
            </svg>
        </div>
        <div class="dfoot" id="Server_Status">
        </div>
    </div>

    <script type="text/javascript">

        var tempgauge = new RadialGauge({
            renderTo: 'Cn_Temp_Img',
            width: 200,
            height: 200,
            units: "°F",
            title: "Temperature",
            minValue: 0,
            maxValue: 110,
            majorTicks: [
                0,
                10,
                20,
                30,
                40,
                50,
                60,
                70,
                80,
                90,
                100,
                110
            ],
            minorTicks: 2,
            strokeTicks: true,
            highlights: [
                {
                    "from": 0,
                    "to": 50,
                    "color": "rgba(138,43, 226, .6)"
                },
                {
                    "from": 50,
                    "to": 75,
                    "color": "rgba(0, 255, 0, .6)"
                },
                {
                    "from": 75,
                    "to": 110,
                    "color": "rgba(255, 0, 0, .6)"
                }
            ],
            ticksAngle: 225,
            startAngle: 67.5,
            colorMajorTicks: "#ddd",
            colorMinorTicks: "#ddd",
            colorTitle: "#eee",
            colorUnits: "#ccc",
            colorNumbers: "#eee",
            colorPlate: "#035cbe",
            borderShadowWidth: 0,
            borders: true,
            needleType: "arrow",
            needleWidth: 2,
            needleCircleSize: 7,
            needleCircleOuter: true,
            needleCircleInner: false,
            animationDuration: 1000,
            animationRule: "linear",
            colorBorderOuter: "#333",
            colorBorderOuterEnd: "#111",
            colorBorderMiddle: "#222",
            colorBorderMiddleEnd: "#111",
            colorBorderInner: "#111",
            colorBorderInnerEnd: "#333",
            colorNeedleShadowDown: "#333",
            colorNeedleCircleOuter: "#333",
            colorNeedleCircleOuterEnd: "#111",
            colorNeedleCircleInner: "#111",
            colorNeedleCircleInnerEnd: "#222",
            valueBoxBorderRadius: 10,
            colorValueBoxRect: "#eee",
            colorValueBoxRectEnd: "#eee",
            colorValueBoxBackground: "Blue",
            colorValueText: "white",
            valueBoxStroke: 3
        });

        var uvgauge = new RadialGauge({
            renderTo: 'Cn_UV_Img',
            width: 200,
            title: "Ultra Violet",
            height: 200,
            units: "μm",
            minValue: 0,
            maxValue: 14,
            majorTicks: [
                0,
                2,
                4,
                6,
                8,
                10,
                12,
                14
            ],
            minorTicks: 2,
            strokeTicks: true,
            highlights: [
                {
                    "from": 0,
                    "to": 4,
                    "color": "rgba(0, 255, 0, .6)"
                },
                {
                    "from": 4,
                    "to": 8,
                    "color": "rgba(255, 255, 0, .6)"
                },
                {
                    "from": 8,
                    "to": 10,
                    "color": "rgba(255, 153, 0, .6)"
                },
                {
                    "from": 10,
                    "to": 12,
                    "color": "rgba(102, 0, 255, .6)"
                },
                {
                    "from": 12,
                    "to": 14,
                    "color": "rgba(255, 0, 0, .6)"
                }
            ],
            ticksAngle: 225,
            startAngle: 67.5,
            colorMajorTicks: "#ddd",
            colorMinorTicks: "#ddd",
            colorTitle: "#eee",
            colorUnits: "#ccc",
            colorNumbers: "#eee",
            colorPlate: "#035cbe",
            borderShadowWidth: 0,
            borders: true,
            needleType: "arrow",
            needleWidth: 2,
            needleCircleSize: 7,
            needleCircleOuter: true,
            needleCircleInner: false,
            animationDuration: 1000,
            animationRule: "linear",
            colorBorderOuter: "#333",
            colorBorderOuterEnd: "#111",
            colorBorderMiddle: "#222",
            colorBorderMiddleEnd: "#111",
            colorBorderInner: "#111",
            colorBorderInnerEnd: "#333",
            colorNeedleShadowDown: "#333",
            colorNeedleCircleOuter: "#333",
            colorNeedleCircleOuterEnd: "#111",
            colorNeedleCircleInner: "#111",
            colorNeedleCircleInnerEnd: "#222",
            valueBoxBorderRadius: 10,
            colorValueBoxRect: "#eee",
            colorValueBoxRectEnd: "#eee",
            colorValueBoxBackground: "#0000ff",
            colorValueText: "#ffffff",
            valueBoxStroke: 3
        });

        var visgauge = new RadialGauge({
            renderTo: 'Cn_Vis_Img',
            width: 200,
            title: "Light Level",
            height: 200,
            units: "Lux",
            minValue: 0,
            maxValue: 2000,
            majorTicks: [
                0,
                200,
                400,
                600,
                800,
                1000,
                1200,
                1400,
                1600,
                1800,
                2000
            ],
            minorTicks: 2,
            strokeTicks: true,
            highlights: [
                {
                    "from": 0,
                    "to": 600,
                    "color": "rgba(0, 0, 0, .6)"
                },
                {
                    "from": 600,
                    "to": 1200,
                    "color": "rgba(100, 100, 100, .6)"
                },
                {
                    "from": 1200,
                    "to": 2000,
                    "color": "rgba(255, 255, 255, .6)"
                }
            ],
            ticksAngle: 225,
            startAngle: 67.5,
            colorMajorTicks: "#ddd",
            colorMinorTicks: "#ddd",
            colorTitle: "#eee",
            colorUnits: "#ccc",
            colorNumbers: "#eee",
            colorPlate: "#035cbe",
            borderShadowWidth: 0,
            borders: true,
            needleType: "arrow",
            needleWidth: 2,
            needleCircleSize: 7,
            needleCircleOuter: true,
            needleCircleInner: false,
            animationDuration: 1000,
            animationRule: "linear",
            colorBorderOuter: "#333",
            colorBorderOuterEnd: "#111",
            colorBorderMiddle: "#222",
            colorBorderMiddleEnd: "#111",
            colorBorderInner: "#111",
            colorBorderInnerEnd: "#333",
            colorNeedleShadowDown: "#333",
            colorNeedleCircleOuter: "#333",
            colorNeedleCircleOuterEnd: "#111",
            colorNeedleCircleInner: "#111",
            colorNeedleCircleInnerEnd: "#222",
            valueBoxBorderRadius: 10,
            colorValueBoxRect: "#eee",
            colorValueBoxRectEnd: "#eee",
            colorValueBoxBackground: "Blue",
            colorValueText: "white",
            valueBoxStroke: 3
        });


        var humdgauge = new RadialGauge({
            renderTo: 'Cn_Humid_Img',
            width: 200,
            height: 200,
            units: "%",
            title: "Humidity",
            minValue: 0,
            maxValue: 100,
            majorTicks: [
                0,
                10,
                20,
                30,
                40,
                50,
                60,
                70,
                80,
                90,
                100
            ],
            minorTicks: 2,
            strokeTicks: true,
            highlights: [
                {
                    "from": 0,
                    "to": 30,
                    "color": "rgba(255, 153, 0, .6)"
                },
                {
                    "from": 30,
                    "to": 60,
                    "color": "rgba(0, 255, 0, .6)"
                },
                {
                    "from": 60,
                    "to": 100,
                    "color": "rgba(255, 0, 0, .6)"
                }
            ],
            ticksAngle: 225,
            startAngle: 67.5,
            colorMajorTicks: "#ddd",
            colorMinorTicks: "#ddd",
            colorTitle: "#eee",
            colorUnits: "#ccc",
            colorNumbers: "#eee",
            colorPlate: "#035cbe",
            borderShadowWidth: 0,
            borders: true,
            needleType: "arrow",
            needleWidth: 2,
            needleCircleSize: 7,
            needleCircleOuter: true,
            needleCircleInner: false,
            animationDuration: 1000,
            animationRule: "linear",
            colorBorderOuter: "#333",
            colorBorderOuterEnd: "#111",
            colorBorderMiddle: "#222",
            colorBorderMiddleEnd: "#111",
            colorBorderInner: "#111",
            colorBorderInnerEnd: "#333",
            colorNeedleShadowDown: "#333",
            colorNeedleCircleOuter: "#333",
            colorNeedleCircleOuterEnd: "#111",
            colorNeedleCircleInner: "#111",
            colorNeedleCircleInnerEnd: "#222",
            valueBoxBorderRadius: 10,
            colorValueBoxRect: "#eee",
            colorValueBoxRectEnd: "#eee",
            colorValueBoxBackground: "Blue",
            colorValueText: "white",
            valueBoxStroke: 3
        });


        var irgauge = new RadialGauge({
            renderTo: 'Cn_IR_Img',
            width: 200,
            title: "Infrared",
            height: 200,
            units: "cm-1",
            minValue: 0,
            maxValue: 20000,
            majorTicks: [
                0,
                2000,
                4000,
                6000,
                8000,
                12000,
                14000,
                16000,
                18000,
                20000
            ],
            minorTicks: 2,
            strokeTicks: true,
            highlights: [
                {
                    "from": 0,
                    "to": 6000,
                    "color": "rgba(0, 255, 0, .6)"
                },
                {
                    "from": 6000,
                    "to": 14000,
                    "color": "rgba(255, 255, 0, .6)"
                },
                {
                    "from": 14000,
                    "to": 20000,
                    "color": "rgba(255, 0, 0, .6)"
                },
            ],
            ticksAngle: 225,
            startAngle: 67.5,
            colorMajorTicks: "#ddd",
            colorMinorTicks: "#ddd",
            colorTitle: "#eee",
            colorUnits: "#ccc",
            colorNumbers: "#eee",
            colorPlate: "#035cbe",
            borderShadowWidth: 0,
            borders: true,
            needleType: "arrow",
            needleWidth: 2,
            needleCircleSize: 7,
            needleCircleOuter: true,
            needleCircleInner: false,
            animationDuration: 1000,
            animationRule: "linear",
            colorBorderOuter: "#333",
            colorBorderOuterEnd: "#111",
            colorBorderMiddle: "#222",
            colorBorderMiddleEnd: "#111",
            colorBorderInner: "#111",
            colorBorderInnerEnd: "#333",
            colorNeedleShadowDown: "#333",
            colorNeedleCircleOuter: "#333",
            colorNeedleCircleOuterEnd: "#111",
            colorNeedleCircleInner: "#111",
            colorNeedleCircleInnerEnd: "#222",
            valueBoxBorderRadius: 10,
            colorValueBoxRect: "#eee",
            colorValueBoxRectEnd: "#eee",
            colorValueBoxBackground: "Blue",
            colorValueText: "white",
            valueBoxStroke: 3
        });


        var ws = new WebSocket("ws://" + location.hostname + ":81/");  // location.
        var conn_status = document.querySelector("#Server_Status");

        ws.onopen = function (evt) {
            conn_status.innerHTML = "Status: Connected!";
        };

        ws.onmessage = function (evt) {
            ProcessMessage(evt.data);
        };

        ws.onclose = function (evt) {
            alert("Status: Disconnected!");
            conn_status.innerHTML = "Status: Disconnected!";
        };

        ws.onerror = function (error) {
            console.log('WebSocket Error ' + error);
            conn_status.innerHTML = "Status: an error ocured";
        };


        window.onload = function () {

            /*tempgauge.draw();
            uvgauge.draw();
            visgauge.draw();
            humdgauge.draw();
            irgauge.draw();*/

        };



        function ProcessMessage(oMsgvalue) {
            obj = JSON && JSON.parse(oMsgvalue) || $.parseJSON(oMsgvalue);

            if (isNaN(obj.Temperature) === false || obj.Temperature !== "") {
                tempgauge.value = parseFloat(obj.Temperature).toFixed(2);
                tempgauge.draw();
            };
            if (isNaN(obj.Humidity) === false || obj.Humidity !== "") {
                humdgauge.value = parseFloat(obj.Humidity).toFixed(2);
                humdgauge.draw();
            };
            if (isNaN(obj.Proximity) === false || obj.Proximity !== "") {

                if (parseInt(obj.Proximity) > 0) {
                    document.querySelector("#Prox_Pulse").style.animation = "dash 1.5s 0s forwards infinite";
                    document.querySelector("#Prox_Pulse").style.webkitAnimation = "dash 1.5s 0s forwards infinite";
                    document.querySelector("#Cir_NoMot").style.display = "none";
                    document.querySelector("#Prox_Pulse").style.display = "initial";
                } else {
                    document.querySelector("#Prox_Pulse").style.animation = "";
                    document.querySelector("#Prox_Pulse").style.webkitAnimation = "";
                    document.querySelector("#Cir_NoMot").style.display = "initial";
                    document.querySelector("#Prox_Pulse").style.display = "none";
                };
            };
            if (isNaN(obj.UltraViolet) === false || obj.UltraViolet !== "") {
                uvgauge.value = parseFloat(obj.UltraViolet).toFixed(2);
                uvgauge.draw();
            };
            if (isNaN(obj.Visible) === false || obj.Visible !== "") {
                visgauge.value = parseInt(obj.Visible);
                visgauge.draw();
            };
            if (isNaN(obj.Infrared) === false || obj.Infrared !== "") {
                irgauge.value = parseInt(obj.Infrared);
                irgauge.draw();
            };
        };

    </script>

</body>
</html>


)=====";
#endif