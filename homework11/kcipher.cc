#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"


/* Helper function definitions
*/
string get_key(string key) {
        string res;
        for (unsigned int i = 0; i < key.size(); i++) {
                if (key[i] != ' ') {
                        res += key[i];
                }
       return res;
}
void add_key(string text);
void set_id(unsigned int page);

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

struct KCipher::KCipherCheshire {
        vector<string> keys;
        unsigned int page;
};

KCipher::KCipher()
{
        kmile = new struct KCipherCheshire;
        kmile->page = 0;
        string keys_cont;
        for (unsigned int i = 0; i < MAX_LENGTH; i++) {
                keys_cont += 'a';
        }
        add_key(keys_cont);
        set_id(0);
}


KCipher::KCipher(string cont)
{
        kmile = new struct KCipherCheshire;
        kmile->page = 0;
        add_key(cont);
}

KCipher::~KCipher()
{
        delete kmile;
}

string KCipher::encrypt(string raw)
{ 		
		string retStr;
		cout << "Encrypting..";
        string plain_alpha = "abcdefghijklmnopqrstuvwxyz";
        string key = kmile->keys[kmile->page];
        string res = get_key(pages);

        unsigned int i = 0;
        unsigned int j = 0;
        char id = raw[i];
        char key_id = res[j];
        for (i = 0; i < raw.size(); i++) {
        		string plain_alpha_copy;
        		if (raw[i] > 'a' && raw[i] < 'z') {
        				plain_alpha = "abcdefghijklmnopqrstuvwxyz";
        				rotate_string(plain_alpha_copy, find_pos(plain_alpha, res[i]));
        				retStr += plain_alpha_copy[find_pos(plain_alpha, raw[i])];
        				res[i] = res[i+1];
        		} else if (raw[i] > 'A' && raw[i] < 'z') {
        				raw[i] = LOWER_CASE(raw[i]);
        				plain_alpha_copy = "abcdefghijklmnopqrstuvwxyz";
        				rotate_string(plain_alpha_copy, find_pos(plain_alpha, res[i]));
        				retStr += UPPER_CASE(plain_alpha_copy[find_pos(plain_alpha, raw[i])]);
        				res[i] = res[i+1];
        		} else if (raw[i] == ' ') {
        				retStr += raw[i];

        		}
        }
        cout << "Done" << endl;
	return retStr;

}

string KCipher::decrypt(string enc)
{ 		
		string retStr;
		cout << "Decrypting..";
        string plain_alpha = "abcdefghijklmnopqrstuvwxyz";
        string key = kmile->keys[kmile->page];
        string res = get_key(pages);

        unsigned int i = 0;
        unsigned int j = 0;
        for (i = 0; i < enc.size(); i++) {
        		string plain_alpha_copy;
        		if (enc[i] > 'a' && enc[i] < 'z') {
        				plain_alpha = "abcdefghijklmnopqrstuvwxyz";
        				rotate_string(plain_alpha_copy, find_pos(plain_alpha, res[i]));
        				int pos;
        				pos = find_pos(plain_alpha_copy, enc[i]);
        				retStr += plain_alpha[pos];
        				res[i] = res[i+1];
        		} else if (enc[i] > 'A' && enc[i] < 'z') {
        				raw[i] = LOWER_CASE(raw[i]);
        				plain_alpha_copy = "abcdefghijklmnopqrstuvwxyz";
        				rotate_string(plain_alpha_copy, find_pos(plain_alpha, res[i]));
        				int pos;
        				pos = find_pos(plain_alpha_copy, enc[i]);
        				retStr += UPPER_CASE(plain_alpha[pos]);
        				res[i] = res[i+1];
        		} else if (enc[i] == ' ') {
        				retStr += enc[i];

        		}
        }
        cout << "Done" << endl;
	return retStr;

}



/* helper function to add content to vectors and find the ciper text according to page number*/
void add_key(string text)
{
        if (text.size() == 0) {
		cout << "Invalid Running key: " << text << endl;
		exit(EXIT_FAILURE);
		}
	
		for (unsigned int i = 0; i < text.size(); i++) {
			if (ispunct(text[i]) || isupper(text[i])) {
				cout << "Invalid Running key: " << text << endl;
				exit(EXIT_FAILURE);
			}
	}

	kmile->keys.push_back(text);
	kmile->page += 1;
}

void set_id(unsigned int page)
{
        if (page > KeySmile->book.size()) {
		cout << "Warning: invalid id: " << page << endl;
		exit(EXIT_FAILURE);
	}
	kmile->page = page;
}

