# Stratego

The Stratego game was developed in C++.

## Introduction

This repository will contain the Stratego project. It will be continuously updated by the team members.

This project will respect the different design patterns such as :
	1. MVC
	2. Observer/Observable

### Description of the game
Stratego is a group game about war that requires a great deal of strategic thinking. 
The origin of the game comes from the Netherlands, where it was invented shortly after the Second World War. 
But at that time, the game was still a table game. Since then, the game has been transformed from a board game to a field game: first with playing cards, then with specially created cards

**Source: Wikipedia. Link: https://fr.wikipedia.org/wiki/Stratego_(homonymity)**

Project created by :
		- Basile Routier - 54018
		- Ian Cotton - 55019

## Header
~~All headers are located in the Stratego folder~~
~~Some headers can be modified due to the fact that we can't model everything directly~~
~~Attributes and methods contain const to allow secure and quicker access to attributes~~


## Library
> The library replaces the old Stratego folder containing all the source files, headers, etc...
	1. Allows a better decomposition between the model and our view/controller
	2. Allows us to have a graphical and console view afterwards

### Model
	The model is in the stratego_model folder
		- Contains the HEADERS and SOURCES files
1. ***We have replaced the bare pointers by optionals 'Case' and optional 'Piece'***.
	1. **This modification was done _during_ the project to replace the pointers and not have to manage them anymore**.
	2. The modification also entails that a Case contains a Piece and is not a Piece.
2. ***We have taken into account the comments posted in the COMMENTS.md file of iteration 1 and tried to reduce the whole thing. Only the positions have been left unchanged because it makes it easier to test things in our methods***.
2. **Some changes have been added to the GUI to make the game run without complications.
	1. *We have a method that converts a position to a direction.
	2. *A method to get the game in a 2d string table version to know the location of the pieces and boxes*.

### View console
	The important classes for the use of the console view can be found in the stratego-view-console file
		- Contains the important classes
			- Controller
			- View

## REPORT - MTD/MCD
The technical class diagram is located in the MCD folder, all attributes and methods are located directly in the diagram
Types and associations are specified on it
1. **Modifications are to be made in the diagram**.
	- Some classes have undefined and useless methods
	- Some files have been deleted to reduce too extreme and useless decomposition

### Changes in the MTD
Some changes took place such as:
	1. Modification of pointers to optional
	2. Change of methods and removal of unused methods
	3. Respect of the DRY principle
	4. ***Big changes have taken place at the level of classes***.
		- This is due to the fact that a box is not a room but contains one
		- It was necessary to readapt the whole structure of our boxes
# COMPILATION
***!!! IT IS IMPORTANT TO FOLLOW THE FOLLOWING PROCEDURE OTHERWISE THE PROGRAM WILL NOT FIND THE CONFIGURATION FILES!!!***
**If you decide to modify the configuration text files it will have NO impact on the tests**.
	1. To compile the project, please go to QT and go to :
		1. Projects then click on the 'Run' BUTTON and change the 'Working directory' and change to the path
			- Path : "i-cotton-b-routier\stratego_lib"
	2. Compile simply by pressing the button Buidl and Run
		- If an error message is displayed restart the compilation at the same time of run and everything will work :)
	3. Otherwise use QMake (which is normally done automatically)


# Implementation

## Console implementation
	Usage :
		1. Each day plays its turn and choose a piece to move in the game
		2. Asking the position of the piece and the direction to go
			- If one piece meets another, a fight is started between the two.
		3. For more rules, here is a link to this one: https://fr.wikipedia.org/wiki/Stratego
	Game image :
![View Image](Images/console.png)


## GUI implementation
	Controller: 
		1. The UPDATING_BOARD state is not used in the GUI version
			1. Is more complicated to implement (more code for less readability)
	Start button :
		1. If the configuration files are not correctly configured and the algorithms detect it -> the game closes abruptly (and no message is displayed)