/*****************************************
** File: Scytale.cpp
** Project: Cipher
** Author: Vidal Bickersteth
** Date: 4/17/25
**
** This program is the Scytale.cpp file of Cipher project
** This file creates a Scytale object.
** This file encrypts or decrypts your message using Scytale cipher
** This file also contains keys to do the encryption/decryption
**
**
***********************************************/

#include "Cipher.h"
#include "Scytale.h"
#include <istream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

const char PADDING = '#';

// Name: Scytale (Default Constructor)
// Desc: Constructor to build an empty Scytale Cipher
// Preconditions - None
// Postconditions - Creates a Scytale cipher
Scytale::Scytale(){

}

// Name: Scytale (Overloaded Constructor)
// Desc: Constructor to build a populated Scytale Cipher
// Preconditions - Pass it the message, isEncrypted, and key (integer)
// Postconditions - Creates a Scytale cipher to be encrypted
Scytale::Scytale(string mess, bool encrypt, int key) : Cipher(mess, encrypt){
    m_key = key; 
}

// Name: Scytale (Destructor)
// Desc: Destructor - Anything specific part of Scytale to delete?
// Preconditions - ~Scytale exists
// Postconditions - Scytale destroyed
Scytale::~Scytale(){
    //Empty
}

// Name: Encrypt
// Desc: Letters are placed on a fence rail based on the number of rails
//       Letters are read from one rail at a time into a single string
// Preconditions - Message exists
// Postconditions - A single encrypted string is stored
void Scytale::Encrypt(){
    string message = GetMessage(); //The cipher message
    string new_message = ""; //The encrypted cipher message
   
    //Fills the extra spaces with #
    while(message.size() % m_key != 0){
        message += PADDING;        
    }
    //Creates the encrypted message
    for(int i = 0; i < m_key; i++){
        for(int j = i; j < int(message.size()); j += m_key){
                new_message += message[j];
        }
    }
    //Set to encrypted message
    SetMessage(new_message);
    ToggleEncrypted();
}

// Name: Decrypt
// Desc: Single encrypted string is pushed back on the rails and reversed
// Preconditions - Message exists
// Postconditions - The decrypted string is stored
void Scytale::Decrypt(){
    string message = GetMessage(); //The cipher message
    int division = ceil(int(message.size())/m_key); // The rows
    string new_message = "";
    int num = 0; //Counter not to exceed the length of cipher message

    //Creates the decrypted message
    vector<char> arr(message.size());
    for(int i = 0; i < division; i++){
        for(int j = i; j < int(message.size()); j+=division){
            if(num < int(message.size())){
                arr[num] = message[j];
                num++;
            }
        }
    }
    //Creates the decrypted message without the padding
    for(int i = 0; i < int(arr.size()); i++){
        if(arr[i] != PADDING){
            new_message += arr[i];
        }
    }
    SetMessage(new_message);
    ToggleEncrypted();
}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Scytale in this case)
string Scytale::ToString(){
    //Specifies the type of cipher (scytale)
    string scy = "(Scytale)";
    return scy;
}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - r, delimiter, isencrypted, delimiter,
//   
string Scytale::FormatOutput(){
    stringstream ss; // Needed for string processing
    string encrypt; // encrypted or not (1/0)
    
    // Output for .txt file (Scytale)
    if(GetIsEncrypted()){
        encrypt = "1";
    }else{
        encrypt = "0";
    }
    ss << "s" << DELIMITER << encrypt << DELIMITER << GetMessage() << ToString() << DELIMITER << m_key << endl;
    return ss.str();
}