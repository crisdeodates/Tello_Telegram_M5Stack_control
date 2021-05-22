#include <Tello.h>
#include <M5Stack.h>

// Refer:https://github.com/akshayvernekar/telloArduino

// WiFi network name and password:
const char * networkName = "TELLO-ABCCB9";//Replace with your Tello SSID
const char * networkPswd = "";

//Are we currently connected?
boolean connected = false;

Tello tello;
String cmd = "";

void setup() 
{
  Serial.begin(9600); 
  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);

  M5.Lcd.begin();
  M5.Power.begin();
  M5.Lcd.fillScreen( BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(GREEN);  //M5.Lcd.setTextSize(3);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("\n\nWelcome to TelloDronebot\n\nTG bot: @DroneTellobot\n\nDesigned by Team Deodates\n\nProgrammers: Cris & Jiss\n\n");
}

void loop() 
{
  // put your main code here, to run repeatedly:
    
  if(connected)
  {
    if (Serial.available() > 0) 
    {
      // read incoming serial data:
      cmd = Serial.readString();
      // Type the next ASCII value from what you received:
      Serial.println(cmd);
      M5.Lcd.println(cmd);
      tello_action(cmd);
    }
    
    delay(500);
  }
}

void connectToWiFi(const char * ssid, const char * pwd) 
{
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);

  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event) 
{
  switch (event) 
  {
    case SYSTEM_EVENT_STA_GOT_IP:
      //When connected set
      Serial.print("WiFi connected! IP address: ");
      Serial.println(WiFi.localIP());
      //initialise Tello after we are connected
      tello.init();
      M5.Lcd.println("Wifi connected");
      connected = true;
      break;
      
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      connected = false;
      break;
  }
}

void tello_action(String &result_label)
{
    if(result_label == "takeoff") tello.takeoff();
    else if(result_label == "land") tello.land();
    else if(result_label == "forward") tello.forward(40); //cm
    else if(result_label == "back") tello.back(40); //cm
    else if(result_label == "left") tello.left(40); //cm
    else if(result_label == "right") tello.right(40); //cm 
    else if(result_label == "up") tello.up(40); //cm
    else if(result_label == "down") tello.down(40); //cm 
    else if(result_label == "battery") 
    {
      int bat = tello.getBattery(); //%
      Serial.print(String(bat));
    }
    else if(result_label == "speed") 
    {
      int speed = tello.getSpeed(); //1-100
      Serial.print(String(speed));
    }
    else if(result_label == "time") 
    {
      int time = tello.getTime(); //secs
      Serial.print(String(time));
    }
    else if(result_label == "height") 
    {
      int height = tello.getHeight(); //0-3000 cms
      Serial.print(String(height));
    }
    else if(result_label == "temp") 
    {
      int temp = tello.getTemperature(); //0-90
      Serial.print(String(temp));
    }
    else if(result_label == "baro") 
    {
      int baro = tello.getBaro(); //meters
      Serial.print(String(baro));
    }
}
