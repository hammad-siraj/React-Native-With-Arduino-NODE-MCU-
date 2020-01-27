

#include <ESP8266WiFi.h>


 
const char* ssid = "PMSNATWORK75"; // SSID i.e. Service Set Identifier is the name of your WIFI
const char* password = "pakistan321"; // Your Wifi password, in case you have open network comment the whole statement.
float times=0,distance=0;
int value = LOW;
static const uint8_t relayPin = 13; // GPIO13 or for NodeMCU you can directly write D7 
static const uint8_t trigger=5;//D1
static const uint8_t echo=4;//D2
static const uint8_t ledPinGreen = 0; //d3
//static const uint8_t ledPinRed = 2;//d4
WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in this case port is 80.


 void measure_distance()
{
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 times=pulseIn(echo,HIGH);
 
 distance=times*200/20000;
  
}
 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(trigger, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo, INPUT); // Sets the echoPin as an 
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  pinMode(ledPinGreen,OUTPUT);
  digitalWrite(ledPinGreen,LOW);
//  pinMode(ledPinRed,OUTPUT);
//  digitalWrite(ledPinRed,HIGH); 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //Gets the WiFi shield's IP address and Print the IP address of serial monitor
  Serial.println("/");
 
}
 
void loop() {

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }




  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
   measure_distance();
  // Match the request

  Serial.print("distance");
  Serial.println(distance,3);

if(distance < 10 && request.indexOf("/LED=ON") != -1){
 
    digitalWrite(relayPin, LOW);

    value = HIGH;
       digitalWrite(ledPinGreen,HIGH);
  //     digitalWrite(ledPinRed,LOW);
}
  
 if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(relayPin, HIGH);
    value = LOW;
        digitalWrite(ledPinGreen,LOW);
    //    digitalWrite(ledPinRed,HIGH);
  
  }




 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
