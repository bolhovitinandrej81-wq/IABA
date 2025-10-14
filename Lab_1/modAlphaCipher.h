#ifndef MODALPHACIPHER_H
#define MODALPHACIPHER_H

#include <string>
using namespace std;

class modAlphaCipher
{
private:
    string key;
public:
    modAlphaCipher(const string& skey);
    string encrypt(const string& text);
    string decrypt(const string& text);
};

#endif
