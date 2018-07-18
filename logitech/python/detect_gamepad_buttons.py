from evdev import InputDevice, categorize, ecodes, KeyEvent, util

devices = [InputDevice(fn) for fn in util.list_devices()]


for device in devices:

	if device.name == 'Logitech Gamepad F710' or device.name == 'Logitech Gamepad F310':
		gamePad = InputDevice(device.fn)
		break



print("\nPrint gamepad object information\n")
print (gamePad)
print("\n")


print("Press gamepad buttons\n")


for event in gamePad.read_loop():
	if event.type == ecodes.EV_KEY:
		keyevent = categorize(event)
		print(keyevent)
		print("")

		if keyevent.keystate == KeyEvent.key_down:
			print('key down detected')
			print("keyevent.keycode")
			print(keyevent.keycode)
			print("")

			if keyevent.keycode[1] == 'BTN_X':
				print('button X\n')
			elif keyevent.keycode[0] == 'BTN_B':
				print('button B\n')
			elif keyevent.keycode[0] == 'BTN_A':
				print('button A\n')
			elif keyevent.keycode[1] == 'BTN_Y':
				print('button Y\n')
			elif keyevent.keycode == 'BTN_TL':
				print('button thumb left\n')
			elif keyevent.keycode == 'BTN_TR':
				print("button thumb right\n")
		