let task = prompt("Which task you are testing? task 1: age");
if (task == 1)
{
    let x = prompt("What is your age?");
    let y = new Date().getFullYear();
    let z = y - x;
    let a = prompt("Do you have birthday this year yet?(Y/N)");
    if (a == "N")z = z - 1;
    alert("I guess you were born in " + z)
}
if (task == 2)
{
    let a = ["red", "pink", "green"];
    a.splice("1", "1", "orange", "yellow");
}