//const { response } = require("express");

function processform() {
  console.log("Submitting");
  console.log("newId: " + document.getElementById('new-id').value);
  const id = document.getElementById('new-id').value;

  fetch(//'http://csci2720-g114.cse.cuhk.edu.hk/event/'
  'http://csci2720-g114.cse.cuhk.edu.hk/event/'+document.getElementById('new-event').value+'/loc/'+document.getElementById('new-loc').value,
  {
    //mode: 'np-cors',
    method: 'POST',
    header: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({
      id,
    }),
    
  })
  .then((response) => response.text())
  .then((data) => {
    console.log(data);
    document.body.innerHTML = data;
  });
  console.log("Done");
}