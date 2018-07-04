# list the device filename if either the F310 or F710 is connectec

import evdev

devices = [evdev.InputDevice(fn) for fn in evdev.list_devices()]

for device in devices:
    # print the device objects to allow us to see the filenames
	print(device.fn, device.name, device.phys)


	if device.name == 'Logitech Gamepad F710' or device.name == 'Logitech Gamepad F310':
		print("filename: ", device.fn)


