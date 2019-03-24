#include <ESP8266WiFi.h>

// enter wifi credentials
const char* ssid = "Mi 3C";
const char* password = "passispass";

/* Arduino to ESP8266 Pin mappings
 *  D0 - > 16; D1 - > 5; D3 - > 4; D4 - > 2; D5 - > 14; D6 - > 12; D7 - > 13; D8 - > 15
 *  RX - > 3; TX - > 1; SD3 -> 10; SD2 -> 9 */

int ledPin = 13;
//  authKey = amichoriyechi

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
	if (request.indexOf("/LED=ON&AUTHKEY=amichoriyechi") != -1)  {
	  digitalWrite(ledPin, HIGH);
	  value = HIGH;
	}
	if (request.indexOf("/LED=OFF&AUTHKEY=amichoriyechi") != -1)  {
	  digitalWrite(ledPin, LOW);
	  value = LOW;
	}
 
	Serial.print (" DEBUG:" );
	Serial.println(request);
	// Set ledPin according to the request
	//digitalWrite(ledPin, value);
 
//// 	// Return the response
 	client.println("HTTP/1.1 200 OK");
//// 	client.println("Content-Type: text/html");
//// 	client.println(""); //  do not forget this one
//// 	client.println("<!DOCTYPE HTML>");
//// 	client.println("<html>");
//// 	client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
////  
//// 	client.print("Led pin is now: ");
////  
//// 	if(value == HIGH) {
//// 	  client.print("On");
//// 	} else {
//// 	  client.print("Off");
//// 	}
//// 	client.println("<br><br>");
//// 	client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
//// 	client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
//// 	client.println("</html>");
 
	delay(1);
	Serial.println("Client disonnected");
	Serial.println("");
}
