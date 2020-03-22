// jshint esversion: 6
const fs = require("fs");
const { promisify } = require("util");
const readDirAsync = promisify(fs.readdir);
const checker = require("../build/Release/checker");

async function writeExercises() {
  let exercises = await readDirAsync("exercises/");
  console.log(exercises);
  const ex_list = document.getElementById("exercises-list");
  for (const exercise of exercises) {
    ex_list.innerHTML += `<li id="${exercise}" onclick="loadExercise(this.id)"><a href="#"> ${exercise} </a> </li>`;
  }
}

writeExercises();

const MarkdownIt = require("markdown-it");
var md = new MarkdownIt();

let currentExercise = null;

function loadExercise(clicked_id) {
  currentExercise = clicked_id;
  fs.readFile(`exercises/${clicked_id}/README.md`, "utf8", (err, data) => {
    if (err) console.log("Something went wrong");
    else document.getElementById("exerciseDetails").innerHTML = md.render(data);
  });
  fs.readFile(`exercises/${clicked_id}/solution.cpp`, "utf8", (err, data) => {
    if (err) console.log("Something went wrong");
    else myCodeMirror.setValue(data);
  });
  // show compile or check button
  document.getElementById("check-sol-btn").disabled = false;
}
function compile() {
  // save the written code in solution.cpp
  const code = myCodeMirror.getValue();
  fs.writeFile(`exercises/${currentExercise}/solution.cpp`, code, err => {
    if (err) {
      return console.log(err);
    }

    console.log("The file was saved!");
    // compile or check
    // tell the user whether it's a correct or a wrong answer!
    alert(checker.verify(parseInt(currentExercise)));
  });
}
