#include <WiFi.h>
#include <WebServer.h>
#include "time.h"

// --- Configuration ---
const char *ssid = "vBakel";          // Replace with your WiFi network name
const char *password = "1001100111";  // Replace with your WiFi password
const int MOTOR_PIN = 4;              // GPIO pin connected to the motor driver control
const int LED_ALIVE_PIN = 2;          // Alive LED Pin
const int AliveOnPeriodTime = 100;
const int AliveOffPeriodTime = 2000;
const int UPDATE_INTERVAL_MS = 1000;  // How often the browser checks the status (1 second)
const char *AUTH_USERNAME = "admin";
const char *AUTH_PASSWORD = "choco";

// NTP Server
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

// Create a WebServer object on port 80
WebServer server(80);

// --- State Variables ---
unsigned long AliveLedStatusChanged = 0;
unsigned long motorDurationMs = 5000; // Default motor run time in milliseconds (5 seconds)
unsigned long motorStartTime = 0;     // Time when the motor was last turned ON
bool isMotorRunning = false;          // Current state of the motor
// FIX: New variable to store the timestamp of the last feed action
char lastActionTime[128] = "Nog niet gevoerd"; 

// --- HTML Templates (No changes needed) ---
// ... (HTML_HEADER, HTML_TIME_FORM, HTML_FOOTER are unchanged)
const char HTML_HEADER[] PROGMEM = R"=====(
<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>
<title>Geitjes portaal</title>
<style>
body{text-align: center; font-family: sans-serif;}
.state{font-size: 20px; font-weight: bold;}
.button{border: none; background-color: dodgerblue; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; border-radius: 8px;}
.form-container{margin-top: 20px; border: 1px solid #ccc; padding: 15px; display: inline-block; border-radius: 5px;}
.running{color: green;} .stopped{color: red;}
.btn-start{background-color: #28a745;} .btn-stop{background-color: #dc3545;}
</style>
</head><body>
<h2>Micky & Molly voermachine</h2>
<hr>
)=====";

const char HTML_TIME_FORM[] PROGMEM = R"=====(
<div class='form-container'>
<form action='/settime' method='get'>
<h4>Admin area</h4>
<label for='duration'>Duration (milliseconds):</label><br>
<input type='number' id='duration' name='duration' value='%lu' min='100' max='120000' required><br><br>
<input class='button' type='submit' value='Set Duration'></form>
</div>
<hr>
)=====";

const char HTML_FOOTER[] PROGMEM = R"=====(
<script>
const statusElement = document.getElementById('statusText');
const buttonLink = document.getElementById('motorLink');
const buttonElement = document.getElementById('motorButton');
const durationElement = document.getElementById('durationDisplay');
const lastRunElement = document.getElementById('lastRunDisplay');
const interval = %d; // Polling interval from ESP32

function updateStatus(status) {
    // Update Status Text and Color
    if (status.running) {
        statusElement.textContent = "Er wordt gevoerd";
        statusElement.className = "state running";
        buttonElement.textContent = "Stop voeren";
        buttonElement.className = "button btn-stop";
    } else {
        statusElement.textContent = "Er wordt niet gevoerd";
        statusElement.className = "state stopped";
        buttonElement.textContent = "Start voeren";
        buttonElement.className = "button btn-start";
    }
    // Update Duration Display (in case it was changed)
    lastRunElement.textContent = status.lastRun;
    durationElement.textContent = status.duration + " ms";
}

function pollStatus() {
    fetch('/status')
        .then(response => response.json())
        .then(data => {
            updateStatus(data);
        })
        .catch(error => console.error('Error fetching status:', error));
}

// Start polling immediately and then every 'interval' milliseconds
pollStatus(); 
setInterval(pollStatus, interval); 
</script>
</body></html>
)=====";


// --- Helper Functions ---
void ControlAliveLed()
{
    bool on = digitalRead(LED_ALIVE_PIN);
    unsigned long now = millis();

    if (on)
    {
        if (now - AliveLedStatusChanged >= AliveOnPeriodTime)
        {
            AliveLedStatusChanged = now;
            digitalWrite(LED_ALIVE_PIN, LOW);
        }
    }
    else
    {
        if (now - AliveLedStatusChanged >= AliveOffPeriodTime)
        {
            AliveLedStatusChanged = now;
            digitalWrite(LED_ALIVE_PIN, HIGH);
        }
    }
}

// FIX: Helper function to get and format current local time
void updateLastActionTime() {
    tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        strftime(lastActionTime, sizeof(lastActionTime), "%d-%m-%Y om %H:%M:%S", &timeinfo);
    } else {
        sprintf(lastActionTime, "Tijd onbekend");
    }
}

tm GetLocalTime()
{
    tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
    }
    return timeinfo;
}


