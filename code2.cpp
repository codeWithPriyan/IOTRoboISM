 // https://github.com/adafruit/DHT-sensor-library  
 // https://github.com/manrueda/ESP8266HttpClient  
 // https://github.com/ekstrand/ESP8266wifi  
 #include <ESP8266WiFi.h>  
 #include <ESP8266HTTPClient.h>  
 String thingSpeakAddress= "http://api.thingspeak.com/update?";  
 String writeAPIKey;  
 String tsfield1Name;  
 String request_string,request_string1;  
 HTTPClient http;  
 #include <DHT.h> 
 // library  
 // https://github.com/adafruit/DHT-sensor-library  
 #include <ESP8266WiFi.h>  
 String apiKey = "77921LPMGM2OAGQE"; 
 const char *ssid = "DESKTOP";     
 const char *pass = "asdfghjkl";      
 const char* server = "api.thingspeak.com";  
 #define DHTPIN 0     
 DHT dht(DHTPIN, DHT11);  
 WiFiClient client;  
 void setup()  
 {  dht.begin();  
   Serial.begin(115200);  
  delay(3000);  
  WiFi.disconnect();  
  Serial.println("START");  
   WiFi.begin("DESKTOP","asdfghjkl");  
  while ((!(WiFi.status() == WL_CONNECTED))){  
   delay(300);  
   Serial.println("...");  
  }  
  Serial.println("I AM CONNECTED");  
 }  
 void loop()  
 {  
   if (client.connect("api.thingspeak.com",80))  
   {  
    request_string = thingSpeakAddress;  
    request_string += "key=";  
    request_string += "77921LPMGM2OAGQE";  
    request_string += "&";  
    request_string += "field3";  
    request_string += "=";  
    request_string += analogRead(A0);  
    http.begin(request_string);  
    http.GET();  
    http.end();  
   }  
   delay(10);  
 float h = dht.readHumidity();  
    float t = dht.readTemperature();  
        if (isnan(h) || isnan(t))   
          {  
            Serial.println("Failed to read from DHT sensor!");  
            return;  
          }  
              if (client.connect(server,80))  
            {   
                String postStr = apiKey;  
                postStr +="&field1=";  
                postStr += String(t);  
                postStr +="&field2=";  
                postStr += String(h);  
                postStr += "\r\n\r\n";  
                client.print("POST /update HTTP/1.1\n");  
                client.print("Host: api.thingspeak.com\n");  
                client.print("Connection: close\n");  
                client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");  
                client.print("Content-Type: application/x-www-form-urlencoded\n");  
                client.print("Content-Length: ");  
                client.print(postStr.length());  
                client.print("\n\n");  
                client.print(postStr);  
                Serial.print("Temperature: ");  
                Serial.print(t);  
                Serial.print(" degrees Celcius, Humidity: ");  
                Serial.print(h);  
                Serial.print(" Soil Sensor ");  
                Serial.print(A0);  
                Serial.println("%. Send to Thingspeak.");  
             }  
      client.stop();  
      Serial.println("Waiting...");  

  delay(10);  
 }  
