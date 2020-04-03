var express = require("express");
var app = express();
var bodyParser = require("body-parser");
var mongo = require("mongodb");
const MongoClient = require("mongodb").MongoClient;
const uri = "mongodb://localhost/get_post_exercise";
app.use(express.static("public"));
app.use(bodyParser.json()); // to support JSON-encoded bodies
app.use(
  bodyParser.urlencoded({
    extended: true
  })
); // to support URL-encoded bodies
app.set("view engine", "ejs");

// TIMESTAMP FORMATTING FUNCTION
function getFormattedDate() {
  var date = new Date();
  var month = date.getMonth() + 1;
  var day = date.getDate();
  var hour = date.getHours();
  var min = date.getMinutes();
  var sec = date.getSeconds();

  month = (month < 10 ? "0" : "") + month;
  day = (day < 10 ? "0" : "") + day;
  hour = (hour < 10 ? "0" : "") + hour;
  min = (min < 10 ? "0" : "") + min;
  sec = (sec < 10 ? "0" : "") + sec;

  var str = date.getFullYear() + month + day + hour + min + sec;
  return str;
}

// GET LATEST UPDATE
app.get("/", (req, res) => {
  MongoClient.connect(
    uri, {
      useNewUrlParser: true,
      useUnifiedTopology: true
    },
    function (err, db) {
      if (err) throw err;
      var dbo = db.db("get_post_exercise");
      dbo.collection("data").findOne({}, {
          sort: {
            _id: -1
          }
        },
        function (err, result) {
          if (err) throw err;
          if (result == null) {
            console.log("Empty\n");
            res.redirect("/");
          } else {
            console.log(result);
            console.log("Found latest update\n");
            res.render("home", {
              result: result
            });
          }
          db.close();
        }
      );
    }
  );
});

// POST REQUEST TO MONGODB MADE BY ESP8266
app.post("/:temp/:hum", (req, res) => {
  var humidity = req.params.hum;
  var temp = req.params.temp;
  var today = getFormattedDate();
  console.log(today);
  MongoClient.connect(
    uri, {
      useNewUrlParser: true,
      useUnifiedTopology: true
    },
    function (err, db) {
      if (err) throw err;
      var dbo = db.db("get_post_exercise");
      var myobj = {
        temperature: temp,
        humidity: humidity,
        timestamp: today
      };
      dbo.collection("data").insertOne(myobj, function (err, res) {
        if (err) throw err;
        console.log("POST Request received!");
        console.log("Latest update inserted\n");
        db.close();
      });
    }
  );
  res.send(
    "Temperature = " +
    temp +
    ", Humidity = " +
    humidity +
    ", AirQuality = " +
    today
  );
});

var server = app.listen(3000, "0.0.0.0", function () {
  var host = server.address().address;
  var port = server.address().port;
  console.log("listening at http://%s:%s\n", host, port);
});