// --- Optimized HTML Content Function ---
void sendOptimizedHTML()
{
    char buffer[2048];

    // 1. Send HTML Header
    server.sendContent_P(HTML_HEADER);

    // 2. Insert Motor Status and Toggle Button with unique IDs for JS
    const char *statusText = isMotorRunning ? "Er wordt gevoerd" : "Er wordt niet gevoerd";
    const char *statusClass = isMotorRunning ? "running" : "stopped";

    sprintf(buffer,
            "<p>Voer Status: <span id='statusText' class='state %s'>%s</span></p>"
            // FIX: Use the global lastActionTime variable directly here
            "<p>Laatste actie: <span id='lastRunDisplay'>%s</span></p>" 
            "<p>Motor Duration Set: <span id='durationDisplay'>%lu ms</span></p>"
            "<p><a id='motorLink' href='/run'><button id='motorButton' class='button %s'>%s</button></a></p>",
            statusClass, statusText,
            lastActionTime, // FIX: Use stored time
            motorDurationMs,
            isMotorRunning ? "btn-stop" : "btn-start",
            isMotorRunning ? "Stop voeren" : "Start voeren");
    server.sendContent(buffer);

    // 3. Send Time Input Form (formatted with current duration)
    sprintf(buffer, HTML_TIME_FORM, motorDurationMs);
    server.sendContent(buffer);

    // 4. Send HTML Footer with JavaScript (formatted with polling interval)
    sprintf(buffer, HTML_FOOTER, UPDATE_INTERVAL_MS);
    server.sendContent(buffer);
}

// --- Handler for Status API ---
void handleStatus()
{
    char response[128 + 128]; // Increased buffer size for safety with JSON string

    // FIX: Send the stored lastActionTime string
    sprintf(response, "{\"running\":%s,\"lastRun\":\"%s\",\"duration\":%lu}", 
        isMotorRunning ? "true" : "false", 
        lastActionTime, // FIX: Send stored time
        motorDurationMs);

    server.send(200, "application/json", response);
}

// --- Handler Functions ---
void handleRoot()
{
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", "");
    sendOptimizedHTML();
    server.client().stop();
}

void handleRun()
{
    if (!isMotorRunning)
    {
        // Start motor
        digitalWrite(MOTOR_PIN, HIGH);
        motorStartTime = millis();
        isMotorRunning = true;
        updateLastActionTime(); // FIX: Update time when starting
        char msg[100];
        sprintf(msg, "Motor started for: %lu ms", motorDurationMs);
        Serial.println(msg);
    }
    else
    {
        // Stop motor manually
        digitalWrite(MOTOR_PIN, LOW);
        motorStartTime = 0;
        isMotorRunning = false;
        updateLastActionTime(); // FIX: Update time when manually stopping
        Serial.println("Motor stopped manually.");
    }
    server.sendHeader("Location", "/");
    server.send(303);
    server.client().stop();
}

void handleSetTime()
{
    // Check for authentication before allowing the duration change
    if (!server.authenticate(AUTH_USERNAME, AUTH_PASSWORD))
    {
        server.requestAuthentication();
        return;
    }

    if (server.hasArg("duration"))
    {
        long newDuration = server.arg("duration").toInt();
        if (newDuration > 0)
        {
            motorDurationMs = newDuration;
            char msg[100];
            sprintf(msg, "New motor duration set to: %lu ms", motorDurationMs);
            Serial.println(msg);
        }
    }
    server.sendHeader("Location", "/");
    server.send(303);
    server.client().stop();
}

// --- Setup and Loop ---
void setup()
{
    Serial.begin(115200);
    pinMode(LED_ALIVE_PIN, OUTPUT);
    pinMode(MOTOR_PIN, OUTPUT);
    digitalWrite(MOTOR_PIN, LOW);

    char msg[32];
    sprintf(msg, "Connecting to %s", ssid);
    Serial.print(msg);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected.");
    Serial.print("Access Web Server at: http://");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/run", handleRun);
    server.on("/settime", handleSetTime);
    server.on("/status", handleStatus);

    server.begin();
    Serial.println("HTTP server started");

    // Init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // Initial time update
    updateLastActionTime(); 
}

void loop()
{
    ControlAliveLed();
    server.handleClient();

    // Check if the motor's timed duration has elapsed
    if (isMotorRunning && motorStartTime > 0)
    {
        if (millis() - motorStartTime >= motorDurationMs)
        {
            // Motor stops automatically
            digitalWrite(MOTOR_PIN, LOW);
            isMotorRunning = false;
            motorStartTime = 0;
            updateLastActionTime(); // FIX: Update time when stopping due to timer
            
            char msg[100];
            sprintf(msg, "Motor stopped automatically after %lu ms", motorDurationMs);
            Serial.println(msg);
        }
    }
}