// jshint esversion: 6
import { readdirSync, readFile, writeFile } from "fs";

function writeExercises() {
  let exercises = readdirSync("exercises/");
  console.log(exercises);
  for (const exercise of exercises) {
    document.write(
      `<li id="${exercise}" onclick="loadExercise(this.id)"><a href="#"> ${exercise} </a> </li>`
    );
  }
}

import MarkdownIt from "markdown-it";
var md = new MarkdownIt();

let currentExercise = null;

function loadExercise(clicked_id) {
  currentExercise = clicked_id;
  readFile("exercises/" + clicked_id + "/README.md", "utf8", (err, data) => {
    if (err) console.log("Something went wrong");
    else
      document.getElementById("exerciseDetails").innerHTML = md.render(
        data.replace(/<br>/g, "\n")
      );
  });
  readFile("exercises/" + clicked_id + "/solution.cpp", "utf8", (err, data) => {
    if (err) console.log("Something went wrong");
    else myCodeMirror.setValue(data);
  });
  // show compile or check button
}
function compile() {
  // save the written code in solution.cpp
  const code = myCodeMirror.getValue();
  writeFile("exercises/" + currentExercise + "/solution.cpp", code, err => {
    if (err) {
      return console.log(err);
    }

    console.log("The file was saved!");
    // compile or check
    // tell the user whether it's a correct or a wrong answer!
    const exerciseNumber = currentExercise.split("-");
    const addon = require("./build/Release/addon");
    alert(addon.verify(parseInt(exerciseNumber[1])));
  });
}
