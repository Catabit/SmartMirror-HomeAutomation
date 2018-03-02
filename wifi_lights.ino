#include <ESP8266WiFi.h>
const char* ssid = "Catabit";
const char* password = "catabitTQTQ";
 
int light1 = 4; // GPIO2 of ESP8266
int light2 = 5; // GPIO4 of ESP8266

int light1_state = HIGH;
int light2_state = HIGH;

WiFiServer server(80);//Service Port

void flash_OK(int returnState) {
  digitalWrite(light1, !returnState);
  digitalWrite(light2, !returnState);
  yield();
  delay(150);
  yield();
  digitalWrite(light1, returnState);
  digitalWrite(light2, returnState);
}
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  digitalWrite(light1, HIGH);
  digitalWrite(light2, HIGH);
   
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
  flash_OK(HIGH);
   
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
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
    yield();
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  //Serial.println(request);
  client.flush();
   
  // Match the request
  
 
  if (request.indexOf("/Light1=ON") != -1) {
    light1_state = LOW;
  } else if (request.indexOf("/Light1=OFF") != -1) {
    light1_state = HIGH;
  } else if (request.indexOf("/Light2=ON") != -1){
    light2_state = LOW;
  } else if (request.indexOf("/Light2=OFF") != -1) {
    light2_state = HIGH;
  } else if (request.indexOf("/AllLights=ON") != -1) {
    light1_state = LOW;
    light2_state = LOW;
  } else if (request.indexOf("/AllLights=OFF") != -1) {
    light1_state = HIGH;
    light2_state = HIGH;
  }

  digitalWrite(light1, light1_state);
  delay(10);
  digitalWrite(light2, light2_state);
  delay(10);
  //Set light1 according to the request
  //digitalWrite(light1, value);
  yield();
  
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
   
  if (light1_state && light2_state) {
    client.print("<h3>Both lights are <b>off</b></h3>");
  } else if(!light1_state && !light2_state) {
    client.print("<h3>Both lights are <b>on</b></h3>");
  } else if (!light2_state) {
    client.print("<h3>Light2 is <b>on</b></h3>");
  } else if (!light1_state) {
    client.print("<h3>Light1 is <b>on</b></h3>");
  } 
   
  client.println("<br><br>");
  client.println("<h2><a style=\"margin-right:10px\" href=\"Light1=ON\">Light1 ON</a><a style=\"margin-left:10px\" href=\"Light1=OFF\">Light1 OFF</a></h2>");
  client.println("<br>");
  client.println("<h2><a style=\"margin-right:10px\" href=\"Light2=ON\">Light2 ON</a><a style=\"margin-left:10px\" href=\"Light2=OFF\">Light2 OFF</a></h2>");
  client.println("<br><br>");
  client.println("<h2><a style=\"margin-right:10px\" href=\"AllLights=ON\">All ON</a><a style=\"margin-left:10px\" href=\"AllLights=OFF\">ALL OFF</a></h2>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
