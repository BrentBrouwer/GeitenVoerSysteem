#include <WiFi.h>
#include <ESPAsyncWebServer.h>

class AsyncEspWebServer
{
    public:
        AsyncEspWebServer(int portNr, const char* ssid, const char* password, const char* domainName = NULL);
    
    private:
        void GetMacAdress();
        void ConnectToLocalNetwork();

    private:
        AsyncEspWebServer m_Server;
        const uint16_t m_PortNr;
        const char* m_SSID;
        const char* m_Password;
        const char* m_DomainName;

        const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Integer Input</title>
  <script>
    function sendValue() {
      var val = document.getElementById("myNumber").value;
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "/setValue?number=" + val, true);
      xhttp.send();
    }
  </script>
</head>
<body>
  <h2>Enter an Integer:</h2>
  <input type="number" id="myNumber" name="myNumber" step="1" oninput="validity.valid||(value='');">
  <br><br>
  <button onclick="sendValue()">Submit</button>
</body>
</html>
)rawliteral";
};
