
                 Read Me


*******************************************************
*
*  Description 
*
*******************************************************

Objective: Create programs detect gamepad events.

Program 0: gamepad0.py
		   prints list of all accessible evend devices


Program 1: gamepad1.py
 		   opens gamepad device, using symbolic link id
		   prints the gamepad object information


Program 2: gamepad2.py
           prints list of connected devices
           loops through the list and prints the device filename if the F710 or F310 
              is connected


Program 3: 	print_gamepad_events.py

			opens gamepad device
			prints event object information

			requires Ctrl+c for program termination

			
Program 4:	print_gamepad_categorize_event.py

			opens gamepad device
			prints the categorized event information
			allows user to see event categories
			    key event
				absolute axis event
				synchronization event

			requires Ctrl+c for program termination


Program 5:	detect_gamepad_buttons.py

			opens gamepad device
			prints all key events
			for key down events
				prints the name of the button pressed down

Program 6:  detect_gamepad_axis_events.py
			
			opens gamepad device
			prints all axis events
			prints event values



*******************************************************
* 
*    Reference
*
*******************************************************

a) Thank you to Eric Goebelbecker. These programs are based on his published work at

http://ericgoebelbecker.com/2015/06/raspberry-pi-and-gamepad-programming-part-1-reading-the-device/


b) python-evdev docs: http://python-evdev.readthedocs.io/en/latest/index.html 




*******************************************************
*  Circumstances of programs
*******************************************************
Date: 7/4/18

   The programs run successfully.  
   
   The programs are developed and tested on Ubuntu 16.04,
   using python 3.6.5

   There are no known bugs.
   


*******************************************************
*  How to run the programs
*******************************************************

    Run script from command line

    Change to the directory that contains the file by:
    % cd [directory_name] 

    run the script:
    % python3 gamepad0.py 

    % python3 gamepad1.py 

    % python3 gamepad2.py 

    % python3 print_gamepad_events.py

    % python3 print_gamepad_categorize_event.py

    % python3 detect_gamepad_buttons.py

    % python3 detect_gamepad_axis_events.py



*******************************************************
*
*  Dependencies
*
*******************************************************

Package: python-evdev

To install:  sudo pip install evdev

or if you have installed pip under python3: sudo pip3 install evdev

Documentation: http://python-evdev.readthedocs.io/en/latest/ 




*******************************************************
*
*  Linux input group 
*
*******************************************************

User must be a member of group input


To see user's group memberships

$ groups userName


To add user to the group

$ sudo usermod -aG input userName

Then the user must logout and log back in.



*******************************************************
*
*  Hardware Used for testing
*
*******************************************************


Logitech Wired Gamepad F310

On my Ubuntu system, after plugging in the usb gamepad, listing the
contents of /dev/input/by-id shows symbolic links created.


Type the command: ls /dev/input/by-id  

Output:
usb-Logitech_Gamepad_F310_BBECCB89-event-joystick
usb-Logitech_Gamepad_F310_BBECCB89-joystick


To find which event to which the symlink points:

Type the command: ls -l /dev/input/by-id

Output:
lrwxrwxrwx 1 root root 10 Jul  4 08:37 usb-Logitech_Gamepad_F310_BBECCB89-event-joystick -> ../event16
lrwxrwxrwx 1 root root  6 Jul  4 08:37 usb-Logitech_Gamepad_F310_BBECCB89-joystick -> ../js0





Logitech Wireless Gamepad F710


On my Ubuntu system, after plugging in the usb gamepad, listing the
contents of /dev/input/by-id shows symbolic links created.


ls /dev/input/by-id  

usb-Logitech_Wireless_Gamepad_F710_0A329D38-event-joystick
usb-Logitech_Wireless_Gamepad_F710_0A329D38-joystick


To find which event to which the symlink points:

ls -l /dev/input/by-id

lrwxrwxrwx 1 root root 10 Feb 16 08:37 usb-Logitech_Wireless_Gamepad_F710_0A329D38-event-joystick -> ../event15
lrwxrwxrwx 1 root root  6 Feb 16 08:37 usb-Logitech_Wireless_Gamepad_F710_0A329D38-joystick -> ../js0





*******************************************************
*
*  Sample Output
*
*******************************************************

File: print_gamepad_events.py

purpose: prints gamepad events that show the event code, type and value

Example output:

event at 1518797947.807215, code 305, type 01, val 01
event at 1518797947.807215, code 00, type 00, val 00
event at 1518797948.043210, code 305, type 01, val 00
event at 1518797948.043210, code 00, type 00, val 00
event at 1518797949.679154, code 04, type 03, val 128
event at 1518797949.679154, code 00, type 00, val 00
event at 1518797949.683154, code 04, type 03, val 899
event at 1518797949.683154, code 00, type 00, val 00
event at 1518797949.687107, code 04, type 03, val 2698
event at 1518797949.687107, code 00, type 00, val 00




File: print_gamepad_categorize_event.py

purpose: show event categories

Example output:

absolute axis event at 1518798318.168858, ABS_HAT0X 
synchronization event at 1518798318.168858, SYN_REPORT 
absolute axis event at 1518798318.352872, ABS_HAT0X 
synchronization event at 1518798318.352872, SYN_REPORT 
key event at 1518798319.816986, 307 (['BTN_NORTH', 'BTN_X']), down
synchronization event at 1518798319.816986, SYN_REPORT 
key event at 1518798320.036958, 307 (['BTN_NORTH', 'BTN_X']), up
synchronization event at 1518798320.036958, SYN_REPORT 
key event at 1518798323.713267, 305 (['BTN_B', 'BTN_EAST']), down
synchronization event at 1518798323.713267, SYN_REPORT 
key event at 1518798323.913296, 305 (['BTN_B', 'BTN_EAST']), up
synchronization event at 1518798323.913296, SYN_REPORT 
absolute axis event at 1518798325.389494, ABS_RY 
synchronization event at 1518798325.389494, SYN_REPORT 
absolute axis event at 1518798325.393493, ABS_RY 




*******************************************************
*
*  Joystick test using js device
*
*******************************************************

For a quick joystick test, install joystick package

 $ sudo apt-get install joystick

Run

 $ jstest /dev/input/js0