const char indexHTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
 <head>
  <title>Weather Station</title>
  <meta http-equiv="content-type" content="text/html; charset=UTF-8">
  <meta name=viewport content="width=device-width, initial-scale=1">

<script>

  var url = "/";     
window.onload = start;                 // initialize AJAX on page load
 
function start() 
{
  myAjax = new XMLHttpRequest();       // new AJAX object
  myAjax.onload=readAjax;              // on server response call readAjax
  setInterval(update_state, 2000);     // set timer for update_state()
  update_state();                     
}
 
function update_state() 
{
  myAjax.open("GET", "/data", true);  // ansynchronous GET-Request
  myAjax.send();  
}
 
function readAjax()                               // AJAX-event handler
{
  if (myAjax.status==200)                         // HTTP-status OK
  {

    console.log("Ajax.status == 200 Ok");

 /*
    Expected JSON-Object of data:
    {
      "temperatureC": number,
      "temperatureF": number,
      "humidity":     number,
      "dewPoint":     number,
      "wetBulb":      number,
      "light":        number 
    }
    */

    let data = JSON.parse(myAjax.responseText);                 // LED state from response body; parse JSON to JS-Object

    displayData(data);
  }
}
 
function httpGet(parameter)            // GET request 
{
  myAjax.open ("GET", url + parameter, true);
  myAjax.send();
}

function displayData(data) {
  // display the data on screen

  console.log("Data received");
  console.log(data);

  // get data from json
  temperatureC = data.temperatureC;
  temperatureF = data.temperatureF;
  humidity = data.humidity;

  dewPoint = data.dewPoint;
  wetBulb = data.wetBulb;

  light = data.light;


  // display the data
  // as text
  let textTemperatureC = document.getElementById("text-temperaturec");
  textTemperatureC.innerText = temperatureC + " °C";

  let textTemperatureF = document.getElementById("text-temperaturef");
  textTemperatureF.innerText = temperatureF + " °F";

  let textHumidity = document.getElementById("text-humidity");
  textHumidity.innerText = humidity + " %";

  let textDewPoint = document.getElementById("text-dewpoint");
  textDewPoint.innerText = dewPoint + " °C";

  let textWetBulb = document.getElementById("text-wetbulb");
  textWetBulb.innerText = wetBulb + " °C";

  let textLight = document.getElementById("text-light");
  textLight.innerText = light;

  // graphically
  let temperaturePercentage = ((temperatureC - (-5)) / (40 - (-5))) * 100;
  temperaturePercentage = Math.min(100, Math.max(0, temperaturePercentage));

  let progressTemperatureC = document.getElementById("progress-temperaturec");
  progressTemperatureC.style["width"] = temperaturePercentage + "%";

  let progressTemperatureF = document.getElementById("progress-temperaturef");
  progressTemperatureF.style["width"] = temperaturePercentage + "%";


  let progressHumidity = document.getElementById("progress-humidity");
  progressHumidity.style["width"] = humidity + "%";


  let dewPointPercentage = ((dewPoint - (-5)) / (40 - (-5))) * 100;
  dewPointPercentage = Math.min(100, Math.max(0, dewPointPercentage));

  let progressDewPoint = document.getElementById("progress-dewpoint");
  progressDewPoint.style["width"] = dewPointPercentage + "%";


  let wetBulbPercentage = ((wetBulb - (-5)) / (40 - (-5))) * 100;
  wetBulbPercentage = Math.min(100, Math.max(0, wetBulbPercentage));

  let progressWetBulb = document.getElementById("progress-wetbulb");
  progressWetBulb.style["width"] = wetBulbPercentage + "%";


  let lightPercentage = (light / 1024) * 100;

  let progressLight = document.getElementById("progress-light");
  progressLight.style["width"] = lightPercentage + "%";

}

</script>

<style type="text/css" media="screen, print, projection">

body {
  font-family: Arial, sans-serif;
  background-color: #ABB5FC;
}

h1 {
  font-size: 5rem;
  text-align: center;
}


.card {
  background-color: #FFF;
  border: solid 1px #0F0F0F;
  border-radius: 15px;
  min-height: 6rem;
  padding: 1rem;
  margin: 1rem;
  box-shadow: 0px 0px 10px 5px #424242;
}


.progressbar-border {
  border-radius: 50px;
  border: solid 1px #0F0F0F;
  height: 1rem;
  background-color: #EBEBEB;
  width: 100%;
}

.progressbar-inner {
  border-radius: 50px;
  background-color: #685EFF;
  height: 100%;
}


/*
Grid-system with 12 columns
*/

.container {
  width: 95%;
  margin-left: auto;
  margin-right: auto;
}

.row::after {
  content: "";
  display: block;
  clear: both;
}

[class*="col-"] {
  float: left;
  min-height: 1px;
  padding: .8rem;
}

.col-1   { width: 8.333%;   }
.col-3   { width: 25%;      }
.col-4   { width: 33.333%;  }
.col-6   { width: 50%;      }
.col-12  { width: 100%      }

@media (max-width: 1175px) {
  .col-4 { width: 100%; }
}

@media (max-width: 768px) {
  .col-3 { width: 50%;  }
  .col-4 { width: 100%; }
}

@media (max-width: 480px) {
  .col-3 { width: 100%; }
  .col-4 { width: 100%; }

  .contained {
    width: 80%;
    margin-left: auto;
    margin-right: auto;
  }
}

</style>
 
</head>

<body>

<h1>Weather Station</h1>

<div class="container">
  <div class="row">

    <div class="col-3">
    <div class="card">

      Temperature (Celsius)
      <hr>
      <p id="text-temperaturec"></p>
      <div class="progressbar-border">
        <div id="progress-temperaturec" class="progressbar-inner">
        </div>
      </div>

    </div>
    </div>
    <div class="col-3">
    <div class="card">

      Temperature (Fahrenheit)
      <hr>
      <p id="text-temperaturef"></p>
      <div class="progressbar-border">
        <div id="progress-temperaturef" class="progressbar-inner">
        </div>
      </div>

    </div>
    </div>
    <div class="col-3">
    <div class="card">

      Humidity
      <hr>
      <p id="text-humidity"></p>
      <div class="progressbar-border">
        <div id="progress-humidity" class="progressbar-inner">
        </div>
      </div>

    </div>
    </div>

  </div>
    <div class="row">

    <div class="col-3">
    <div class="card">

      Dew Point
      <hr>
      <p id="text-dewpoint"></p>
      <div class="progressbar-border">
        <div id="progress-dewpoint" class="progressbar-inner">
        </div>
      </div>

    </div>
    </div>
    <div class="col-3">
    <div class="card">

      Wet Bulb
      <hr>
      <p id="text-wetbulb"></p>
      <div class="progressbar-border">
        <div id="progress-wetbulb" class="progressbar-inner">
        </div>
      </div>

    </div>
    </div>
    <div class="col-3">
    <div class="card">

      Light
      <hr>
      <p id="text-light"></p>
      <div class="progressbar-border">
        <div id="progress-light" class="progressbar-inner">
        </div>
      </div>

    </div>
    </div>

  </div>
</div>

</body>
</html>
)=====" ;