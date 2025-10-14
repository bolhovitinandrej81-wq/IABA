#include "modAlphaCipher.h"
#include <algorithm>

modAlphaCipher::modAlphaCipher(const string& skey)
{
    key = skey;
}

string modAlphaCipher::encrypt(const string& text)
{
    string result = text;
    // Простая заглушка - просто возвращаем текст
    // Замените на реальный алгоритм шифрования
    return result;
}

string modAlphaCipher::decrypt(const string& text)
{
    string result = text;
    // Простая заглушка - просто возвращаем текст
    // Замените на реальный алгоритм дешифрования
    return result;
}
