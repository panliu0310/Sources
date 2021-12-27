// Name: Liu Hoi Pan
// SID: 1155127464

// require express
var express = require('express');
var app = express();
// require mongoose
var mongoose = require('mongoose');
var dbUri = "mongodb://s1155127464:x02795@localhost/s1155127464"
mongoose.connect(dbUri);
var db = mongoose.connection;

// require body-parser
const bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({extended: false}));

// Upon connection failure
db.on('error', console.error.bind(console, 'connection error:'));
// Upon opening the database successfully
db.once('open', function () {
console.log("Connection is open...");
});

// database schema (20%)

var EventSchema = mongoose.Schema({
  eventId: {type: Number, required: true, unique: true},
  name: {type: String, required: true},
  loc: {type: mongoose.Schema.Types.ObjectId, ref: 'Location'},
  quota: {type: Number},
});

var Event = mongoose.model('Event', EventSchema);

var LocationSchema = mongoose.Schema({
  locId: {type: Number, required: true, unique: true},
  name: {type: String, required: true},
  quota: {type: Number},
})

var Location = mongoose.model('Location', LocationSchema);

// GET and POST (30%)

app.get('/event/:eventId', function(req, res) {
  Event.findOne({eventId: req.params['eventId']},
    'eventId name loc quota',
    function (err, e) {
      if (err || e === null) {
        res.send("No event ID found in database");
      } 
      if (e !== null) {
        Location.findOne({_id: e.loc},
        function (err2, e2) {
          if (err2 || e2 === null) res.send("No Loc ID found in database");
          if (e2 !== null) {
            res.send("This is event  " + e.eventId + ":<br>\n" + 
            "Event name: " + e.name + "<br>\n" +
            "location ID: " + e.loc + "<br>\n" +
            "location name: " + e2.name + "<br>\n" +
            "Event quota: " + e.quota + "<br>\n" +
            "Ref: " + e);
          }
        });
      }
    });
});

app.post('/event', function (req, res) {
  var eventId;
  var eventName = req.body['name'];
  var eventLocation = req.body['loc'];
  var eventQuota = req.body['quota'];
  Event.find().sort({eventId: -1})
  .then((data) => {
    eventId = data[0].eventId + 1;
    Location.findOne({locId: eventLocation}, 
    'locId name quota', function (err2, e2) {
      if (err2 || e2 === null) {
        res.send("such location id not exists in database");
      }
      if (e2 !== null) {
        if (e2.quota < eventQuota) {
          res.send("The location quota is smaller than event quota, please find another location");
        } else {
          Event.create({
            eventId: eventId,
            name: eventName,
            loc: e2._id,
            quota: eventQuota
          }, function(err3, e3) {
            if (err3 || e3 === null) {
              res.send("some input are invalid");
            }
            if (e3 !== null) {
              res.status(201).header({Location: "/event/" + eventId}).send("Event created!");
            }
          });
        }
      }  
    });
  });
});

// DELETE (20%)

app.delete('/event/:eventId', function(req, res) {
  Event.findOne({eventId: req.params['eventId']},
    'eventId name loc quota',
    function (err, e) {
      if (err || e === null) {
        res.send("No event ID found in database");
      } 
      if (e !== null) {
        Location.findOne({_id: e.loc},
        function (err2, e2) {
          if (err2 || e2 === null) res.send("such location id not exists in database");
          if (e2 !== null) {
            Event.remove({eventId: req.params['eventId']}, function (err3, e3) {
              res.send("This is event  " + e.eventId + ":<br>\n" + 
              "Event name: " + e.name + "<br>\n" +
              "location ID: " + e.loc + "<br>\n" +
              "location name: " + e2.name + "<br>\n" +
              "Event quota: " + e.quota + "<br>\n" +
              "Ref: " + e + "<br>\n" +
              "Event deleted!");
            });
          }
        });
      }
    });
})

// Some more queries (30%)

// GET http://csci2720-g114.cse.cuhk.edu.hk/event

app.get('/event', async function(req, res) {
  var document = "";
  await Event.find(async function(err, e) {
    if (err || e === null) {
      res.send("No event in database");
    }
    if (e !== null) {
      e.forEach(async i => {
        await Location.findOne({_id: i.loc}, 'locId name quota', (err2, e2) => {
          if (err2 || e2 === null) {
            res.send("such location id not exists in database")
          }
          if (e2 !== null) {
            document = document +
            "Event ID  " + i.eventId + ":<br>\n" + 
            "Event name: " + i.name + "<br>\n" +
            "location ID: " + i.loc + "<br>\n" +
            "location name: " + e2.name + "<br>\n" +
            "Event quota: " + i.quota + "<br>\n" + "<br>\n"
          }
        });
      });
    }
  }).then(() => setTimeout(() => {
    res.send(document);
  }, 100
  ));         
})

// GET http://csci2720-g114.cse.cuhk.edu.hk/loc
// GET http://csci2720-g114.cse.cuhk.edu.hk/loc?quota=number

app.get('/loc', function (req, res) {
  var keyword = req.query['quota'];
  var document = "";
  if (keyword !== undefined) {
    Location.find({quota:{ $gte: keyword }}, function(err, e) {
      if (err || e === null) {
        res.send("No data satisfy the criteria");
      }
      if (e !== null) {
        e.forEach(i => {
          document = document +
          "location ID " + i.locId + ":<br>\n" + 
          "location name: " + i.name + "<br>\n" +
          "location quota: " + i.quota + "<br>\n" + "<br>\n"
        });
      }
    }).then(() => res.send(document));
  } else {
    Location.find(function(err, e) {
      if (err || e === null) {
        res.send("No data in database");
      }
      if ( e !== null) {
        e.forEach(i => {
          document = document +
          "location ID " + i.locId + ":<br>\n" + 
          "location name: " + i.name + "<br>\n" +
          "location quota: " + i.quota + "<br>\n" + "<br>\n"
        });
      }
    }).then(() => res.send(document));
  }
})

// GET http://csci2720-g114.cse.cuhk.edu.hk/event/loc/locationID

app.get('/loc/:locId', function(req, res) {
  Location.findOne({locId: req.params['locId']},
    'locId name quota',
    function(err, e) {
      if (err || e === null) {
        res.send("No location ID found in database");
      }
      if (e !== null) {
        res.send("Location ID: " + e.locId + "<br>\n" +
        "location name: " + e.name + "<br>\n" +
        "location quota: " + e.quota + "<br>\n");
      }
    })
})

// POST http://csci2720-g114.cse.cuhk.edu.hk/loc

app.post('/loc', function(req, res) {
  var locId;
  var locName = req.body['name'];
  var locQuota = req.body['quota'];
  Location.find().sort({locId: -1})
  .then((e) => {
    if (e === null) {
      Location.create({
        locId: 1,
        name: locName,
        quota: locQuota
      }, function(err2, e2) {
        if (err2 || e2 === null) {
          res.send("e2 some input are invalid");
        }
        if (e2 !== null) {
          res.status(201).header({Location: "/loc/" + 1}).send("Location created!");
        }
      });
    } else {
      locId = e[0].locId + 1;
      Location.create({
        locId: locId,
        name: locName,
        quota: locQuota
      }, function(err4, e4) {
        if (err4 || e4 === null) {
          res.send("some input are invalid");
        }
        if (e4 !== null) {
          res.status(201).header({Location: "/loc/" + locId}).send("Location created!");
        }
      });
    }
  });
});

app.all('/*', function(req, res) { res.status(404).send('Not found'); });
  // listen to port 2114
const server = app.listen(2114);