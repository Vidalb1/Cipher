/*****************************************
** File: Atbash.cpp
** Project: Cipher
** Author: Vidal Bickersteth
** Date: 4/17/25
**
** This program is the Atbash.cpp file of Cipher.
** This file creates an Atbash object.
** This file encrypts or decrypts your message using Atbash cipher.
**
**
***********************************************/

#include "Cipher.h"
#include "Atbash.h"
#include <string>
#include <vector>
using namespace std;

// Name: Atbash (Default Constructor)
// Desc: Constructor to build an empty Atbash Cipher
// Preconditions - None
// Postconditions - Creates a Atbash cipher to be encrypted
Atbash::Atbash(){

}

// Name: Atbash (Overloaded Constructor)
// Desc: Constructor to build a populated Atbash Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates a Atbash cipher to be encrypted
Atbash::Atbash(string mess, bool encry) : Cipher(mess, encry){
    
}

// Name: Atbash (Destructor)
// Desc: Destructor - Anything specific to Atbash to delete?
// Preconditions - ~Atbash exists
// Postconditions - Atbash destroyed
Atbash:: ~Atbash(){
    
}

// Name: Encrypt
// Desc: Reverses the alphabet (A ↔ Z, B ↔ Y, etc.)
// Preconditions - Message exists
// Postconditions - Reverses the characters. Ignores punctuation.
void Atbash::Encrypt(){
    string message = GetMessage(); //The cipher message
    string new_message = ""; // The new message
    char reverse; //The reversed character

    //Creates the encrypted message only for letters
    for(int i = 0; i < int(message.length()); i++){
        char letter = message[i];
        if(letter >= 'A' && letter <= 'Z'){
            reverse = 'Z' - (letter - 'A');
            new_message += reverse;
        }
        else if(letter >= 'a' && letter <= 'z'){
            reverse = 'z' - (letter - 'a');
            new_message += reverse;
        }else{
            new_message += letter;
        }
    }
    //Sets to new message
    SetMessage(new_message);
    ToggleEncrypted();
}

// Name: Decrypt
// Desc: Reverses the alphabet (A ↔ Z, B ↔ Y, etc.)
// Preconditions - Message exists
// Postconditions - Reverses the characters. Ignores punctuation.
void Atbash::Decrypt(){
    //Reverses the characters to decrypt
    Encrypt();
    ToggleEncrypted();
}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Atbash in this case)
string Atbash::ToString(){
    //Specifies the type of cipher (Atbash)
    string s = "(Atbash)";
    return s;
}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
//                  message, delimiter are returned for output
string Atbash::FormatOutput(){
    stringstream ss; // Needed for string processing
    string encrypt; // encrypted or not (1/0)

    // Output for .txt file (AtBash)
    if(GetIsEncrypted()){
        encrypt = "0";
    }else{
        encrypt = "1";
    }
    ss << "a" << DELIMITER << encrypt << DELIMITER << GetMessage() << ToString() << endl;
    return ss.str();
}

