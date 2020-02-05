#include "web_client.h"

#ifndef HAVE_HWSERIAL1
	#include "SoftwareSerial.h"

	SoftwareSerial esp8266Serial(8, 9); 
#endif

#define ROUTER_SSID		"HUAWEI-B315-60A6"
#define PASS			"R9Q05BT6GMB"

#if LOCAL == 1
	#define SERVER			"localhost:8080"
	#define PORT			8080
	#define APP_PATH		"/weatherStation/"
#else
	#define SERVER			"heroku server"
	#define PORT			80
	#define APP_PATH		"/"
#endif

int status = WL_IDLE_STATUS;

WiFiEspClient client;

void printWifiStatus();

void setupWiFiConnection()
{
  esp8266Serial.begin(9600);
  WiFi.init(&esp8266Serial);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ROUTER_SSID);
	
    status = WiFi.begin(ROUTER_SSID, PASS);
  }

  Serial.println("You're connected to the network");
  
  printWifiStatus();
}


void sendData(MeasuredData* data) {
  Serial.println();
  Serial.println("Starting connection to server...");
  
  if (client.connect(SERVER, PORT)) {
    Serial.println("Connected to server");
    // Make a HTTP request
    client.print("POST ");
	client.print(APP_PATH);
	client.println("mainWindowServlet HTTP/1.1");
    client.print("Host: ");
	client.print(SERVER);
	client.print(':');
	client.println(PORT);
	client.println("Content-Type: application/x-www-form-urlencoded");
	client.print("measurementTime=");
	client.print(withLeadingZero(data->dt.year, "%04d"));
	client.print("-");
	client.print(withLeadingZero(data->dt.month));
	client.print("-");
	client.print(withLeadingZero(data->dt.day));
	client.print(" ");
	client.print(withLeadingZero(data->dt.hour));
	client.print(":");
	client.print(withLeadingZero(data->dt.minute));
	client.print(":");
	client.print(withLeadingZero(data->dt.second));
	client.print("&temperature=");
	client.print(data->tempC);
	client.print("&airHumidity=");
	client.print(data->humidity);
	client.print("&airPressure=");
	client.println(data->pressure);
    client.println("Connection: close");
    client.println();
  }
}

// void loop()
// {
//   // if there are incoming bytes available
//   // from the server, read them and print them
//   while (client.available()) {
//     char c = client.read();
//     Serial.write(c);
//   }

//   // if the server's disconnected, stop the client
//   if (!client.connected()) {
//     Serial.println();
//     Serial.println("Disconnecting from server...");
//     client.stop();

//     // do nothing forevermore
//     while (true);
//   }
// }

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
