# GNU/Linux Wayland TriggerBot

The TriggerBot that works in any game by detecting a new pixel in the center of screen.

## TODO
* Create auto keyboard event pick
* Fully fix image noise and false shots

## Setup
You must install some packages.

> There maybe will be some issues with opencv, if you have those, check "Issues" paragraph.

```
$ opencv
$ ydotool
$ grim
```

### Next you need to pick your keyboard.

* To set a keyboard, you need to find its event in `/dev/input/event*`, google how to do this. And then you need to change 52 and 54 lines.

* (Optional) To set a triggerKey you can change trig.setKey(58) at 133 line of code. (It's a key code, by default set to CAPSLOCK)


## Run 

Run `./build.sh` to compile application.

Run `./LinuxTriggerBot` in the project directory.

Ingame you need to hold capslock and do not move camera.
