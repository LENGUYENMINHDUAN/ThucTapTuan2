/*
  Rui Santos & Sara Santos - Random Nerd Tutorials
  https://RandomNerdTutorials.com/esp32-web-server-beginners-guide/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/
#include "TaskWebserver.h"

// Username and password for web page access
const char *http_username = "admin";
const char *http_password = "admin";

// Assign output variables to GPIO pins
//const int output10 = 10;
const int singleLED = 48; //single LEDs D13-> GPIO48
bool rgbOn = false;
bool singleLEDOn = false;


// Create a web server object
WebServer server(80);

float tempWeb = 0;
float humiWeb = 0;
int moistureWeb = 0;
int lightWeb = 0;
float distanceWeb = 0;

// Function to authenticate user
bool isAuthenticated()
{
    if (!server.authenticate(http_username, http_password))
    {
        server.requestAuthentication();
        return false;
    }
    return true;
}



// Function to handle the root URL and show the current states
void handleRoot()
{
    if (!isAuthenticated())
        return;

    String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<link rel=\"icon\" href=\"data:,\">";
    html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
    html += ".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
    html += ".button2 { background-color: #555555; }</style></head>";
    html += "<body><h1>ESP32 Web Server</h1>";

    // Sensor values
    html += R"rawliteral(
    <h2>Sensor Readings: </h2>
    <p>Temperature: <span id="tempWeb">--</span> C</p>
    <p>Humidity: <span id="humiWeb">--</span> %</p>
    <p>Soil moisture: <span id="moistureWeb">--</span></p>
    <p>Light Level: <span id="lightWeb">--</span></p>
    <p>Distance: <span id="distanceWeb">--</span> cm</p>

    <script>
    function updateSensor() {
        fetch('/sensor-data')
            .then(response => response.json())
            .then(data => {
                document.getElementById('tempWeb').textContent = data.tempWeb;
                document.getElementById('humiWeb').textContent = data.humiWeb;
                document.getElementById('moistureWeb').textContent = data.moistureWeb;
                document.getElementById('lightWeb').textContent = data.lightWeb;
                document.getElementById('distanceWeb').textContent = data.distanceWeb;
            });
    }
    setInterval(updateSensor, 5000);
    updateSensor(); // initial fetch
    </script>
    )rawliteral";

    // RGB
    html += "<h2>LED RGB - State: " + String(rgbOn ? "ON" : "OFF") + "</h2>";
    if (rgbOn == 0)
    {
        
        html += "<p><a href=\"/rgb/on\"><button class=\"button\">Turn ON</button></a></p>";
    }
    else 
    {
        html += "<p><a href=\"/rgb/off\"><button class=\"button button2\">Turn OFF</button></a></p>";
    }

    html += "<p><a href=\"/rgb/switch\"><button class=\"button\">Next Color</button></a></p>";

    
    // Display Single LED controls
    html += "<h2>Single LED - State " + String(singleLEDOn ? "ON" : "OFF") + "</h2>";
    if (singleLEDOn)
    {
        html += "<p><a href=\"/led/off\"><button class=\"button button2\">Turn OFF</button></a></p>";
    }
    else
    {
        html += "<p><a href=\"/led/on\"><button class=\"button\">Turn ON</button></a></p>";
    }


    html += "</body></html>";
    server.send(200, "text/html", html);
}



//handle turning RGB off
void handleRGBOff() {
    if (!isAuthenticated()) return;
    RGBoff();
    rgbOn = false;
    handleRoot();
}

//function handle turning RGB on
void handleRGBOn() {
    if (!isAuthenticated()) return;
    colorNumber = 0;
    loopRGB();
    rgbOn = true;
    handleRoot();
}

void handleRGBSwitch()
{
    if (!isAuthenticated()) return;
    if (rgbOn = true)
    {
        colorNumber = (colorNumber + 1) % 8;
        rgb.setPixelColor(0, colors[colorNumber]);
        rgb.show();
        handleRoot();
    }
}
// Function to handle turning LED on
void handlesingleLEDOn()
{
    if (!isAuthenticated())
        return;
    singleLEDOn = true;
    digitalWrite(singleLED, HIGH);
    handleRoot();
}

// Function to handle turning LED off
void handlesingleLEDOff()
{
    if (!isAuthenticated())
        return;
    singleLEDOn = false;
    digitalWrite(singleLED, LOW);
    handleRoot();
}
void InitWebsever()
{
    // Initialize the output variables as outputs
    pinMode(singleLED, OUTPUT);
    // Set outputs to LOW
    digitalWrite(singleLED, LOW);
    colorNumber = 8; // off

    // Connect to Wi-Fi network
    Serial.print("Connecting to ");
    Serial.println("ACLAB");
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Set up the web server to handle different routes with authentication
    server.on("/", handleRoot);
    server.on("/rgb/on", handleRGBOn);
    server.on("/rgb/off", handleRGBOff);
    server.on("/rgb/switch", handleRGBSwitch);
    server.on("/led/on", handlesingleLEDOn);
    server.on("/led/off", handlesingleLEDOff);

    // Cảm biến
    server.on("/sensor-data", []() 
    {
        tempWeb = getValueDHT20_temp();
        humiWeb = getValueDHT20_humi();
        moistureWeb = MoistureGet();
        lightWeb = LightGet();
        distanceWeb = DistanceCalculate();

        String json = "{";
        json += "\"tempWeb\":" + String(tempWeb, 1) + ",";
        json += "\"humiWeb\":" + String(humiWeb, 1) + ",";
        json += "\"moistureWeb\":" + String(moistureWeb) + ",";
        json += "\"lightWeb\":" + String(lightWeb) + ",";
        json += "\"distanceWeb\":" + String(distanceWeb, 1);
        json += "}";

        server.send(200, "application/json", json);
    });
    // Start the web server
    server.begin();
    Serial.println("HTTP server started");
}

void WebSeverloop()
{
    // Handle incoming client requests
    if (WiFi.status() != WL_CONNECTED)
    {
        return;
    }
    server.handleClient();
}