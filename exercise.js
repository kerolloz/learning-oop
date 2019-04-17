// jshint esversion: 6
const fs = require('fs');

function writeExercises() {
    let exercises = fs.readdirSync('exercises/');
    console.log(exercises);
    for (const exercise of exercises) {
        document.write(`<li id="${exercise}" onclick="loadExercise(this.id)"><a href="#"> ${exercise} </a> </li>`);
    }
}

var MarkdownIt = require('markdown-it'),
    md = new MarkdownIt();

let currentExercise = null;

function loadExercise(clicked_id) {
    currentExercise = clicked_id;
    fs.readFile('exercises/' + clicked_id + "/README.md", "utf8", (err, data) => {
        if (err)
            console.log("Something went wrong");
        else
            document.getElementById("exerciseDetails").innerHTML = md.render(data.replace(/<br>/g, "\n"));
    });
    fs.readFile('exercises/' + clicked_id + "/solution.cpp", "utf8", (err, data) => {
        if (err)
            console.log("Something went wrong");
        else
            myCodeMirror.setValue(data);
    });
    // show compile or check button

}
function compile() {
    const {
        exec
    } = require('child_process');
    // save the written code in solution.cpp
    const code = myCodeMirror.getValue();
    fs.writeFile('exercises/' + currentExercise + "/solution.cpp", code, (err) => {
        if (err) {
            return console.log(err);
        }

        console.log("The file was saved!");
        // compile or check
        // tell the user whether it's a correct or a wrong answer!
        const exerciseNumber = currentExercise.split("-");
        const addon = require('./build/Release/addon');
        alert(addon.verify(parseInt(exerciseNumber[1])));
    });

}