const express = require('express');
const app = express();
const cors = require('cors');
const bodyParser = require('body-parser');
var mongoose = require('mongoose');
mongoose.connect('mongodb://s1155127464:x02795@localhost/s1155127464');
var db = mongoose.connection;

var EventSchema = mongoose.Schema({
	eventId: {type: Number, required: true, unique: true},
	name: {type: String, required: true},
	loc: {type: String},
	quota: {type: Number}
});

var Event = mongoose.model('Event', EventSchema);

db.on('error', console.error.bind(console, 'Connection error:'));

db.once('open', function () {
	console.log("Connection is open...");
});

app.use(cors());

app.use(express.json());

app.use(bodyParser.urlencoded({extended: false}));

app.get('/event/:eventId', function(req, res) {
	Event.findOne({eventId: req.params['eventId']},
		'eventId name loc quota',
		function (err, e) {
			if (err) res.send(err);
			res.send("This is event  " + e.eventId + ":<br>\n" +
				"Event name: " + e.name + "<br>\n" +
				"Event location: " + e.loc + "<br>\n" +
				"Event quota: " + e.quota + "<br>\n" +
				"Ref: " + e);
		});
});

app.post('/event/:eventId/loc/:locId', function(req, res) {
	        let pa = req.params;
	        console.log('Post request received');
	        console.log('req.body.id:' + req.body.id);
	        res.send('Event ID: ' + pa.eventId + '<br>Location: ' + pa.locId + '<br>Login ID: ' + req.body.id);
});

app.all('/*', function (req, res) { res.send("Hello World!")});
  // listen to port 2114
  const server = app.listen(2114);
