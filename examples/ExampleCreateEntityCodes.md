# Quick Starter on SensorThings API
## Training Workshop for code::XtremeApps::2017 Participants


### Example Code for Weather Stations Use Case

This set of example code in JavaScript/JQuery demonstrates the use of SensorThings API to create and access the data model for the weather stations use case.


### (1) Create a Thing

``` javascript
var dataObj = {
     name: "SGWeatherStation1",
     description: "SG Weather Station located at Central"
};

$.ajax({
     url: "https://cxa2017-ws2.sensorup.com/v1.0/Things",
     type: "POST",
     data: JSON.stringify(dataObj),
     contentType: "application/json",
     headers: {
          "Authorization": "Basic " + btoa("myusername:mypassword")
     },
     success: function(response) {
          console.log(JSON.stringify(response));  
     },
     error: function(response) {
          console.log(response.status);
     }
});

```
#### *HTTP response from STA*
``` json
{
     "@iot.id": 817562,
     "@iot.selfLink": "https://cxa2017-ws2.sensorup.com/v1.0/Things(817562)",
     "description": "SG Weather Station located at Central",
     "name": "SGWeatherStation1",
     "properties": {},
     "Datastreams@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Things(817562)/Datastreams",
     "HistoricalLocations@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Things(817562)/HistoricalLocations",
     "Locations@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Things(817562)/Locations"
}
```

### (2) Create a Location

``` javascript
var dataObj = {
     name: "SGWeatherStation1-Loc",
     description: "NYP, Block S",
     encodingType: "application/vnd.geo+json",
     location: {
          "type": "Point",
          "coordinates": [103.84814858436584,
                             1.3793617047382691]
     }
};

$.ajax({
     url: "https://cxa2017-ws2.sensorup.com/v1.0/Things(817562)/Locations",
     type: "POST",
     data: JSON.stringify(dataObj),
     contentType: "application/json",
     headers: {
          "Authorization": "Basic " + btoa("myusername:mypassword")
     },
     success: function(response) {
          console.log(JSON.stringify(response));  
     },
     error: function(response) {
          console.log(response.status);
     }
});
```
#### *HTTP response from STA*
``` json
{
     "@iot.id": 817570,
     "@iot.selfLink": "https://cxa2017-ws2.sensorup.com/v1.0/Locations(817570)",
     "description": "NYP, Block S",
     "name": "SGWeatherStation1-Loc",
     "encodingType": "application/vnd.geo+json",
     "location": {
          "coordinates": [
                103.84814858436584,
                1.3793617047382691
          ],
          "type": "Point"
    },
    "Things@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Locations(817570)/Things",
    "HistoricalLocations@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Locations(817570)/HistoricalLocations"
}
```

### (3) Create an Observed Property

``` javascript
var dataObj = {
    name: "air_temperature",
    description: "Temperature of air in situ.",
    definition: "http://mmisw.org/ont/ioos/parameter/air_temperature"
};

$.ajax({
    url: "https://cxa2017-ws2.sensorup.com/v1.0/ObservedProperties",
    type: "POST",
    data: JSON.stringify(dataObj),
    contentType: "application/json",
    headers: {
          "Authorization": "Basic " + btoa("myusername:mypassword")
     },
     success: function(response) {
          console.log(JSON.stringify(response));  
     },
     error: function(response) {
          console.log(response.status);
     }
});
```
#### *HTTP response from STA*
``` json
{
    "@iot.id": 855226,
    "@iot.selfLink": "https://cxa2017-ws2.sensorup.com/v1.0/ObservedProperties(855226)",
    "description": "Temperature of air in situ.",
    "definition": "http://mmisw.org/ont/ioos/parameter/air_temperature",
    "name": "air_temperature",
    "Datastreams@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/ObservedProperties(855226)/Datastreams"
}
```

### (4) Create a Sensor

