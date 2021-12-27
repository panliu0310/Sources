const express = require('express');
const app = express();
const cors = require('cors');
const bodyParser = require('body-parser');

app.use(cors());

app.use(express.json());

app.use(bodyParser.urlencoded({extended: false}));

app.get('/event/:eventId/loc/:locId', function (req, res) {
          let pa = req.params;
          console.log('request received');
          res.send(
                      'Event ID: ' + pa.eventId + '<br>Location: ' + pa.locId
                    );
});

app.post('/event/:eventId/loc/:locId', function(req, res) {
        let pa = req.params;
        console.log('Post request received');
        console.log('req.body.id:' + req.body.id);
          res.send(
                      'Event ID: ' + pa.eventId + '<br>Location: ' + pa.locId + '<br>Login ID: ' + req.body.id
                    );
});

app.all('/*', function (req, res) {
        res.send("Hello World!");

// listen to port 2114
const server = app.listen(2114);