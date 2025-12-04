/**
 * @file main.cpp
 * @author Ваше Имя
 * @version 1.0
 * @date 04.12.2026
 * @brief Главный файл программы для табличного маршрутного шифра
 * @details Программа предоставляет интерфейс для шифрования и расшифрования
 *          текста табличным маршрутным методом на английском языке.
 */

#include <iostream>
#include <string>
#include <cctype>
#include "TableRouteCipher.h"

using namespace std;

/**
 * @brief Главная функция программы
 * @return Код завершения программы
 */
int main() {
    string text;
    int key;
    unsigned vibor;
    
    // Выводим информацию о поддерживаемых символах в самом начале
    cout << "--- Шифратор табличным маршрутным шифром ---\n";
    cout << "Поддерживаются только английские буквы и пробелы\n";
    cout << "---\n";
    
    cout << "Введите текст: ";
    getline(cin, text);
    
    cout << "Введите кол-во столбцов: ";
    cin >> key;
    
    try {
        TableRouteCipher shifr(key);
        cout << "Ключ загружен\n";
        
        do {
            cout << "Шифратор готов. Выберите операцию (Выход-0, Шифровка-1, Расшифровка-2): ";
            cin >> vibor;
            
            if (vibor > 2) {
                cout << "Неверная операция!\n";
            } else if (vibor > 0) {
                try {
                    if (vibor == 1) {
                        text = shifr.encrypt(text);
                        cout << "Зашифрованный текст: " << text << endl;
                    } else {
                        text = shifr.decrypt(text);
                        cout << "Расшифрованный текст: " << text << endl;
                    }
                } catch (const cipher_error& e) {
                    cout << "Ошибка при выполнении операции: " << e.what() << endl;
                    break;
                }
            }
        } while (vibor != 0);
        
    } catch (const cipher_error& e) {
        cout << "Ошибка при создании шифратора: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
