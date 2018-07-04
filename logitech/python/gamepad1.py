from evdev import InputDevice

# using symbolic link from by-id 

# F710
#gamePad = InputDevice('/dev/input/by-id/usb-Logitech_Wireless_Gamepad_F710_0A329D38-event-joystick')

#F310
gamePad = InputDevice('/dev/input/by-id/usb-Logitech_Gamepad_F310_BBECCB89-event-joystick')


print("\nPrint gamepad object information\n")
print (gamePad)
print("\n")

