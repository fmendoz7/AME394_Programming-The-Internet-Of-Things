var nodemailer = require('nodemailer');

//THIS LINE ALLOWS YOU CHOOSE THE SENDER FOR THE GMAIL ACCOUNT

//>>> DISCREP <<<
var transporter = nodemailer.createTransport('smtp://ame394fall2018%40gmail.com:francissamuelmendoza7@gmail.com');
//##############################################################################

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
var tempDisplacement = 0;

//var db = MS.db("mongodb://root:46Jl57IDy3Ji@127.0.0.1:27017/sensorData")
var db = MS.db("mongodb://admin:123456@localhost:27017/sensorData");
app.get("/", function (req, res)
{
    res.redirect("/index.html");
});

//----------------------------------------------------------------------------
app.get("/getAverage", function (req, res)
{
  //res.writeHead(200, {'Content-Type': 'text/plain'});
  var from = parseInt(req.query.from);
  var to = parseInt(req.query.to);
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
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
    console.log(tAvg, hAvg);
    res.send(tAvg.toString() + " " + hAvg.toString() + " " + from.toString() + "\r");
  });

});
//##############################################################################
//(!!!) TWO NEW HELPER FUNCTIONS ADDED TO PULL DATA

//GETS LATEST DATA
app.get("/getLatest", function (req, res)
{
  db.collection("data").find({}).sort({time:-1}).limit(10).toArray(function(err, result)
  {
      res.send(JSON.stringify(result));
      //Sending the collection of data as a string
  });
});

//GETS DATA
app.get("/getData", function (req, res)
{
  var from = parseInt(req.query.from);
  var to = parseInt(req.query.to);
  db.collection("data").find({time:{$gt:from, $lt:to}}).sort({time:-1}).toArray(function(err, result)
  {
      res.send(JSON.stringify(result));
  });
});
//##############################################################################
//GETVALUE METHOD
app.get("/getValue", function (req, res)
{
  //res.writeHead(200, {'Content-Type': 'text/plain'});
  res.send(VALUEt.toString() + " " + VALUEh + " " + VALUEtime + "\r");
});
//----------------------------------------------------------------------------
//SETVALUE METHOD
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
  //##############################################################################
  //CONDITION TO CALL SENDEMAIL
    //currentDate
    //tempDisplacement is the previous moment's date

    //(!!!) MODIFY FOR BOTH TEMPERATURE AND HUMIDITY
  console.log(data);
  if(VALUEt > 60)
  {
    var currentDate = new Date();
    if(currentDate.getTime() >= tempDisplacement + 300000)
    {
      tempDisplacement = date.getTime();
      sendEmail(VALUEt, currentDate);
    }
  }
//##############################################################################
	db.collection("data").insert(dataObj, function(err,result){
		console.log("added data: " + JSON.stringify(dataObj));
	});
  console.log(dataObj);
  console.log("We are getting data!");

  res.send(VALUEtime.toString());
});
    //##############################################################################
    //SENDMAIL FUNCTION
    function sendEmail(tempInput, timeInput)
    {
      var message =
      {
          // Comma separated list of recipients
          to: 'Francis Mendoza <fmendoz7@asu.edu>',
          subject: 'Button pressed',
          // plaintext body

          //MODIFY TO GET REAL TIME STATEMENT
          text: 'Button pressed!',
          // HTML body

          //Can view as plain text HTML
          html:  '<p>Your button was presssed </p>',
          watchHtml:  '<p>Your button was presssed </p>'
        }

        console.log('Sending Mail');
        transporter.sendMail(message, function(err, result)
        {
      	   console.log(err,result);
        });
    }
    //##############################################################################

app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
