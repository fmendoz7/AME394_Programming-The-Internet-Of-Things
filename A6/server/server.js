var nodemailer = require('nodemailer');
let transporter = nodemailer.createTransport('smtp://ame394fall2018%40gmail.com:fmendoz7@asu.edu');
var express = require("express");
var app = express();
var bodyParser = require('body-parser');
var errorHandler = require('errorhandler');
var methodOverride = require('method-override');
var hostname = process.env.HOSTNAME || 'localhost';
var port = 1234;
var lastSend = 0;

app.get("/setValue", function (req, res)
{
  VALUEt = parseFloat(req.query.t);
  VALUEh = parseFloat(req.query.h);
  VALUEtime = new Date().getTime();
  var id = req.query.id;
	var dataObj =
  {
		t: VALUEt,
		h: VALUEh,
		time: VALUEtime

	}

	if (VALUEt > 100) //100 degress
	{
		var now = new Date().getTime();

		if(now - lastSend > 5*60*1000) //5minutes
		{
			console.log("The temperature is" + VALUEt + ", email sent");
			sendEmail();
			lastSend = now; //resets it
		}

	res.send("2");
}
	else
	{
		console.log("The temperature is" + " " + VALUEt + ",email not sent. Temperature needs to be above 100 to be sent.");
		//sendEmail();
			res.send("2");

	}
});

function sendEmail()
{
  nodemailer.createTestAccount((err, account) => {

var transporter = nodemailer.createTransport({
 service: 'gmail',
 auth: {
        user: 'fmendoz7@asu.edu',
        pass: 'HanchiBoy77***>>'
    }
});

    // setup email data with unicode symbols
    let mailOptions = {
        from: '"Test account" <fmendoz7@asu.edu>', // sender address
        to: 'fmendoz7@asu.edu', // list of receivers
        subject: 'Sensor Alert', // Subject line
        text: 'The temperature is' + ' ' + VALUEt + '!!!', // plain text body
        html: '<b>The temperature is' + ' ' +VALUEt + '!!!</b>' // html body
    };

  	  transporter.sendMail(mailOptions, (error, info) => {
	        if (error) {
	            return console.log(error);
	        }
	        console.log('Message sent: %s', info.messageId);
	        //Preview only available when sending through an Ethereal account
	       console.log('Preview URL: %s', nodemailer.getTestMessageUrl(info));
	});

  });
}

app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
