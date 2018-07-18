from evdev import InputDevice, categorize, ecodes, KeyEvent, util

devices = [InputDevice(fn) for fn in util.list_devices()]


for device in devices:

	if device.name == 'Logitech Gamepad F710' or device.name == 'Logitech Gamepad F310':
		gamePad = InputDevice(device.fn)
		break


print("\nPress thumbstick\n")


for event in gamePad.read_loop():
	# event type 3 is EV_ABS
	if event.type == ecodes.EV_ABS:
		absaxisevent = categorize(event)
		print(absaxisevent)
		print("")

		if event.code == ecodes.ABS_X:   # ecodes.ABS_X is 3
			print('ABS_X detected, event.value: ', event.value)
		elif event.code == ecodes.ABS_Y: # ecodes.ABS_Y is 1
			print('ABS_Y detected, event value: ', event.value)
		elif event.code == ecodes.ABS_RX:
			print('ABS_RX dectected, event.value: ', event.value)
		elif event.code == ecodes.ABS_RY:
			print('ABS_RY detected, event.value: ', event.value)
		elif event.code == ecodes.ABS_Z:
			print('ABS_Z detected, event.value: ', event.value)
		elif event.code == ecodes.ABS_RZ:
			print('ABS_RZ detected, event.value: ', event.value)
		elif event.code == ecodes.ABS_HAT0X:
			print('ABS_HAT0X detected, event.value: ', event.value)
		elif event.code == ecodes.ABS_HAT0Y:
			print('ABS_HAT0Y detected, event.value: ', event.value)

		