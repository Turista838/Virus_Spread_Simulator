# Virus_Spread_Simulator

### Project developed for 'Programming', a first year subject @ISEC

#### Guide:

This program aims to simulate the spread of a viral agent in a closed space with people. It can predict virus behavior by using various mathematical models. This program is prepared for the following functions:
* Advance 1 Iteration in Simulation: calculations and collection of new data are performed.
* Display Statistics: displays statistical data including rate of sick people, rate of healthy people and rate of immune people.
* Add Patient: add a person in a room of your choice.
* Transfer Patients: Transfer patients to a room of your choice.
* Go Back X Iterations: allows you to go back up to 3 iterations.

When starting the program, the user must enter the name of the closed space file (must be in .bin format), and the name of the patients file (must be in .txt format). Any error in formatting these two files, the program closes immediately.

The closed space binary file must contain an ID, capacity and connections between rooms (maximum 3 connections). These connections serve to move people to other rooms (one closed space can have several rooms), and they don't interfere with dissemination, meaning there is no spread of the viral agent between rooms. For a room to connect to the other, there must necessarily be connections between the two, that is, for a room that connects to the other, this must be connected to the last one and vice versa.

The text file with the list of people must contain an alphanumeric code (one of each person), their age, and their status (S-healthy, D-sick and I-immune). In case you are sick, the count of the number of days you have been sick must also be entered. This information must be entered in one line per patient, and each patient's data separated by at least one space.

At the end of the program, the final statistical report and the final list of people, whose file name is chosen by the user, are also automatically saved.
