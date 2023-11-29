const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <title>Freezer Burn Setup</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <h3>Freezer Burn Setup</h3>
  <br><br>
  <form action="/get">
    Enter your name: <input type="text" name="name">
    <br>
    Max amount of minutes: <input type="text" name="seconds">
    <br>
    Wifi network: <input type="text" name="network">
    <br>
    Wifi password: <input type="password" name="netpass">
    <br>
    <input type="submit" value="Submit">
  </form>
  <h5>This webpage does not publicly store any sensitive Wifi information.</h5>
</body>
</html>)rawliteral";
