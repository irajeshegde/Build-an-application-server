var express = require("express");
var app = express();
app.use(express.static("public"));

app.get("/", function (req, res) {
  res.render("dashboard.ejs");
});

var server = app.listen(3000, "0.0.0.0", function () {
  var host = server.address().address;
  var port = server.address().port;
  console.log("listening at http://%s:%s\n", host, port);
});
