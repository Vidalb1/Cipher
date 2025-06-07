/*****************************************
** File: Ong.cpp
** Project: Cipher
** Author: Vidal Bickersteth
** Date: 4/17/25
**
** This program is the Ong.cpp file of Cipher project
** This file creates an Ong object
** This file encrypts or decrypts your message using Ong cipher
** 
**
**
***********************************************/
#include "Cipher.h"
#include "Ong.h"
#include <istream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;

// Name: Ong (Default Constructor)
  // Desc: Constructor to build an empty Ong Cipher
  // Preconditions - None
  // Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(){

}

// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(string mess, bool encrypt) : Cipher(mess, encrypt){

}

// Name: Ong (Destructor)
// Desc: Destructor - Anything unique to Ong to delete?
// Preconditions - ~Ong exists
// Postconditions - Ong destroyed
Ong::~Ong(){
    
}

// Name: IsVowel (Helper function)
// Desc: Returns true if vowel
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsVowel(char ch){
    char arr[] = {'a', 'e', 'o', 'i', 'u'}; //lower case vowels
    char arr2[] = {'A', 'E', 'O', 'I', 'U'}; //upper case vowels
    
    //If between a and z as well as a vowel letter, then it's a vowel
    if(ch >= 'a' && ch <= 'z'){
        for(int i = 0; i < 5; i++){
            if(ch == arr[i]){
                return true;
            }
        }
    }

    //If between A and Z as well as a vowel letter, then it's a vowel
    else if(ch >= 'A' && ch <= 'Z'){
        for(int i = 0; i < 5; i++){
            if(ch == arr2[i]){
                return true;
            }else{
                return false;
            }
        }
    }
    return false;
}

 // Name: IsPunct (Helper function)
  // Desc: Returns true if space, or punctuation
  // Preconditions - Message exists
  // Postconditions - Returns true or false as above
bool Ong::IsPunct(char c){
    // If char not a letter, then it must be a punctuation or space
    if(!(c >= 'a' && c <= 'z')){
        if(!(c >= 'A' && c <= 'Z')){
            return true;
        }
    }else if(c == ' '){
        return true;
    }
    return false;
}

// Name: Encrypt
// Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
// If consonant then consonant and ong and dash displayed.
// Preconditions - Message exists
// Postconditions - Encrypts as above
void Ong::Encrypt(){
    string message = GetMessage(); //The cipher message
    string new_message = ""; //The encrypted cipher message
    char letter; //The letter 

    //If consonant, then ong and dash gets displayed for encrypted
    for(int i = 0; i < int(message.length()); i++){
        letter = message[i];
        if(!IsVowel(letter) && !IsPunct(letter)){
            new_message += letter;
            new_message += "ong-";
        }
    //If space, then it gets ignored
        else if(!IsVowel(letter) && IsPunct(letter)){
            new_message += letter;
    //If neither, then a dash is added
        }else{
            new_message += letter;
            new_message += "-";
        }
    }
    //Set to encrypted message
    SetMessage(new_message);
    ToggleEncrypted();
}

// Name: Decrypt
// Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
// Double check words like "wrong" so that they work correctly!
// Preconditions - Message exists
// Postconditions - Original message is displayed
void Ong::Decrypt(){
    string message = GetMessage(); //The cipher message
    stringstream ss(message); //To process through the string
    string part; //parts of the message
    size_t index = 0; // the index
    string new_string = ""; // the new message
    vector<string> mess; // The vector

    //Removes all ongs and dashes if identified
    while(getline(ss, part, '-')){
        index = part.find(ong);
        while(index != string::npos){
            part.erase(index,3);
            index = part.find(ong);
        }
        mess.push_back(part);
    }

    //Creates the decrypted message
    for(int i = 0; i < int(mess.size()); i++){
        new_string += mess.at(i);
    }
    SetMessage(new_string);
    ToggleEncrypted();        
}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Ong in this case)
string Ong::ToString(){
    //Specifies the type of cipher (ong)
    string o = "(Ong)";
    return o;
}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - o, delimiter, isencrypted, delimiter,
//                  message, delimiter, blank are output
string Ong::FormatOutput(){
    stringstream ss; // Needed for string processing
    string encrypt; // encrypted or not (1/0)

    // Output for .txt file (Ong)
    if(GetIsEncrypted()){
        encrypt = "1";
    }else{
        encrypt = "0";
    }
    ss << "o" << DELIMITER << encrypt << DELIMITER << GetMessage() << ToString() << DELIMITER << endl;
    return ss.str();
}