``` javascript
var dataObj = {
    name: "DHT22",
    description: "The DHT22 temperature sensor located at SGWeatherStation1",
    encodingType: "application/pdf",
    metadata: "https://cdn-shop.adafruit.com/datasheets/DHT22.pdf"
};

$.ajax({
    url: "https://cxa2017-ws2.sensorup.com/v1.0/Sensors",
    type: "POST",
    data: JSON.stringify(dataObj),
    contentType: "application/json",
    headers: {
          "Authorization": "Basic " + btoa("myusername:mypassword")
     },
     success: function(response) {
          console.log(JSON.stringify(response));  
     },
     error: function(response) {
          console.log(response.status);
     }
});
```
#### *HTTP response from STA*
```  json
{
    "@iot.id": 855243,
    "@iot.selfLink": "https://cxa2017-ws2.sensorup.com/v1.0/Sensors(855243)",
    "description": "The DHT22 temperature sensor located at SGWeatherStation1",
    "name": "DHT22",
    "encodingType": "application/pdf",
    "metadata": "https://cdn-shop.adafruit.com/datasheets/DHT22.pdf",
    "Datastreams@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Sensors(855243)/Datastreams"
}
```

### (5) Create a Datastream

``` javascript
var dataObj = {
    name: "Air_temperature_readings",
    description: "Air temperature readings from SGWeatherStation1",
    observationType: "http://www.opengis.net/def/observationType/OGC-OM/2.0/OM_Measurement",
    unitOfMeasurement: {
        "name": "Degree Celsius",
        "symbol": "degC",
        "definition": "http://www.qudt.org/qudt/owl/1.0.0/unit/Instances.html#DegreeCelsius"
    },
    Thing:{"@iot.id":817562},
    ObservedProperty:{"@iot.id":855226},
    Sensor:{"@iot.id":855243}
};

$.ajax({
    url: "https://cxa2017-ws2.sensorup.com/v1.0/Datastreams",
    type: "POST",
    data: JSON.stringify(dataObj),
    contentType: "application/json",
    headers: {
          "Authorization": "Basic " + btoa("myusername:mypassword")
     },
     success: function(response) {
          console.log(JSON.stringify(response));  
     },
     error: function(response) {
          console.log(response.status);
     }
});
```
#### *HTTP response from STA*
``` json
{
    "@iot.id": 855256,
    "@iot.selfLink": "https://cxa2017-ws2.sensorup.com/v1.0/Datastreams(855256)",
    "description": "Air temperature readings from SGWeatherStation1",
    "name": "Air_temperature_readings",
    "observationType": "http://www.opengis.net/def/observationType/OGC-OM/2.0/OM_Measurement",
    "unitOfMeasurement": {
        "symbol": "degC",
        "name": "Degree Celsius",
        "definition": "http://www.qudt.org/qudt/owl/1.0.0/unit/Instances.html#DegreeCelsius"
    },
    "Observations@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Datastreams(855256)/Observations",
    "ObservedProperty@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Datastreams(855256)/ObservedProperty",
    "Sensor@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Datastreams(855256)/Sensor",
    "Thing@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Datastreams(855256)/Thing"
}
```

### (6) Create a Feature of Interest
``` javascript
var dataObj = {
    name: "NYP_Block_S_Roof",
    description: "Roof of Block S, NYP",
    encodingType: "application/vnd.geo+json",
    feature: {
      "type": "Point",
      "coordinates": [103.84814858436584, 1.3793617047382691]
    }
};

$.ajax({
    url: "https://cxa2017-ws2.sensorup.com/v1.0/FeaturesOfInterest",
    type: "POST",
    data: JSON.stringify(dataObj),
    contentType: "application/json",
    headers: {
          "Authorization": "Basic " + btoa("myusername:mypassword")
     },
     success: function(response) {
          console.log(JSON.stringify(response));  
     },
     error: function(response) {
          console.log(response.status);
     }
});
```
#### *HTTP response from STA*
``` json
{
    "@iot.id": 855260,
    "@iot.selfLink": "https://cxa2017-ws2.sensorup.com/v1.0/FeaturesOfInterest(855260)",
    "description": "Roof of Block S, NYP",
    "name": "NYP_Block_S_Roof",
    "encodingType": "application/vnd.geo+json",
    "feature": {
         "coordinates": [
              103.84814858436584,
              1.3793617047382691
         ],
         "type": "Point"
     },
    "Observations@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/FeaturesOfInterest(855260)/Observations"
}
```

