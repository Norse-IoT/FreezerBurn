const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <title>Freezer Burn Setup</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <h3>Freezer Burn Setup</h3>
  <br><br>
  <form action="/configure" method="post">
    <!-- Configue WiFi -->
    <fieldset>
        <legend>Enter your WPA2 WiFi credentials</legend>
        <!-- Note that html uses kebab case because it isn't case sensitive -->
        <div>
            <label for="eap-id">EAP ID</label>
            <input type="text" id="eap-id" name="eap-id" value="" />
        </div>
        <div>
            <label for="eap-username">EAP USERNAME</label>
            <input type="text" id="eap-username" name="eap-username" value="" />
        </div>
        <div>
            <label for="eap-password">EAP PASSWORD</label>
            <input type="password" id="eap-password" name="eap-password" value="" />
        </div>
    </fieldset>

    <!-- SMS configuraiton not included, because we don't know what's required.
        This is why it's important this solution is scalable. -->

    <div>
        <!-- Configure phone number to contact -->
        <label for="phone">Phone Number</label>
        <input type="tel" id="phone" name="phone" pattern="\d{10}" />
    </div>
    <div>
        <!-- Time Limit -->
        <label for="time-limit">Time Limit</label>
        <input type="number" id="time-limit" name="time-limit" />
    </div>
    <div>
        <!-- Freezer Name -->
        <label for="freezer-name">Freezer Name</label>
        <input type="text" id="freezer-name" name="freezer-name" />
    </div>

    <input type="submit" value="Submit">
</form>
  <h5>This webpage does not publicly store any sensitive Wifi information.</h5>
</body>
</html>)rawliteral";
