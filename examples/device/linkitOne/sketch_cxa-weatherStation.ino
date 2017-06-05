#include <Barometer.h>
#include <DHT.h>
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <PubSubClient.h>
//#include <SensorThings.h>

#define DHTPIN 2        //  pin D2
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

Barometer myBarometer;

// *** Wifi Client
#define WIFI_AP       "AP_SSID"      	// to replace with your AP SSID 
#define WIFI_PASSWORD "PassWord"        // to replace with your AP Security Key
#define WIFI_AUTH LWIFI_WPA   // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
LWiFiClient client;

// *** STA Platform
/*
#define REST_SERVER "scratchpad.sensorup.com"   //port: 80
#define REST_SERVER "sg2017-sta.sensorup.com"   //port: 80
*/

#define REST_SERVER "cxa2017-ws1.sensorup.com"   //port: 80
#define AUTH_ENCODED "Authorization: Basic bWFpbjpmMDk2MTFlYy02MGY2LTUyM2ItOGU3NC05NjYwMTkxMjU3N2I=" //cxa2017-ws1 encoded to Base64

//#define REST_SERVER "cxa2017-ws2.sensorup.com"    //port: 80
//#define AUTH_ENCODED "Authorization: Basic bWFpbjo3YjM3YWVlNy01ZTc2LTVkODMtYThlYy01MTNmMzZiNTU1ZGU=" //cxa2017-ws2 encoded to Base64

/*
#define MQTT_BROKER "scratchpad.sensorup.com"   //port: 1883
#define MQTT_BROKER "sg2017-sta.sensorup.com"   //port: 1883
*/

#define MQTT_BROKER "cxa2017-ws1.sensorup.com"  //port: 1883
#define AUTH_USER   "main"  //cxa2017-ws1
#define AUTH_PASSWD "f09611ec-60f6-523b-8e74-96601912577b"  //cxa2017-ws1

//#define MQTT_BROKER "cxa2017-ws2.sensorup.com"   //port: 1883
//#define AUTH_USER   "main"  //cxa2017-ws2
//#define AUTH_PASSWD "7b37aee7-5e76-5d83-a8ec-513f36b555de"  //cxa2017-ws2

/*
#define TEMPERATURE_DATASTREAM_ID 47557   //sg2017-sta datastream
#define HUMIDITY_DATASTREAM_ID    47562   //sg2017-sta datastream
#define PRESSURE_DATASTREAM_ID    47565   //sg2017-sta datastream
#define ILLUMINANCE_DATASTREAM_ID 47564   //sg2017-sta datastream
*/
#define TEMPERATURE_DATASTREAM_ID 34   //cxa2017-ws1 & cxa2017-ws2 WS-Sembawang(38); WS-Cashew(42); WS-NYP/SEG(34)
#define HUMIDITY_DATASTREAM_ID    35   //cxa2017-ws1 & cxa2017-ws2 WS-Sembawang(39); WS-Cashew(43); WS-NYP/SEG(35)
#define PRESSURE_DATASTREAM_ID    36   //cxa2017-ws1 & cxa2017-ws2 WS-Sembawang(40); WS-Cashew(44); WS-NYP/SEG(36)
#define ILLUMINANCE_DATASTREAM_ID 37   //cxa2017-ws1 & cxa2017-ws2 WS-Sembawang(41); WS-Cashew(45); WS-NYP/SEG(37)

//#define ILLUMINANCE_DATASTREAM_ID 46    //cxa2017-ws1 & cxa2017-ws2 WS-NYP-datastream(46)


float   t1        = 0.0;
float   t2        = 0.0;
float   h         = 0.0;
float   pressure  = 0.0;
float   atm       = 0.0;
char    mqClientID[10];
boolean isMQTT    = false; // true / false

void setup()
{
    Serial.begin(9600);
    InitLWiFi();
    myBarometer.init();
    dht.begin();
    randomSeed(analogRead(0));
    sprintf(mqClientID,"cxa_%d",random(10000));
}

void InitLWiFi()
{
    LWiFi.begin();
    // Keep retrying until connected to AP
    Serial.println("Connecting to AP...");
    while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD))) {
      delay(1000);
    }
    Serial.print("Connected to ");
    Serial.println(WIFI_AP);
}


void msgCallback(char* topic, byte* payload, unsigned int len)
{
    // handle message arrived
}

PubSubClient mqttClient((char*)MQTT_BROKER, 1883, msgCallback, client);

