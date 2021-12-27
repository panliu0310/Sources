//const { response } = require("express");

function processform() {
  console.log("Submitting");

  fetch(//'http://csci2720-g1.cse.cuhk.edu.hk/event/'
  'http://localhost:3000/event/'+document.getElementById('new-event').value+'/loc/'+document.getElementById('new-loc').value,
  {
    //mode: 'np-cors',
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({
      id: document.getElementById('new-id').value
    }),
    
  })
  .then((response) => response.text())
  .then((data) => {
    console.log(data);
    document.body.innerHTML = data;
  });
  console.log("Done");
}