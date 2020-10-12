//MQTT
#include <MQTT.h>
#include <WiFiNINA.h>
#include <SPI.h>
#define BROKER_IP    "mqtt.eclipse.org"
#define DEV_NAME     "mqttdevice"
#define MQTT_USER    ""
#define MQTT_PW      ""
WiFiClient net;
MQTTClient client;

//OLED
#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,SCL,SDA,U8X8_PIN_NONE);

//Ring
#include <Adafruit_NeoPixel.h>
#define LED_PIN 3
#define LED_COUNT 20
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//variables
extern int countprt = 0;
const char ssid[] = "";
const char pass[] = "";

//connected method
void connect() {
 Serial.print("checking wifi...");
 while (WiFi.status() != WL_CONNECTED) {
 Serial.print(".");
 delay(1000);
 }
 Serial.print("\nconnecting...");
 while (!client.connect(DEV_NAME, MQTT_USER, MQTT_PW)) {
 Serial.print(".");
 delay(1000);
 }
 Serial.println("\nconnected!");
 client.subscribe("/count");
 client.subscribe("/count1");
 client.subscribe("/countmeno1");
 
}

void messageReceived(String &topic, String &payload) {
  if (topic == "/count1"){
   do {u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_inb16_mr);
      u8g2.setCursor(0, 20);
      u8g2.println("Num: " + payload);
      countprt ++;
      }while (u8g2.nextPage());
      }else if (topic == "/countmeno1"){
      countprt = countprt - 1;
      }
}

void setup() { 
    //setup OLED
    u8g2.begin();
    //setup MQTT
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    client.begin(BROKER_IP, 1883, net);
    client.onMessage(messageReceived);
    connect();

    //setup ring
    strip.begin();
    strip.setBrightness(255);
    strip.show();
}


void colorWipe(uint32_t color) {
    for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
  }
}

void loop() {
    client.loop();
    if (!client.connected()){
    connect();
    }
    delay(1000);
    //the ring will work as a traffic light, becoming red when 4 users are all inside a room at the same time
       if (countprt <4){                              //maximum capacity set at 4
          colorWipe(strip.Color(0,   255,   0));
          }else{
          colorWipe(strip.Color(  255, 0,   0));
    }
    
}   
