var MS = require("mongoskin");
var express = require("express");
var app = express();
var bodyParser = require('body-parser');
var errorHandler = require('errorhandler');
var methodOverride = require('method-override');
var hostname = process.env.HOSTNAME || 'localhost';
var port = 1234;
var VALUEt = 0;
var VALUEh = 0;
var VALUEtime = 0;
var tempCheck = 0;
var nodemailer = require('nodemailer');

var transporter = nodemailer.createTransport('smtp://ame394fall2018%40gmail.com:francissamuelmendoza7@gmail.com');

//var db = MS.db("mongodb://root:OfaZ13Q6DERS@localhost:27017/sensorData");
var db = MS.db("mongodb://root:OfaZ13Q6DERS@localhost:27017/sensorData");
app.get("/", function (req, res) {
    res.redirect("/index.html");
});
function sendEmail(temp, time)
{
    var message = {
        // Comma separated list of recipients
        to: 'Francis Mendoza <francissamuelmendoza7@gmail.com>',
        subject: 'Temperature is over 100 degrees!!',
        // plaintext body
        text: 'The temperature reached over 100 degrees, currently it is: ' + temp + '°F at ' + time ,
        // HTML body
        html:  '<p> The temperature reached over 100 degrees, currently it is: ' + temp + '°F at ' + time + '</p>',
        watchHtml:  '<p> The temperature reached over 100 degrees, currently it is: ' + temp + '°F at ' + time + '</p>'
    };

    console.log('Sending Mail');
    transporter.sendMail(message, function(err, result){
        console.log(err,result);
    });


}

app.get("/getAverage", function (req, res) {
  //res.writeHead(200, {'Content-Type': 'text/plain'});
  var from = parseInt(req.query.from);
  var to = parseInt(req.query.to);

  db.collection("data").find({time:{$gt:from, $lt:to}}).toArray(function(err, result){
  	console.log(err);
  	console.log(result);
  	var tempSum = 0;
  	var humSum = 0;
  	for(var i=0; i< result.length; i++){
  		tempSum += result[i].t || 0;
  		humSum += result[i].h || 0;
  	}
  	var tAvg = tempSum/result.length;
  	var hAvg = humSum/result.length;
    res.send(tAvg.toString() + " " + hAvg.toString() + " " + from.toString() + "\r");
  });

});

app.get("/getLatest", function (req, res) {
    db.collection("data").find({}).sort({time:-1}).limit(10).toArray(function(err, result){
        res.send(JSON.stringify(result));
    });
});

app.get("/getData", function (req, res) {
    var from = parseInt(req.query.from);
    var to = parseInt(req.query.to);
    db.collection("data").find({time:{$gt:from, $lt:to}}).sort({time:-1}).toArray(function(err, result){
        res.send(JSON.stringify(result));
    });
});
app.get("/getValue", function (req, res) {
  //res.writeHead(200, {'Content-Type': 'text/plain'});
  res.send(VALUEt.toString() + " " + VALUEh + " " + VALUEtime + "\r");
});

app.get("/setValue", function (req, res) {
  VALUEt = parseFloat(req.query.t);
  VALUEh = parseFloat(req.query.h);
  VALUEtime = new Date().getTime();
	var dataObj = {
		t: VALUEt,
		h: VALUEh,
		time: VALUEtime
	};
	if(VALUEh > 80) {
        var date = new Date(); // get the current date.
        if(date.getTime() >= (tempCheck + 300000)) { // get the current time from the date object we just made, compare that to the previous date object, plus 5 minutes, if it's greater, send email
            tempCheck = date.getTime();
            sendEmail(VALUEt, date);
		}
	}
	db.collection("data").insert(dataObj, function(err,result){
		console.log("added data: " + JSON.stringify(dataObj));
	});
  res.send(VALUEtime.toString());
});


app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
