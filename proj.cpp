/*****************************************
** File: proj.cpp
** Project: Cipher
** Author: Vidal Bickersteth
** Date: 4/17/25
**
** This program is the proj.cpp file of the Cipher project.
** This file creates a CipherTool object, which allows you to 
** perform various encryption techniques.
**
**
***********************************************/
#include "CipherTool.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

//Inside the parameters for main, we can pass arguments
//argc is the count of arguments
//argv are the parameters themselves
int main(int argc, char* argv[]) {
  cout << "Welcome to Cipher Encryption" << endl;
  while (argc < 2) { //Checks to make sure the user passes a file to load
    cout << "You are missing a data file." << endl;
    cout << "Expected usage ./proj proj_data1.txt" << endl;
    cout << "The input file should have some strings to encrypt or decrypt" << endl;
    return 0;
  }
  CipherTool myCipher(argv[1]); //Creates a new ciphertool passing the filename
  myCipher.Start(); //Starts the cipherTool
  return 0;
}
