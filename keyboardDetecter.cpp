#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string findKeyboard() {
  
  system("ls /dev/input/by-id/ | grep kbd > .keyboards.txt");

  std::ifstream file(".keyboards.txt");

  std::string line;

  std::vector<std::string> keyboards;

  if(file.is_open()) {
    while(std::getline(file, line)){
      keyboards.push_back(line);
    }
  }


  for(int i=0; i < keyboards.size(); i++){
    std::cout << " (" << i << "): " << keyboards[i] << std::endl;
  }
  
  int keyboardnumber;
  std::cout << "Pick your keyboard: ";
  std::cin >> keyboardnumber;

  std::string fullpath = "/dev/input/by-id/" + keyboards[keyboardnumber];

  return fullpath;
}

