/*
    Name: Liu Hoi Pan
    Student ID: 1155127464
*/

function task0() {
    let x = document.getElementById("special");
    if (x.style.display === "none") {
        x.style.display = "block";
    } else {
        x.style.display = "none";
    }
}

function task1() {
    for ( let i = 0; i < 4; i++ ){
        let x = document.getElementsByClassName("sectionHeading")[i];
        if (x.classList.contains("text-start")){
            x.classList.remove("text-start");
            x.classList.add("text-center");
        }
        else if (x.classList.contains("text-center")){
            x.classList.remove("text-center");
            x.classList.add("text-end");
        }
        else if (x.classList.contains("text-end")){
            x.classList.remove("text-end");
            x.classList.add("text-start");
        }
    }
}

function task2() {
    let newHobby = prompt();

    // set up a new element
    let newBox = document.createElement("div");
    let element = '<div></div>';
    newBox.innerHTML = element;

    // set class
    newBox.classsName = "d-flex";
    newBox.querySelector("div").className = "m-2 p-3 bg-primary";

    let lastBox = document.querySelector("#task2hobby").lastElementChild;

    newBox.querySelector("div").innerHTML = newHobby;

    document.querySelector("#task2hobby").appendChild(newBox);
}

function task3ShowBar() {
    let x = document.getElementById("task3progressbox");
    if (x.style.visibility === "hidden") {
        x.style.visibility = "visible";
    } else {
        x.style.visibility = "hidden";
    }
}

function task3ScrollBar() {
    let x = document.getElementById("task3progressbar");
    let h = document.body.clientHeight - window.innerHeight;
    let myScroll = (window.scrollY / h) * 100;
    x.style.width = myScroll + "%";
}

async function processform() {

    let email = document.querySelector("#new-email");
    let comment = document.querySelector("#new-comment");

    if (email.validity.valid) {
        email.classList.remove("is-invalid");
        email.classList.add("is-valid");
    } else {
        email.classList.remove("is-valid");
        email.classList.add("is-invalid");
    }

    if (comment.validity.valid) {
        comment.classList.remove("is-invalid");
        comment.classList.add("is-valid");
    } else {
        comment.classList.remove("is-valid");
        comment.classList.add("is-invalid");
    }

    // Only the case that the email and text are of correct format can passes through this if statement 
    if (email.validity.valid && comment.validity.valid === false) {
        return;
    }

    // set up a new element
    let newComment = document.createElement("div");
    let element = '<div><svg height="100" width="100"><circle cx="50" cy="50" r="40"></svg></div><div><h5></h5><p></p></div><div><p></p><p></p><p></p><p></p><p></p></div>';
    newComment.innerHTML = element;

    // set the classes of the div and its children div's
    newComment.className = "d-flex";
    newComment.querySelectorAll("div")[0].className = "flex-shrink-0";
    newComment.querySelectorAll("div")[1].className = "flex-grow-1";

    //increment the comment id
    let lastComment = document.querySelector("#comments").lastElementChild;
    newComment.id = 'c' + (Number(lastComment.id.substr(1)) + 1);

    // change contents of <h5> and <p> according to form input with id
    document.getElementById("loading").innerHTML = "Loading... We need some time to access IP address.";
    
    let userIP;
    // get user's ip address first (need to wait some time due to fetch)
    await fetch("http://api.ipify.org/?format=text") 
    .then(res => res.text()) 
    .then(txt => userIP = txt);

    // bonus 3-5 (need to wait some time due to fetch)
    let x;
    await fetch("https://ipapi.co/" + userIP + "/json/")
    .then(res => res.json())
    .then(out => {
        x = out
    })
    // bonus 3 
    newComment.querySelectorAll("p")[3].innerHTML = "User's IP address: " + x.ip;
    // bonus 4
    newComment.querySelectorAll("p")[4].innerHTML = "User's location: " + x.country_name;
    // bonus 5
    newComment.querySelectorAll("p")[5].innerHTML = "User's region: " + x.region;

    newComment.querySelectorAll("h5")[0].innerHTML = document.querySelector("#new-email").value;
    newComment.querySelectorAll("p")[0].innerHTML = document.querySelector("#new-comment").value;
    
    // bonus 1
    newComment.querySelectorAll("p")[1].innerHTML = "Browser Information: " + navigator.appName;
    // bonus 2
    newComment.querySelectorAll("p")[2].innerHTML = "Data and time: " + Date();

    // draw circle
    let color = document.querySelectorAll("input[name=new-color]:checked")[0].value; // look for checked radio buttons
    newComment.querySelector("circle").setAttribute("fill", color);

    // append to #comment
    document.querySelector("#comments").appendChild(newComment);

    // reset the form
    document.querySelector("form").reset();
    email.classList.remove("is-valid");
    email.classList.remove("is-invalid");
    comment.classList.remove("is-valid");
    comment.classList.remove("is-invalid");
    document.getElementById("loading").style.display = "none";

    savefile(); // auto save comment after finishing all tasks

}

function savefile() {
    fetch('comments.txt', {
        method: 'PUT',
        body: document.querySelector("#comments").innerHTML
    });
}

function loadfile() {
    fetch("comments.txt")
    .then(res => res.text())
    .then(txt => document.querySelector("#comments").innerHTML = txt);
}