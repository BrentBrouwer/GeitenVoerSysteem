#include "AsyncWifiServer.h"
#include <Arduino.h>

const char *htmlPage = R"(
<!DOCTYPE HTML><html>
<head>
  <title>Geitjes</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">

    <style>
        /* The switch - the box around the slider */
        .switch {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;
            }

            /* Hide default HTML checkbox */
            .switch input {
            opacity: 0;
            width: 0;
            height: 0;
            }

        /* The slider */
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            -webkit-transition: .4s;
            transition: .4s;
            }

        .slider:before {
            position: absolute;
            content: "";
            height: 26px;
            width: 26px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            -webkit-transition: .4s;
            transition: .4s;
            }

        input:checked + .slider {
        background-color: #04AA6D;
        }

        input:focus + .slider {
        box-shadow: 0 0 1px #2196F3;
        }

        input:checked + .slider:before {
        -webkit-transform: translateX(26px);
        -ms-transform: translateX(26px);
        transform: translateX(26px);
        }

        /* Rounded sliders */
        .slider.round {
        border-radius: 34px;
        }

        .slider.round:before {
        border-radius: 50%;
        }

    </style>
</head>
<body>
    <!-- Header -->
    <h1>Geitjes portaal</h1>
    <!-- Rounded switch -->
    <div style="text-align: center;">
        <p>Motor aan</p>
        <!-- Rounded switch -->
        <label class="switch">
            <input type="checkbox">
            <span class="slider round"></span>
        </label>
    </div>
</body>
</html>
)";

AsyncWifiServer::AsyncWifiServer(const char *ssid, const char *password)
    : m_SSID(ssid), m_PASSWORD(password)
{
    if (ssid != nullptr && password != nullptr)
    {
        m_Server = new AsyncWebServer(80);
        ConnectToLocalNetwork();
    }
}

void AsyncWifiServer::ConnectToLocalNetwork()
{
    // Connect to Wi-Fi
    Serial.printf("Connect to '%s'\n", m_SSID);

    WiFi.begin(m_SSID, m_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
    }

    // Print ESP Local IP Address
    Serial.print("Connected. Adress: ");
    Serial.println(WiFi.localIP());

    // Route for root / web page
    m_Server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                 { request->send(200, "text/html", htmlPage); });

    m_Server->begin();
}