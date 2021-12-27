const express = require('express');
const app = express();
const cors = require('cors');

app.use(cors());

app.use(express.json());

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
  res.send(
    'Event ID: ' + pa.eventId + '<br>Location: ' + pa.locId + '<br>Login ID: ' + req.body.id 
  );
});

// listen to port 3000
const server = app.listen(3000);