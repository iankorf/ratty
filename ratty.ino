/******************************************************************************\
 ratty.ino by Ian Korf
\******************************************************************************/

#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include "push_button.h"
#include "messages.h"
#include "config.h"

// Time

unsigned long curr_time = 0;
unsigned long prev_time = 0;
unsigned long diff_time = 0;

// Button - this application uses only 1

push_button button = new_push_button(2, millis());

// WiFi

const char ssid[] = MY_SSID;
const char pass[] = MY_PASS;
int status = WL_IDLE_STATUS;
	
void setup_wifi () {
	String fv = WiFi.firmwareVersion(); 
	if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
		Serial.println("Please upgrade the firmware");
	}

	while (status != WL_CONNECTED)	{
		Serial.print("Connecting to network: ");
		Serial.println(MY_SSID);
		status = WiFi.begin(MY_SSID, MY_PASS);
		delay(5000);
	}
	Serial.println("Success"); 
}

// Messaging service

const char serv[] = MY_SERV;
const char hook[] = MY_HOOK;
const int port = MY_PORT;

WiFiSSLClient wifi_client;
HttpClient http_client = HttpClient(wifi_client, serv, port);

void send_button_message(int clicks, bool held) {
	if			(held)				publish_message(MESSAGEY);
	else if (clicks == 1) publish_message(MESSAGE1);
	else if (clicks == 2) publish_message(MESSAGE2);
	else if (clicks >	 3) publish_message(MESSAGEX);
}

void publish_message(String message) {
	String content = "{\"content\": \"" + message + "\", " + "\"username\": \"" + MY_NAME + "\"}";
	Serial.println(content);
	http_client.post(hook, "application/json", content);
	 
	int statusCode = http_client.responseStatusCode();
	String response = http_client.responseBody();

	Serial.print("[HTTP] Status code: ");
	Serial.println(statusCode);
	Serial.print("[HTTP] Response: ");
	Serial.println(response);
}

/******************************************************************************\
 Main Setup and Loop
\******************************************************************************/

void setup() {
	Serial.begin(9600);
	pinMode(button.pin, INPUT);
	setup_wifi();
	publish_message(GREETING);
}

void loop() {	 
	curr_time = millis();
	diff_time = curr_time - prev_time;
	button = update_button(button, curr_time, diff_time);
	if (button.pressed) send_button_message(button.clicks, button.held);
	prev_time = curr_time;
}
