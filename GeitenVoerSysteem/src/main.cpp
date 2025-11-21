#include <WiFi.h>
#include <WebServer.h>

// --- Configuration ---
const char *ssid = "vBakel";          // Replace with your WiFi network name
const char *password = "1001100111";  // Replace with your WiFi password
const int MOTOR_PIN = 4;              // GPIO pin connected to the motor driver control
const int LED_ALIVE_PIN = 2;          // Alive LED Pin
const int AliveOnPeriodTime = 100;
const int AliveOffPeriodTime = 2000;

// Create a WebServer object on port 80
WebServer server(80);

// --- State Variables ---
unsigned long AliveLedStatusChanged = 0;
unsigned long motorDurationMs = 5000; // Default motor run time in milliseconds (5 seconds)
unsigned long motorStartTime = 0;     // Time when the motor was last turned ON
bool isMotorRunning = false;          // Current state of the motor

// --- HTML Templates (Stored in Flash Memory) ---

// Static parts of the HTML page
const char HTML_HEADER[] PROGMEM = R"=====(
<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>
<title>Geitjes portaal</title>
<style>
body{text-align: center; font-family: sans-serif;}
.state{font-size: 20px; font-weight: bold;}
.button{background-color: #007bff; border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; border-radius: 8px;}
.form-container{margin-top: 20px; border: 1px solid #ccc; padding: 15px; display: inline-block; border-radius: 5px;}
.running{color: green;} .stopped{color: red;}
.btn-start{background-color: #28a745;} .btn-stop{background-color: #dc3545;}
</style>
</head><body>
<h2>Mick & Moel voermachine</h2>
<hr>
)=====";

const char HTML_TIME_FORM[] PROGMEM = R"=====(
<div class='form-container'>
<form action='/settime' method='get'>
<label for='duration'>Duration (milliseconds):</label><br>
<input type='number' id='duration' name='duration' value='%lu' min='100' required><br><br>
<input class='button' type='submit' value='Set Duration'></form>
</div>
<hr>
)=====";

const char HTML_FOOTER[] PROGMEM = "</body></html>";

// --- Handle Alive LED (No change needed, it's efficient) ---
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

// --- Optimized HTML Content Function ---
void sendOptimizedHTML()
{
    // Pre-allocate buffer for dynamic parts
    char buffer[1024];
    
    // 1. Send HTML Header
    server.sendContent_P(HTML_HEADER);

    // 2. Insert Motor Status dynamically
    const char* statusText = isMotorRunning ? "Er wordt gevoerd" : "Er wordt niet gevoerd";
    const char* statusClass = isMotorRunning ? "running" : "stopped";
    sprintf(buffer, "<p>Voer Status: <span class='state %s'>%s</span></p>", statusClass, statusText);
    server.sendContent(buffer);

    // 3. Insert Toggle Button dynamically
    const char* buttonText = isMotorRunning ? "STOP Motor" : "START Motor";
    const char* buttonClass = isMotorRunning ? "btn-stop" : "btn-start";
    
    sprintf(buffer, 
        "<p>Motor Duration Set: %lu ms</p>"
        "<p><a href='/run'><button class='button %s'>%s</button></a></p>",
        motorDurationMs, buttonClass, buttonText);
    server.sendContent(buffer);
    
    // 4. Send Time Input Form (formatted with current duration)
    sprintf(buffer, HTML_TIME_FORM, motorDurationMs);
    server.sendContent(buffer);

    // 5. Send HTML Footer
    server.sendContent_P(HTML_FOOTER);
}

// --- Handler Functions ---

// Handles the root page ("/")
void handleRoot()
{
    // Start the response, but don't close it yet
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", ""); 
    
    sendOptimizedHTML();
    
    // Finish the response
    server.client().stop();
}

// Handles the motor run request ("/run")
void handleRun()
{
    // ... (Your existing logic for handling run/stop)
    if (!isMotorRunning)
    {
        digitalWrite(MOTOR_PIN, HIGH);
        motorStartTime = millis();
        isMotorRunning = true;
        char msg[100];
        sprintf(msg, "Motor started for: %lu ms", motorDurationMs);
        Serial.println(msg);
    }
    else
    {
        digitalWrite(MOTOR_PIN, LOW);
        motorStartTime = 0;
        isMotorRunning = false;
        Serial.println("Motor stopped manually.");
    }
    // ... (Existing logic ends)

    // Redirect back to the root page to update status
    server.sendHeader("Location", "/");
    server.send(303);
}

// Handles the duration setting request ("/settime?duration=XXX")
void handleSetTime()
{
    // ... (Your existing logic for handling set time)
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
    // ... (Existing logic ends)

    // Redirect back to the root page
    server.sendHeader("Location", "/");
    server.send(303);
}

// --- Setup and Loop ---

void setup()
{
    // Increase Serial speed to 115200 for faster output
    Serial.begin(115200); 
    pinMode(LED_ALIVE_PIN, OUTPUT);
    pinMode(MOTOR_PIN, OUTPUT);
    digitalWrite(MOTOR_PIN, LOW);

    // Connect to WiFi (No change needed)
    char msg[32];
    sprintf(msg, "Connecting to %s", ssid);
    Serial.print(msg);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500); // Reduced delay for faster connection time
        Serial.print(".");
    }

    Serial.println("\nWiFi connected.");
    Serial.print("Access Web Server at: http://");
    Serial.println(WiFi.localIP());

    // Set up web server routes (No change needed)
    server.on("/", handleRoot);
    server.on("/run", handleRun);
    server.on("/settime", handleSetTime);

    server.begin();
    Serial.println("HTTP server started");
}

void loop()
{
    ControlAliveLed();

    server.handleClient(); // Handles web client requests

    // Check if the motor's timed duration has elapsed (No change needed, it's efficient)
    if (isMotorRunning && motorStartTime > 0)
    {
        if (millis() - motorStartTime >= motorDurationMs)
        {
            digitalWrite(MOTOR_PIN, LOW);
            isMotorRunning = false;
            motorStartTime = 0;
            char msg[100];
            sprintf(msg, "Motor stopped automatically after %lu ms", motorDurationMs);
            Serial.println(msg);
        }
    }
}