
#include<ESP8266WiFi.h>


#define LED D4
#define LED2 D3
const char* ssid = "wifi name";
const char* password = "password";
unsigned char status_led=0;
unsigned char status_led2=0;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if (req.indexOf("/motorclockwise") != -1)
  {
    status_led=0;   
    digitalWrite(LED,LOW);
     digitalWrite(LED2,HIGH);
    Serial.println("LED1 OFF");
  }
  else if(req.indexOf("/motoranticlockise") != -1)
  {
    status_led=1;
    digitalWrite(LED,HIGH);
    digitalWrite(LED2,LOW);
    Serial.println("LED1 ON");
  }

  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>MOTOR Status</h1>\r\n";
  web += "<p>\r\n";
  if(status_led==1)
      web += "MOTOR ANTICLOCKWISE\r\n";
  else
      web += "MOTOR CLOCKWISE\r\n";
  web += "</p>\r\n";
  web += "</p>\r\n";
  web += "<a href=\"/motorclockwise\">\r\n";
  web += "<button>MOTOR CLOCKWISE</button >\r\n";
  web += "</a>\r\n";
  web += "</p>\r\n";
  
  web += "<a href=\"/motoranticlockise\">\r\n";
  web += "<button>MOTOR ANTICLOCKWISE</button >\r\n";
  web += "</a>\r\n";
    
    

  
  web += "</body>\r\n";
  web += "</html>\r\n";
  
  client.print(web);
}
