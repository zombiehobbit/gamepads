
                 Read Me


*******************************************************
*  Description 
*******************************************************

Objective: 		Create a program that reads Logitech gamepad 

Functionality: 	main.c program 
                    sets up SIGINT signal interrupt handler
					opens /dev/input/js0
					loops until a ctrl+c signal interrupt is received
						reads gamepad 
						displays gamepad values readme
					 
                    frees dynamically allocated memory
					program terminates



*******************************************************
*  Source files
*******************************************************


Name:	main.c   

Dependencies: logitech.h provides gamepad access functions


Name: 	logitech.c  
			implements gamepad functions
            
            open connection to gamepad
            display gamepad values 

Name:   logitech.h
            gamepad struct
            gamepad function prototype declaration



*******************************************************
*  Circumstances of programs
*******************************************************
Date: 6/23/2018

	The programs compile and run successfully. 
   
	The program was developed and tested on Ubuntu 18.04,
	using gcc version 7.3.0

   	This program was developed to read values from a 
    Logitech gamepad.


    Please maintain this program as is, and create a new program for 
    specific gamepad applications.



*******************************************************
*  How to build and run the program
*******************************************************

Instructions: 	The Makefile in this directory creates an executable named etest

1. Folder receive_bytes contains the following files:

	main.c
	logitech.c
	logitech.h
	Makefile
	readme.txt

Follow steps 2 - 5 to build the shared object library files, install the library, configure
the cache, and include it in the searchable library path.

2. Build the executable

    Compile the program and build the object .o and executable files:
    % make


3. Run the program
   % ./etest



To clean the files: make clean