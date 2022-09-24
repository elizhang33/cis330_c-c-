#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include "vcipher.h"


// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

struct KCipher::KCipherCheshire 
{
		vector<string> keys;
		unsigned int page;
};

VCipher::VCipher() : KCipher()
{

}

VCipher::VCipher(string key) : KCipher() {
	string new_key;
	while (new_key.size() < MAX_LENGTH) {
		new_key += key;
	}
	kmile->keys[kmile->page] = new_key;
}

VCipher::~VCipher() {

}

