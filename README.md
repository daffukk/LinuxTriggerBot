# GNU/Linux Wayland TriggerBot

The TriggerBot that works in any game by detecting a new pixel in the center of screen.

Tested on:
 * Arch linux 

## TODO
- [X] Create config file to minimize interaction with code
- [X] Create auto keyboard event pick
- [ ] Fully fix image noise and false shots

# Setup
You must install some packages.


```bash 
cmake
opencv
ydotool
grim
```

> [!NOTE]
> To set a triggerKey you can change trig.setKey(58) at 133 line of code. (It's a key code, by default set to CAPSLOCK)

---

# Run 

Run `./build.sh` to compile application.

> [!WARNING]
> There might be some issues with opencv, if you have those, check [Tips and issues](#tips-and-issues) section.


Run `./LinuxTriggerBot` in the project directory:

* Enter your screen resolution
* Enter delay(70 is recommended)
* Enter your keyboard device event


Ingame you need to hold capslock and do not move camera.

---

# Tips and issues

> [!IMPORTANT]
> If you have issues with compiling, try to install these packages:
> ```bash
> hdf5
> vtk
> ```
>


> [!TIP]
> If you want to change keyboard, just add **`-k`** flag next to the applicaton. 
> ```bash
> ./LinuxTriggerBot -k
> ```
>

