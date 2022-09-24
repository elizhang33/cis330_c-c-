#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation
struct Cipher::CipherCheshire {
    string cipher_alpha;
}; 

struct CCipher::CCipherCheshire : CipherCheshire{
    string cipher_alpha;
    int rot;
};

CCipher::CCipher() : Cipher()
{	
	cmile = new struct CCipherCheshire;
   	cmile->rot = 0;
   	rotate_string(smile->cipher_alpha, cmile->rot);
}

CCipher::CCipher(int offset): Cipher() {
    cmile = new struct CCipherCheshire;
    cmile->rot = offset;
    if (cmile->rot >0) {
    	rotate_string(smile->cipher_alpha, cmile->rot);
    }
    else {
    	cerr << "Error: Caesar cipher is less than 0" << endl;
    }
}

CCipher::~CCipher()
{
	delete cmile;
}

// -------------------------------------------------------


// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
    // TODO: You will likely need this function. Implement it.
    rot = (rot % 26);
    //rotate(in_str.begin(), in_str.begin() + rot, in_str.end());
    reverse(in_str.begin(), in_str.end());
    reverse(in_str.begin(), in_str.begin() + (26-rot));
    reverse(in_str.begin() + (26-rot), in_str.end());
    
}






