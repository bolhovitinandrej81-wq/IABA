/**
 * @file modAlphaCipher.cpp
 * @author Ваше Имя
 * @version 1.0
 * @date 04.12.2026
 * @brief Файл реализации класса modAlphaCipher
 */

#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <cwctype>
#include <algorithm>

using namespace std;

modAlphaCipher::modAlphaCipher(const wstring& skey)
{
    // 3.1.1 Пустой ключ
    if(skey.empty())
        throw cipher_error("Пустой ключ");

    // 3.1.2 Неправильный ключ
    for(auto c : skey) {
        if((c < L'А' || c > L'Я') && c != L'Ё') {
            throw cipher_error("Неправильный ключ: содержит недопустимые символы");
        }
    }

    // Инициализация алфавита
    for(unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(skey);
}

/**
 * @brief Преобразование строки в вектор чисел
 * @param s Исходная строка
 * @return Вектор числовых представлений
 */
vector<int> modAlphaCipher::convert(const wstring& s)
{
    vector<int> result;
    for(auto c : s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

/**
 * @brief Преобразование вектора чисел в строку
 * @param v Вектор числовых представлений
 * @return Результирующая строка
 */
wstring modAlphaCipher::convert(const vector<int>& v)
{
    wstring result;
    for(auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

/**
 * @brief Шифрование открытого текста
 * @param open_text Текст для шифрования
 * @return Зашифрованная строка
 */
wstring modAlphaCipher::encrypt(const wstring& open_text)
{
    // 3.1.3 Отсутствие текста
    if(open_text.empty())
        throw cipher_error("Отсутствует текст");

    vector<int> work = convert(open_text);
    
    // Основной алгоритм шифрования
    for(unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

/**
 * @brief Расшифрование текста
 * @param cipher_text Зашифрованный текст
 * @return Расшифрованная строка
 */
wstring modAlphaCipher::decrypt(const wstring& cipher_text)
{
    // 3.1.4 Пустой текст
    if(cipher_text.empty())
        throw cipher_error("Пустой текст");

    // 3.1.5 Неправильно зашифрованный текст
    for(auto c : cipher_text) {
        if((c < L'А' || c > L'Я') && c != L'Ё') {
            throw cipher_error("Неправильно зашифрованный текст: содержит недопустимые символы");
        }
    }

    vector<int> work = convert(cipher_text);
    
    // Алгоритм расшифрования
    for(unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