### (7) Create an Observation
``` javascript
var dataObj = {
    phenomenonTime: "2017-05-02T19:11:38.008Z",
    resultTime: "2017-05-02T19:11:38.008Z",
    result: 28.6,
    FeatureOfInterest: {"@iot.id": 855260}
};

$.ajax({
    url: "https://cxa2017-ws2.sensorup.com/v1.0/Datastreams(855256)/Observations",
    type: "POST",
    data: JSON.stringify(dataObj),
    contentType: "application/json",
    headers: {
          "Authorization": "Basic " + btoa("myusername:mypassword")
     },
     success: function(response) {
          console.log(JSON.stringify(response));  
     },
     error: function(response) {
          console.log(response.status);
     }
});
```
#### *HTTP response from STA*
``` json
{
    "@iot.id": 855900,
    "@iot.selfLink": "https://cxa2017-ws2.sensorup.com/v1.0/Observations(855900)",
    "phenomenonTime": "2017-05-02T19:11:38.008Z",
    "result": "28.6",
    "resultTime": "2017-05-02T19:11:38.008Z",
    "Datastream@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Observations(855900)/Datastream",
    "FeatureOfInterest@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/Observations(855900)/FeatureOfInterest"
}
```

### (8) Update a Feature of Interest
``` javascript
var dataObj = {
    feature: {
        "type": "Polygon",
        "coordinates": [
          [
            [
              103.8479071855545,
              1.3794823691652804
            ],
            [
              103.8479071855545,
              1.3794823691652804
            ],
            [
              103.8479071855545,
              1.3794823691652804
            ],
            [
              103.8479071855545,
              1.3794823691652804
            ]
          ]
        ]
    }
};

$.ajax({
    url: "https://cxa2017-ws2.sensorup.com/v1.0/FeaturesOfInterest(855260)",
    type: "PATCH",
    data: JSON.stringify(dataObj),
    contentType: "application/json",
    headers: {
          "Authorization": "Basic " + btoa("myusername:mypassword")
     },
     success: function(response) {
          console.log(JSON.stringify(response));  
     },
     error: function(response) {
          console.log(response.status);
     }
});
```
#### *HTTP response from STA*
``` json
{  
   "@iot.id": 855260,
   "@iot.selfLink": "https://cxa2017-ws2.sensorup.com/v1.0/FeaturesOfInterest(855260)",
   "description": "Roof of Block S, NYP",  
   "name": "NYP_Block_S_Roof",
   "encodingType": "application/vnd.geo+json",
   "feature": {
       "coordinates": [      
           [        
               [103.8479071855545, 1.3794823691652804],        
               [103.8479071855545, 1.3794823691652804],        
               [103.8479071855545, 1.3794823691652804],        
               [103.8479071855545, 1.3794823691652804]      
           ]    
        ],    
       "type": "Polygon"  
   },  
   "Observations@iot.navigationLink": "https://cxa2017-ws2.sensorup.com/v1.0/FeaturesOfInterest(855260)/Observations"
}
```

### (9) Read Observations
``` javascript
$.get("http://scratchpad.sensorup.com/OGCSensorThings/v1.0/Datastreams(855256)/Observations", function(response, status) {
    console.log(response);
});
```
#### *HTTP response from STA*
``` json
{
  "@iot.count": 1,
  "value": [
    {
      "@iot.id": 855900,
      "@iot.selfLink": "http://scratchpad.sensorup.com/OGCSensorThings/v1.0/Observations(855900)",
      "phenomenonTime": "2017-05-02T19:11:38.008Z",
      "result": "28.6",
      "resultTime": "2017-05-02T19:11:38.008Z",
      "Datastream@iot.navigationLink": "http://scratchpad.sensorup.com/OGCSensorThings/v1.0/Observations(855900)/Datastream",
      "FeatureOfInterest@iot.navigationLink": "http://scratchpad.sensorup.com/OGCSensorThings/v1.0/Observations(855900)/FeatureOfInterest"
    }
  ]
}
```

### (10) Delete an Observation
``` javascript
$.ajax({
    url: "https://cxa2017-ws2.sensorup.com/v1.0/Observations(855900)",
    type: "DELETE",
    contentType: "application/json",
    headers: {
          "Authorization": "Basic " + btoa("myusername:mypassword")
     },
     success: function(response) {
          console.log(response);  
     },
     error: function(response) {
          console.log(response.status);
     }
});
```



