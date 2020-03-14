var websocket = null; // websocket instance
var localhost = "192.168.1.65";
var b = document.getElementById('btnWS');
var buttonClicked = false;

// Initialize the websocket
function init() {
    if (window.location.hostname != "") {
        localhost = window.location.hostname;
    }

}

function doConnect() { // makes a connection and defines callbacks
    if (b.innerText == "Start Webcam") {
        b.disabled = true;
        websocket = new WebSocket("ws://" + localhost + "/stream");
        websocket.onopen = function (evt) {
            onOpen(evt)
        };
        websocket.onclose = function (evt) {
            onClose(evt)
        };
        websocket.onmessage = function (evt) {
            onMessage(evt)
        };
        websocket.onerror = function (evt) {
            onError(evt)
        };
    } else {
        //      writeToScreen("Disconnecting ...");
        websocket.close();
    }
}

function onOpen(evt) { // when handshake is complete:
    //*** Change the text of the button to read "Stop Webcam" ***//
    b.textContent = 'Stop Webcam';
    //*** Change the title attribute of the button to display "Click to stop webcam" ***//
    b.title = 'Click to stop webcam';
    //*** Enable the button ***//
    b.disabled = false;

    buttonClicked = false;
}

function onClose(evt) { // when socket is closed:
    //*** Change the text of the button to read "Start Webcam" ***//
    b.textContent = 'Start Webcam';
    //*** Change the title attribute of the button to display "Click to start webcam" ***//
    b.title = 'Click to start webcam';
    //*** Enable the button ***//
    b.disabled = false;
    document.getElementById("timestamp").textContent = "";

    // If the user never actually clicked the button to stop the webcam, reconnect.
    if (buttonClicked == false) {
        doConnect();
    }
    buttonClicked = false;
}

function onMessage(msg) { // when client receives a WebSocket message because a new image is ready:
    //*** Display a new timestamp ***//
    var d = new Date();
    document.getElementById("timestamp").textContent = d;

    // Get the image just taken from WiFi chip's RAM.
    var image = document.getElementById('image');
    var reader = new FileReader();
    reader.onload = function (e) {
        var img_test = new Image();
        img_test.onload = function () {
            image.src = e.target.result;
        };
        img_test.onerror = function () {
            ;
        };
        img_test.src = e.target.result;
    };
    reader.readAsDataURL(msg.data);
}


function onError(evt) { // when an error occurs
    websocket.close();

    //*** Change the text of the button to read "Start Webcam" ***//
    b.textContent = 'Start Webcam';
    //*** Change the title attribute of the button to display "Click to start webcam" ***//
    b.title = 'Click to start webcam';
    //*** Enable the button ***//
    b.disabled = false;
    document.getElementById("timestamp").textContent = "";


    buttonClicked = false;
}

// Set up event listeners
//*** When the button is clicked, disable it and set the 'buttonClicked' variable to true, and depending on whether a Websocket is open or not, either run "doConnect()" or "websocket.close()" ***//

b.onclick = function () {
    b.disabled = true;
    buttonClicked = true;
    var text = b.textContent;
    if (text == 'Start Webcam') {
        doConnect();
    } else {
        websocket.close();
    }
}

// Open Websocket as soon as page loads
window.addEventListener("load", init, false);
