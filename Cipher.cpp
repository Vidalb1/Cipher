/*****************************************
** File: Cipher.cpp
** Project: Cipher
** Author: Vidal Bickersteth
** Date: 4/17/25
**
** This program is the Cipher.cpp file of Cipher
** This is the Parent class of Cipher.
** This file creates a Cipher object.
** This file is neccessary to create ciphers like atBash,
** Scytale, and Ong.
** Messages are set using this file.
**
**
***********************************************/

#include <iostream>
#include <string>
#include <sstream> 
#include "Cipher.h"    
using namespace std;

// Name: Cipher (Default Constructor)
// Desc - Stores a message and if it is encrypted (or not)
// Preconditions - None
// Postconditions - A message is stored in a Cipher object
Cipher::Cipher(){
    //Default Constructor    
}

// Name: Cipher (Overloaded Constructor)
// Desc - Passed a message and if it is encrypted (or not)
// Preconditions - A message is passed to this constructor, and if it is encrypted
// Postconditions - A message is stored in a Cipher object
Cipher::Cipher(string message, bool isEncrypted){
    //Creates Cipher object
    m_message = message;
    m_isEncrypted = isEncrypted;
}

// Name: ~Cipher (Destructor)
// Desc - Virtual destructor
// Preconditions - A derived class is being deleted
// Postconditions - A base class is deleted
Cipher::~Cipher(){
    
}

//  virtual void Decrypt() = 0;
//  virtual void Encrypt() = 0;
//  Both of them does not get implemented because Cipher is an abstract class

// Name: GetMessage
// Desc - Returns the message
// Preconditions - The message exists
// Postconditions - A message is returned
string Cipher::GetMessage(){
    //returns the message
    return m_message;
}

// Name: GetIsEncrypted
// Desc - Returns isEncrypted (0 is not encrypted and 1 is encrypted)
// Preconditions - The cipher exists
// Postconditions - A bool is returned
bool Cipher::GetIsEncrypted(){
    //returns if encrypted
    return m_isEncrypted; 
}

// Name: SetMessage
// Desc - Updates a message
// Preconditions - The message exists
// Postconditions - A message is updated
void Cipher::SetMessage(string mess){
    // Sets to new message
    m_message = mess;
}

// Name: ToggleEncrypted
// Desc - Turns (true to false) or (false to true)
// Preconditions - The cipher exists
// Postconditions - The m_isEncrypted is toggled
void Cipher::ToggleEncrypted(){
    //Toggles encryption indication
    if(m_isEncrypted){
        m_isEncrypted = false;
    }else{
        m_isEncrypted = true;
    }
}

//   virtual string ToString() = 0;
//   virtual string FormatOutput() = 0;
//   Both of them does not get implemented because Cipher is an abstract class

// Name: Overloaded << Operator
// Desc - Outputs the message
// Preconditions - The object exists
// Postconditions - The message from the object is returned
ostream& operator<<(ostream &output, Cipher &C){
    //The message returned
    return output << C.GetMessage() << endl;
}