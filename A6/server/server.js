/*
  Programmer: Francis Mendoza
  Date: 11/27/18, 17:32 hrs MST
  Purpose: AME394 Fall 2018- calculate average for a selected day
*/
//---------------------------------------------------------------------------------------------------------
//Nodemailer
var nodemailer = require('nodemailer');
var transporter = nodemailer.createTransport('smtp://ame394fall2018%40gmail.com:francissamuelmendoza7@gmail.com');
//---------------------------------------------------------------------------------------------------------
//Variables
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
var tempAssess = 0;
//---------------------------------------------------------------------------------------------------------
//MongoDB variable with PROPER CREDENTIALS
//var db = MS.db("mongodb://root:OfaZ13Q6DERS@localhost:27017/sensorData");
var db = MS.db("mongodb://root:OfaZ13Q6DERS@localhost:27017/sensorData");
app.get("/", function (req, res)
{
    res.redirect("/index.html");
});
//---------------------------------------------------------------------------------------------------------
//Function: getAverage
app.get("/getAverage", function (req, res)
{
  //res.writeHead(200, {'Content-Type': 'text/plain'});
  var from = parseInt(req.query.from);
  var to = parseInt(req.query.to);

  db.collection("data").find({time:{$gt:from, $lt:to}}).toArray(function(err, result)
  {
  	console.log(err);
  	console.log(result);
  	var tempSum = 0;
  	var humSum = 0;
  	for(var i=0; i< result.length; i++)
    {
  		tempSum += result[i].t || 0;
  		humSum += result[i].h || 0;
  	}
  	var tAvg = tempSum/result.length;
  	var hAvg = humSum/result.length;
    res.send(tAvg.toString() + " " + hAvg.toString() + " " + from.toString() + "\r");
  });

});
//---------------------------------------------------------------------------------------------------------
//Function: getLatest
app.get("/getLatest", function (req, res)
{
    db.collection("data").find({}).sort({time:-1}).limit(10).toArray(function(err, result)
    {
        res.send(JSON.stringify(result));
    });
});
//---------------------------------------------------------------------------------------------------------
//Function: getData
app.get("/getData", function (req, res)
{
    var from = parseInt(req.query.from);
    var to = parseInt(req.query.to);
    db.collection("data").find({time:{$gt:from, $lt:to}}).sort({time:-1}).toArray(function(err, result)
    {
        res.send(JSON.stringify(result));
    });
});
//---------------------------------------------------------------------------------------------------------
//Function: getValue
app.get("/getValue", function (req, res)
{
  //res.writeHead(200, {'Content-Type': 'text/plain'});
  res.send(VALUEt.toString() + " " + VALUEh + " " + VALUEtime + "\r");
});
//---------------------------------------------------------------------------------------------------------
//Function: setValue
app.get("/setValue", function (req, res)
{
  VALUEt = parseFloat(req.query.t);
  VALUEh = parseFloat(req.query.h);
  VALUEtime = new Date().getTime();
	var dataObj =
  {
		t: VALUEt,
		h: VALUEh,
		time: VALUEtime
	};

  //Conditional: Temperature above 100* F
	if(VALUEt > 60)
  {
        var date = new Date(); // get the current date.
        if(date.getTime() >= (tempAssess + 300000))
        { // get the current time from the date object we just made, compare that to the previous date object, plus 5 minutes, if it's greater, send email
            tempAssess = date.getTime();
            sendEmail(VALUEt, date);
		    }
	}

/*
  //(nA) Conditional: Humidity above 50%
  if(VALUEh > 100)
  {
        var date = new Date(); // get the current date.
        if(date.getTime() >= (tempAssess + 300000))
        { // get the current time from the date object we just made, compare that to the previous date object, plus 5 minutes, if it's greater, send email
            tempAssess = date.getTime();
            sendEmail(VALUEt, VALUEh, date);
        }
  }
*/
  //MongoDB
	db.collection("data").insert(dataObj, function(err,result)
  {
		console.log("added data: " + JSON.stringify(dataObj));
	});

  res.send(VALUEtime.toString());
});
//---------------------------------------------------------------------------------------------------------
//Function: sendEmail
function sendEmail(temp, time)
{
  var message =
  {
      // Comma separated list of recipients
      to: 'Francis Mendoza <fmendoz7@asu.edu>',
      subject: 'IoT T&H Sensor: Warning',
      // plaintext body

      //Text to display trip and current temperature or humidity
      text: 'At ' + time + ' , temperature exceeded 100* F or humidity exceeded 50%.\n' + 'Current Temperature: ' + temp + '\n',

      //Can view as plain text HTML
      html:  '<p> At ' + time + ' , temperature exceeded 100* F or humidity exceeded 50%.\n' + 'Current Temperature: ' + temp + '\n </p>',
      watchHtml:  '<p> At ' + time + ' , temperature exceeded 100* F or humidity exceeded 50%.\n' + 'Current Temperature: ' + temp + '\n </p>'
  };

    console.log('Sending Mail');
    transporter.sendMail(message, function(err, result)
    {
        console.log(err,result);
    });
}
//---------------------------------------------------------------------------------------------------------
//Assorted Functions
app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
