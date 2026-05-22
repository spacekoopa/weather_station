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
  console.log("function readAjax");
  if (myAjax.status==200)                         // HTTP-status OK
  {

    console.log("Ajax.status == 200 Ok");

 /*
    Expected JSON-Object of data:
    {
      "temperatureC": String,
      "temperatureF": String,
      "humidity":     String,
      "dewPoint":     String,
      "wetBulb":      String,
      "light":        String 
    }
    */

    let data = JSON.parse(myAjax.responseText);                 // LED state from response body; parse JSON to JS-Object

    let paragraph = document.getElementById("test");
    paragraph.innerText = data;

    console.log(data);
  }
}
 
function httpGet(parameter)            // GET request 
{
  myAjax.open ("GET", url + parameter, true);
  myAjax.send();
}

</script>

<style type="text/css" media="screen, print, projection">



</style>
 
</head>

<body>

<p id="test">Hier ist ein paragraph</p>

</body>
</html>
)=====" ;