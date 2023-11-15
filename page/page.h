const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Freezer Burn Setup</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <h3>Freezer Burn Setup</h3>
  <br><br>
  <form action="/get">
    <br>
    Max amount of minutes: <input type="text" name="seconds">
    <br>
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";