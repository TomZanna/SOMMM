function qs(sel) {
  return document.querySelector(sel);
}
function displayIPSettings(isVisible) {
  qs("#indirizzo_ip").style.display = isVisible ? "" : "none";
  document.querySelectorAll("input.casella").forEach(function (userItem) {
    userItem.required = isVisible;
  });
}
// and here's the trick (works everywhere)
function g(f) {
  /in/.test(document.readyState) ? setTimeout("g(" + f + ")", 9) : f();
}
g(function () {
  // On document ready
  var r = new XMLHttpRequest();
  r.open("GET", "/config", true);
  r.onload = function () {
    if (r.status >= 200 && r.status < 400) {
      // Success!
      var configJson = JSON.parse(r.responseText);
      qs("#net_ssid").value = configJson["net_ssid"];
      qs("#aula").value = configJson["aula"];
      qs("#attuale").textContent = configJson["aula"];
      qs("#api_url").value = configJson["api_url"];
      if (configJson["net_static"] != null) {
        Object.entries(configJson["net_static"]).forEach(([key, value]) => {
          qs("#" + key).value = value.join(".");
        });
        qs("#net_static").checked = true;
        displayIPSettings(true);
      }
    } else console.error("Error on /config status " + r.status);
  };
  r.send();

  qs("#send").addEventListener("submit", function (e) {
    e.preventDefault(); //stop form from submitting
    var net_static;
    var net_ip = ["", "", "", ""];
    var net_sm = ["", "", "", ""];
    var net_dfgw = ["", "", "", ""];
    var net_dns = ["", "", "", ""];

    var net_ssid = qs("#net_ssid").value;
    var net_pswd = qs("#net_pswd").value;

    if (qs("#net_static").checked) {
      net_ip = qs("#net_ip").value.split(".");
      net_sm = qs("#net_sm").value.split(".");
      net_dfgw = qs("#net_dfgw").value.split(".");
      net_dns = qs("#net_dns").value.split(".");
      net_static = {
        net_ip: net_ip,
        net_sm: net_sm,
        net_dfgw: net_dfgw,
        net_dns: net_dns,
      };
    } else net_static = null;

    var aula = qs("#aula").value;
    var api_url = qs("#api_url").value;

    document.body.style.cursor = "wait";
    qs("#salva").disabled = true;

    var params = {
      net_ssid: net_ssid,
      net_pswd: net_pswd,
      net_static: net_static,
      aula: aula,
      api_url: api_url,
    };
    console.log(params);

    var r = new XMLHttpRequest();
    r.open("POST", "/save");
    r.setRequestHeader("Content-Type", "application/json");
    r.onload = function () {
      var resp = r.responseText;
      if (r.status >= 200 && r.status < 400) console.log(resp);
      // Success!
      // We reached our target server, but it returned an error (500)
      else console.error("Error " + resp + " - status " + r.status);
      alert(resp);
      document.body.style.cursor = "default";
      qs("#salva").disabled = false;
    };
    r.onerror = function () {
      // There was a connection error of some sort
      document.body.style.cursor = "default";
      qs("#salva").disabled = false;
      console.error("Errore di connessione: " + r.responseText);
      alert(r.responseText);
    };
    r.send(JSON.stringify(params));
  });
});
