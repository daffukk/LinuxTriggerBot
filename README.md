# GNU/Linux Wayland TriggerBot

The TriggerBot that works in any game by detecting a new pixel in the center of screen.

Tested on:
 * Arch linux 

## TODO
- [X] Create config file to minimize interaction with code
- [ ] Create auto keyboard event pick
- [ ] Fully fix image noise and false shots

# Setup
You must install some packages.

> There maybe will be some issues with opencv, if you have those, check [Tips and issues](#tips-and-issues) section.

```bash 
opencv
ydotool
grim
```

> [!NOTE]
> To set a triggerKey you can change trig.setKey(58) at 133 line of code. (It's a key code, by default set to CAPSLOCK)

---

# Run 

Run `./build.sh` to compile application.

Run `./LinuxTriggerBot` in the project directory:

* Enter your screen resolution
* Enter delay(70 is recommended)
* Enter your keyboard device event

> [!IMPORTANT]
> Check [Tips and issues](#tips-and-issues) for keyboard event information

Ingame you need to hold capslock and do not move camera.

---

# Tips and issues

### Keyboard event
1. Showing all keyboard devices:
```bash
ls /dev/input/by-id/ | grep kbd
``` 
2. Pick your keyboard from received list:
```bash
usb-MY_KEYBOARD-event-kbd -> ../event2
usb-ANOTHER_KEYBOARD-event-kbd -> ../event17
usb-SOME_KEYBOARD-if01-event-kbd -> ../event20
usb-MY_MICE_KEYBOARD_IDK_WHAT_ITS_DOING_HERE-if01-event-kbd -> ../event11
```
3. Copy your keyboard event path and paste it into application or to config instead:
```bash
/dev/input/event2
```

