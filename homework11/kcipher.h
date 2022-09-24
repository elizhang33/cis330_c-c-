#ifndef KCIPHER_H_
#define KCIPHER_H_
#include "cipher.h"
#include "ccipher.h"

using namespace std;

const unsigned int MAX_LENGTH = 100;

/* A class that implements a
   Running key cipher class. It 
   inherts class Cipher */
// TODO: Implement this function
class KCipher : public Cipher {
        struct KCipherCheshire;
        KCipherCheshire *kmile;

public:
        KCipher();
        KCipher(vector <string> cont);
        ~KCipher();
        string encrypt(string raw);
        string decrypt(string enc);
};


//void add_key(string text);
//void set_id(unsigned int page);
#endif

