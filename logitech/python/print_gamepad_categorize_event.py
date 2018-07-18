import evdev 

devices = [evdev.InputDevice(fn) for fn in evdev.list_devices()]


for device in devices:

	if device.name == 'Logitech Gamepad F710' or device.name == 'Logitech Gamepad F310':
		gamePad = evdev.InputDevice(device.fn)
		break


print("\nPrinting gamepad event categories")

for event in gamePad.read_loop():
	print(evdev.categorize(event))
