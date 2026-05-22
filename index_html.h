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
}

</script>

<style type="text/css" media="screen, print, projection">

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


/*
Grid-system with 12 columns
*/

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

<p id="test">Hier ist ein paragraph</p>

</body>
</html>
)=====" ;