void loop()
{
    if (isMQTT) {
      mqttLoop();
      Serial.print("Using MQTT......Client ID: ");
      Serial.println(mqClientID);
    }
    else Serial.println("Using REST...");
    
    do {
      dht.readHT(&t1, &h);
      delay(100);
    } while (isnan(t1) || isnan(h) || t1 <= -40 || t1 > 80 || h <= 5 || h > 99.9);
  
    do {
      t2 = myBarometer.bmp085GetTemperature(myBarometer.bmp085ReadUT()); //Get the temperature, bmp085ReadUT MUST be called first
      pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP());//Get the temperature
      atm = (pressure / 101325) * 1000;
    }while (isnan(t2) || isnan(atm) || t2 <= -40 || t2 > 80 || atm <= 200.00 || h > 12000.00);
  
    //Temperature reading not in use
    Serial.print("Temperature 1: ");
    Serial.print(t1, 2);   //not used in this example
    Serial.println("deg C");
        
    Serial.print("Temperature 2: ");
    Serial.print(t2, 2); //display 2 decimal places
    Serial.println("deg C");
    if (isMQTT) 
      mqttPublishResult(t2, TEMPERATURE_DATASTREAM_ID);
    else
      httpPostResult(t2, TEMPERATURE_DATASTREAM_ID);  
    
    Serial.print("humidity = ");
    Serial.print(h,1);
    Serial.println("%");
    if (isMQTT)
      mqttPublishResult(h, HUMIDITY_DATASTREAM_ID);
    else
      httpPostResult(h, HUMIDITY_DATASTREAM_ID);
      
    Serial.print("Atmosphere Pressure: ");
    Serial.print(atm, 2); //display 4 decimal places
    Serial.println("mBar");
    if (isMQTT)
      mqttPublishResult(atm, PRESSURE_DATASTREAM_ID);
    else
      httpPostResult(atm, PRESSURE_DATASTREAM_ID);
  
    Serial.print("Light: ");
    Serial.print(analogRead(A0));
    Serial.println("lux");
    if (isMQTT)
      mqttPublishResult(analogRead(A0), ILLUMINANCE_DATASTREAM_ID);
    else
      httpPostResult(analogRead(A0), ILLUMINANCE_DATASTREAM_ID);
  
    Serial.println("Waiting for next acquisition...");
    delay(10000); 
}

void mqttPublishResult(float value,int datastreamId)
{
    char sensorData[100];
    char topic[50];
    
    createObservationJson(value).toCharArray( sensorData, 100 );
    sprintf(topic, "v1.0/Datastreams(%d)/Observations", datastreamId); 
    Serial.print("Publish Topic:");
    Serial.println(topic);
    mqttClient.publish(topic, sensorData );
    Serial.println( sensorData );
}

String createObservationJson(float value)
{
    String jsonString = "{";
    jsonString += "\"result\":";
    jsonString +=  value;
    jsonString += "}";
    return jsonString;
}

void mqttLoop()
{
    if( !mqttClient.connected() ) {
      mqttReconnect();
    }
    Serial.println( "CONNECTED MQTT" );
    mqttClient.loop();
}

void mqttReconnect() 
{
    boolean isConnected;

    if (!mqttClient.connected()) {
      Serial.println("\nConnecting to MQTT broker ...");

      // Attempt to connect
      //isConnected = mqttClient.connect("SEG1234567890", AUTH_USER, AUTH_PASSWD);
      isConnected = mqttClient.connect(mqClientID, AUTH_USER, AUTH_PASSWD);
      if (isConnected) {  
        Serial.println( "[DONE]" );
      } else {
        Serial.print( "[FAILED] [ rc = " );
        Serial.print( mqttClient.state() );
        Serial.println( " : retrying in 5 seconds]" );
        delay( 5000 );
      }
    }
}

void httpPostResult(float value, int datastreamId)
{
    Serial.println("HTTP POST an Observation result ...");
    String observationJson = createObservationJson(value);
    Serial.println(observationJson);
    if (client.connect(REST_SERVER, 80))
    {
      Serial.print( "to ");
      Serial.println(REST_SERVER);
      
      // Build HTTP POST request
/*      
      client.println("POST /OGCSensorThings/v1.0/Datastreams(" + String(datastreamId) + ")/Observations HTTP/1.1");
      Serial.println("POST /OGCSensorThings/v1.0/Datastreams(" + String(datastreamId) + ")/Observations HTTP/1.1");
*/
      client.println("POST /v1.0/Datastreams(" + String(datastreamId) + ")/Observations HTTP/1.1"); 
      Serial.println("POST /v1.0/Datastreams(" + String(datastreamId) + ")/Observations HTTP/1.1");

      String host = "Host: ";
      host.concat(REST_SERVER);
      client.println(host);
      Serial.println(host);
      client.println("Connection: close");
      Serial.println("Connection: close");
      client.println("Content-Type: application/json");
      Serial.println("Content-Type: application/json");
      
      client.println(AUTH_ENCODED);     //encoded to Base64 format
      Serial.println(AUTH_ENCODED); 
      
      client.println("Cache-Control: no-cache");
      Serial.println("Cache-Control: no-cache");
      client.print("Content-Length: ");
      Serial.print("Content-Length: ");
      client.print(observationJson.length());
      Serial.print(observationJson.length());
      client.print("\n\n");
      Serial.print("\n\n");
      client.print(observationJson);
      Serial.println("Observation: " + observationJson);
      while (true)
      {
        // if there are incoming bytes available
        // from the server, read them and print them:
        if (client.available()) {
          char c = client.read();
          //  Serial.print(c);
        }
        // if the server's disconnected, stop the client:
        if (!client.connected()) {
          Serial.println();
          Serial.println("server disconnected. stopping the client.\n");
          client.stop();
          break;
        }
      }
    }
    else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }
}


