#include <ESP8266WiFi.h>

// enter wifi credentials
const char* ssid = "wifiname";
const char* password = "letthisbe password";

/* arduino to ESP8266 pin mappings
 D0 - > 16
 D1 - > 5
 D3 - > 4
 D4 - > 2
 D5 - > 14
 D6 - > 12
 D7 - > 13
 D8 - > 15
 RX - > 3
 TX - > 1
 SD3 -> 10
 SD2 -> 9
*/

int ledPin = 13;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connection status
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n Connecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print(".");  }
  Serial.println("\nINFO : WiFi connected");
  digitalWrite(16, LOW);
  
  // Start the server
  server.begin();
  Serial.printf("INFO : Server started\n");
  Serial.print("Use this URL to connect: http://");
  Serial.println(WiFi.localIP());
}

void loop () {

  // Check if a client has connected
  WiFiClient client = server.available();
  if ( !client ) { return; }
  Serial.println(client);
  // Wait until the client sends some data
  Serial.println("Connected to a new client");
  while( !client.available() ) { delay(1); }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  int value = LOW;
  if (request.indexOf("/LED=ON&AUTHKEY=INSERTAUTHKEY") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF&AUTHKEY=INSERTAUTHKEY") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
  Serial.print (" DEBUG:" );
  Serial.println(request);
 
   client.println("HTTP/1.1 200 OK");
  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
