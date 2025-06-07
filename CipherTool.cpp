/*****************************************
** File: CipherTool.cpp
** Project: Cipher
** Author: Vidal Bickersteth
** Date: 4/17/25
**
** This program is the CipherTool.cpp file of the Cipher project
** This file creates a variety of ciphers ranging from Atbash,
** Syctale, and Ong.
** This program allows you to display, encrypt, or decrypt all of your ciphers.
** You can also export your ciphers into a new file.
**
***********************************************/
#include "Cipher.h"
#include "Atbash.h"
#include "Scytale.h"
#include "CipherTool.h"
#include "Ong.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
// Preconditions - Input file passed and populated with Cipher
// Postconditions - CipherTool created
CipherTool::CipherTool(string file){
    m_filename = file;
}

// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
// Preconditions - m_ciphers is populated
// Postconditions - m_ciphers deallocated and vector emptied
CipherTool::~CipherTool(){
    //Destroyes all ciphers
    for(int i = 0; i < int(m_ciphers.size()); i++){
        delete m_ciphers.at(i);
        m_ciphers.at(i) = nullptr;
    }
}

// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers (a is Atbash, s is Scytale, and o is Ong)
// Preconditions - Input file passed and populated with Ciphers
// Postconditions - m_ciphers populated with Ciphers
void CipherTool::LoadFile(){
    ifstream inputStream; // The input stream variable that will load the 
                          // text file into the document
    string cipher; //The cipher
    string encrypt; // 0/1
    string text; // The message
    string key; //The num of keys
    bool crypt; // 0/1 as an int

    inputStream.open(m_filename); 
    if(inputStream.is_open()){
        // If the file is open, then 
        // the text file and all of it's lines
        // gets loaded into creating a vector of Ciphers
        // No spaces are allowed
        while(
            getline(inputStream, cipher, DELIMITER)
            && getline(inputStream, encrypt, DELIMITER)
            && getline(inputStream, text, DELIMITER)
            && getline(inputStream, key)){
            if((!cipher.empty() && !encrypt.empty() && !text.empty())){
                crypt = StringToBoolean((encrypt));
                if(cipher == "a"){
                    m_ciphers.push_back(new Atbash(string(text), crypt));
                }else if(cipher == "s" && !key.empty()){
                    int keys = stoi(key);
                    m_ciphers.push_back(new Scytale(string(text), crypt, keys));
                }else if(cipher == "o"){
                    m_ciphers.push_back(new Ong(string(text), crypt));
                }
            }
        }
        // The file gets closed after the load
    inputStream.close();
    }else{
        // Print this if the file does not get opened
        cout << "File does not exist." << endl;
        return;
    }
}

// Name: StringToBoolean
// Desc - Helper function that converts a string to a boolean for reading in file
// Preconditions - Passed string of either 0 or 1
// Postconditions - Returns false if 0 else true
bool CipherTool::StringToBoolean(string input){
    //Converts input to boolean if 0 or 1
    if(input == "0"){
        return false;
    }
    return true;
}

// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Displays ciphers
void CipherTool::DisplayCiphers(){
    //Displays ciphers
    if(m_ciphers.size() == 0){
        cout << "No data to display" << endl;
        return;
    }
    for(int i = 0; i < int(m_ciphers.size()); i++){
        cout << i+1 << ". " << m_ciphers.at(i)->GetMessage() 
        << m_ciphers.at(i)->ToString() << endl;
        cout << endl;
    }
}

// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
void CipherTool::EncryptDecrypt(bool crypt){
    //Encrypt or decrypt ciphers
    //Cipher must exist to encrypt or decrypt messages
    if(m_ciphers.size() == 0){
        cout << "No data to encrypt/decrypt" << endl;
        return;
    }
    int counter = 0; // To count how many messages are encrypted or decrypted
    if(crypt){
        for(int i = 0; i < int(m_ciphers.size()); i++){
            if(!m_ciphers.at(i)->GetIsEncrypted()){
                m_ciphers.at(i)->Encrypt();
                counter++;
            }
        }
        cout << counter << " ciphers Encrypted" << endl;
    }else{
        for(int i = 0; i < int(m_ciphers.size()); i++){
            if(m_ciphers.at(i)->GetIsEncrypted()){
                m_ciphers.at(i)->Decrypt();
                counter++;
            }
        }
        cout << counter << " ciphers Decrypted" << endl;
    }
}

// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - All ciphers exported
void CipherTool::Export(){
    string file; // file name
    ofstream outputstream; // The output stream variable that will save the 
                           // current document to a text file 
    int counter = 0;
    cout << "What would you like to call the export file?" << endl;
    getline(cin, file); 
    while(true){
        // If the input is invaild, the user is prompt to try again.
        if(cin.fail()){
            cin.clear();
            cin.ignore(256, '\n');
            cout << "What would you like to call the export file?" << endl;
            getline(cin, file);
        }else{
            break;
        }
    }   
    outputstream.open(file);
    if((outputstream.is_open())){
        // If the file is open, then 
        // the current document and all of it's ciphers
        // gets saved into the file
        for(int i = 0; i < int(m_ciphers.size()); i++){
            outputstream << m_ciphers.at(i) -> FormatOutput();
            counter++;
        }
        // The file gets closed after the save
        cout << counter << " ciphers exported" << endl;
        outputstream.close();
    }
}

// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_ciphers all populated
// Postconditions - Returns choice
int CipherTool::Menu(){
    int option; // The option from 1-8 that the user chooses

    // The main menu of Cipher
    // The user can choose to participate or exit
    cout << "What would you like to do?" << endl;
    cout << "1. Display All Ciphers" << endl;
    cout << "2. Encrypt All Ciphers" << endl;
    cout << "3. Decrypt All Ciphers" << endl;
    cout << "4. Export All Ciphers" << endl;
    cout << "5. Quit" << endl;
    cin >> option; 
    
    while(true){
        // If the input is invaild, the user is prompt to try again.
        if(cin.fail() || option < 1 || option > 5){
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid input. Please enter a valid value" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Display All Ciphers" << endl;
        cout << "2. Encrypt All Ciphers" << endl;
        cout << "3. Decrypt All Ciphers" << endl;
        cout << "4. Export All Ciphers" << endl;
        cout << "5. Quit" << endl;
        cin >> option;
        }else{
            break;
        }
    }
    // Returns the user's choice
    return option;
}

// Name: Start
// Desc - Loads input file, allows user to choose what to do
// Preconditions - m_ciphers populated with ciphers
// Postconditions - none
void CipherTool::Start(){
    int menu = 0; // stores the user's choice
    LoadFile();
    if(m_ciphers.size() == 0){
        cout << "No data loaded." << endl;
        return;
    }
    while(menu != 5){
        // The game will contiune to play until
        // the user wants to exit, which is 5.
        menu = Menu();
        switch(menu){
            case 1:
                if(cin.peek() == '\n'){
                    cin.ignore();
                }
                //displays ciphers
                DisplayCiphers();
                break;
            case 2:
                if(cin.peek() == '\n'){
                    cin.ignore();
                }
                //encrypt
                EncryptDecrypt(true);
                break;
            case 3:
                if(cin.peek() == '\n'){
                    cin.ignore();
                }
                //decrypt
                EncryptDecrypt(false);
                break;
            case 4:
                if(cin.peek() == '\n'){
                    cin.ignore();
                }
                //Saves ciphers
                Export();
                break;
            case 5:
                //Final message
                cout << "Thanks for using Cipher Encryption!" << endl;
                break;
            
        }
    }
}
