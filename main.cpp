#include <iostream>
#include <string>
#include <thread>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <filesystem>
#include <chrono>
#include <atomic>
#include <fstream>
#include "header.h"

std::atomic<bool> hold(false);
std::atomic<bool> running(true);

class Trigger {
private:
  short delay;
  short actionKeyCode; 

public:

  void setDelay(short delay_in_ms) { 
    delay = delay_in_ms;
  }

  void setKey(short keyCode) { 
    actionKeyCode = keyCode;
  }

  short getDelay() {
    return delay;
  }
  
  void screenClip(int width, int height) {
    std::string cmd = "grim -g \"" + std::to_string(width) + "," + std::to_string(height) + " 10x10\" clip.png";
    system(cmd.c_str()); 
  }

  void screenStart(int width, int height){
    std::string cmd = "grim -g \"" + std::to_string(width) + "," + std::to_string(height) + " 10x10\" action.png";
    system(cmd.c_str()); 
  }

  short getKeyCode(){
    return actionKeyCode;
  }

};

int keyLog(short actionKey, std::string keyboardEvent) { 

    std::string cmd = "sudo chmod a+r " + keyboardEvent;
    system(cmd.c_str()); // needs to access the /dev/input/eventX file  
    system("ydotoold > /dev/null 2>&1 &"); // ydotool daemon
    int fd = open(keyboardEvent.c_str(), O_RDONLY); 
    if (fd == -1) {
      std::cerr << "Failed to open a device " << keyboardEvent << ". Try sudo.\n";
      return 1;
    }
    
    input_event ev;

    while (true) { 
      ssize_t n = read(fd, &ev, sizeof(ev));
      if (n == (ssize_t)sizeof(ev)) {
        if (ev.type == EV_KEY) {
          if (ev.value == 1) {
            if (ev.code == 54) { //rShift to exit
              std::cout << "Exit.\n";
              running = false;
              return 0;
            }   
          }

          if(ev.code == actionKey) {
            if (ev.value == 1 || ev.value == 2) {
              hold = true;
            }
         
            if (ev.value == 0) {
              hold = false;
            }
          }
        }
      }
    }

    close(fd); 
    return 0;
}


int main() {

  int screenWidth;
  int screenHeight;
  int triggerDelay;
  std::string keyboardEvent;

  if(!std::filesystem::exists("config.cfg")) { 

    std::ofstream file("config.cfg");
  
    std::cout << "Enter your screen width: ";
    std::cin >> screenWidth;
    file << screenWidth << "\n";
  
    std::cout << "Enter your screen height: ";
    std::cin >> screenHeight;
    file << screenHeight << "\n";

    std::cout << "Enter triggerbot delay (70 is highly recommended): ";
    std::cin >> triggerDelay;
    file << triggerDelay << "\n";

    keyboardEvent = findKeyboard();
    file << keyboardEvent << "\n";

  } else {

    std::ifstream file("config.cfg");
    
    if(file.is_open()) {
      file >> screenWidth >> screenHeight >> triggerDelay >> keyboardEvent;
    }
  }

  std::cout << "Using " << screenWidth << "x" << screenHeight << " resolution.\n";
  std::cout << "Delay: " << triggerDelay << "ms\n"; 


  screenWidth = (screenWidth / 2) - 5;
  screenHeight = (screenHeight / 2) - 5;

  Trigger trig;
  trig.setDelay((short)triggerDelay); //ms
  trig.setKey(58); //CAPSLOCK

  std::thread keyThread(keyLog, trig.getKeyCode(), keyboardEvent); 

  bool clipExist = false;
  bool singleClick = false;

  const std::filesystem::path currentDir = std::filesystem::current_path();
  const std::filesystem::path clip = currentDir / "clip.png";
  const std::filesystem::path action = currentDir / "action.png";

  while(running){

    if (hold){
      if (!clipExist) {
        trig.screenClip(screenWidth, screenHeight);
        clipExist = true;
      }
      trig.screenStart(screenWidth, screenHeight);
      
      if(differentpixels(clip.string(), action.string())) {
        if (!singleClick) {
          std::this_thread::sleep_for(std::chrono::milliseconds(trig.getDelay()));
          system("ydotool click 0xC0");
          std::cout << "SHOT!!!\n";
          singleClick = true;
        }
      }

    }
    if (!hold) {
      clipExist = false;
      singleClick = false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  
  keyThread.join();
  system("pkill ydotoold");
  return 0;
}
