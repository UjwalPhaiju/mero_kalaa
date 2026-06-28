#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>        // ← Important
#include <ESPmDNS.h>
#include <Arduino.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* mdnsName = "led";

const int ledPin = 2;
const int pwmFreq = 5000;
const int pwmResolution = 8;

int currentDuty = 0;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");     // This works with ESPAsyncWebServer

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
               void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_DATA) {
    String msg = String((char*)data, len);
    if (msg.startsWith("pwm:")) {
      int duty = msg.substring(4).toInt();
      if (duty >= 0 && duty <= 255) {
        currentDuty = duty;
        ledcWrite(ledPin, currentDuty);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  ledcAttach(ledPin, pwmFreq, pwmResolution);
  ledcWrite(ledPin, 0);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  if (MDNS.begin(mdnsName)) {
    MDNS.addService("http", "tcp", 80);
    Serial.printf("→ http://%s.local\n", mdnsName);
  }

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 LED Control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {font-family:Arial; text-align:center; margin-top:50px; background:#111; color:#fff;}
    h1 {color:#0f0;}
    button {padding:15px 32px; margin:10px; font-size:18px; border:none; border-radius:10px; cursor:pointer;}
    #onBtn {background:#0f0; color:black;}
    #offBtn {background:#f00; color:white;}
    input[type=range] {width:85%; accent-color:#0f0; height:12px;}
    #value {font-size:48px; font-weight:bold; margin:20px 0 5px; color:#0f0;}
  </style>
</head>
<body>
  <h1>ESP32 LED Control</h1>
  <button id="onBtn">FULL ON</button>
  <button id="offBtn">OFF</button>
  
  <div style="margin:40px auto; max-width:500px;">
    <input type="range" id="slider" min="0" max="100" value="0">
    <div id="value">0</div>
    <div id="percent">0%</div>
  </div>

  <script>
    let ws = new WebSocket('ws://' + window.location.hostname + '/ws');
    let lastSend = 0;
    const slider = document.getElementById('slider');
    const valueEl = document.getElementById('value');
    const percentEl = document.getElementById('percent');

    ws.onopen = () => console.log('WebSocket Connected');

    function sendPWM(percent) {
      if (Date.now() - lastSend > 15) {
        const duty = Math.round(percent * 2.55);
        ws.send('pwm:' + duty);
        lastSend = Date.now();
      }
    }

    slider.addEventListener('input', () => {
      const p = parseInt(slider.value);
      valueEl.textContent = p;
      percentEl.textContent = p + '%';
      sendPWM(p);
    });

    document.getElementById('onBtn').onclick = () => { slider.value=100; valueEl.textContent=100; percentEl.textContent='100%'; sendPWM(100); };
    document.getElementById('offBtn').onclick = () => { slider.value=0; valueEl.textContent=0; percentEl.textContent='0%'; sendPWM(0); };

    fetch('/state').then(r=>r.text()).then(d => {
      if(d){
        const p = Math.round((+d * 100)/255);
        slider.value = p; valueEl.textContent = p; percentEl.textContent = p + '%';
      }
    });
  </script>
</body>
</html>
)rawliteral";
    request->send(200, "text/html", html);
  });

  server.on("/state", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(currentDuty));
  });

  server.begin();
  Serial.println("Ready!");
}

void loop() {
  ws.cleanupClients();
  delay(10);
}