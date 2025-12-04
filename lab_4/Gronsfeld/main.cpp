/**
 * @file main.cpp
 * @author Ваше Имя
 * @version 1.0
 * @date 04.12.2026
 * @brief Главный файл программы для шифра Гронсфельда
 * @details Программа предоставляет интерфейс для шифрования и расшифрования
 *          текста методом Гронсфельда на русском языке.
 */

#include "modAlphaCipher.h"
#include <iostream>
#include <locale>
#include <codecvt>
#include <algorithm>

using namespace std;

/**
 * @brief Удаление пробелов из строки
 * @param s Исходная строка
 * @return Строка без пробелов
 */
wstring remove_spaces(const wstring& s) {
    wstring result;
    for(auto c : s) {
        if(c != L' ') {
            result += c;
        }
    }
    return result;
}

/**
 * @brief Проверка валидности русского текста
 * @param s Проверяемая строка
 * @return true если текст содержит только русские буквы и пробелы
 */
bool is_valid_russian_text(const wstring& s) {
    for(auto c : s) {
        if(c == L' ') continue;
        if((c < L'А' || c > L'Я') && c != L'Ё') {
            return false;
        }
    }
    return true;
}

/**
 * @brief Проверка валидности ключа
 * @param s Ключ для проверки
 * @return true если ключ содержит только русские буквы
 */
bool is_valid_key(const wstring& s) {
    for(auto c : s) {
        if((c < L'А' || c > L'Я') && c != L'Ё') {
            return false;
        }
    }
    return true;
}

/**
 * @brief Преобразование строки к верхнему регистру (русский)
 * @param s Исходная строка
 * @return Строка в верхнем регистре
 */
wstring to_upper_rus(const wstring& s) {
    wstring result = s;
    for (auto& c : result) {
        if (c >= L'а' && c <= L'я') {
            c = c - L'а' + L'А';
        } 
        else if (c == L'ё') {
            c = L'Ё';
        }
    }
    return result;
}

/**
 * @brief Преобразование narrow string в wide string
 * @param narrow_str Строка в кодировке UTF-8
 * @return Строка в формате wstring
 */
wstring to_wide(const string& narrow_str) {
    try {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(narrow_str);
    } catch (const exception& e) {
        return L"";
    }
}

/**
 * @brief Преобразование wide string в narrow string
 * @param wide_str Строка в формате wstring
 * @return Строка в кодировке UTF-8
 */
string to_narrow(const wstring& wide_str) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wide_str);
}

/**
 * @brief Главная функция программы
 * @return Код завершения программы
 */
int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    string key_input;
    string text_input;
    unsigned op;
    
    cout << "Шифр готов. Введите ключ: ";
    getline(cin, key_input);
    
    wstring key = to_wide(key_input);
    key = to_upper_rus(key);
    
    wstring clean_key = remove_spaces(key);
    
    try {
        if(!is_valid_key(clean_key)) {
            throw cipher_error("Неправильный ключ: содержит недопустимые символы");
        }
        
        modAlphaCipher cipher(clean_key);
        cout << "Ключ загружен\n";
        
        do {
            cout << "Шифр готов. Выберите операцию (0-выход, 1-шифрование, 2-расшифрование): ";
            cin >> op;
            
            if(op > 2) {
                cout << "Неверная операция\n";
            } else if(op > 0) {
                cout << "Введите текст: ";
                cin.ignore();
                getline(cin, text_input);
                
                wstring text = to_wide(text_input);
                if(text.empty() && !text_input.empty()) {
                    cout << "Ошибка кодировки\n";
                    continue;
                }
                
                text = to_upper_rus(text);
                
                try {
                    if(op == 1) {
                        if(!is_valid_russian_text(text)) {
                            cout << "Ошибка: Текст содержит недопустимые символы\n";
                            continue;
                        }
                        wstring text_no_spaces = remove_spaces(text);
                        wstring encrypted = cipher.encrypt(text_no_spaces);
                        cout << "Зашифрованный текст: " << to_narrow(encrypted) << endl;
                    } else {
                        wstring text_no_spaces = remove_spaces(text);
                        wstring decrypted = cipher.decrypt(text_no_spaces);
                        cout << "Расшифрованный текст: " << to_narrow(decrypted) << endl;
                    }
                } catch (const cipher_error& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
            }
        } while(op != 0);
        
    } catch (const cipher_error& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cerr << "Неизвестная ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
