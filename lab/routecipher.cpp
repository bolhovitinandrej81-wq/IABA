#include "routecipher.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace std;

RouteCipher::RouteCipher(int skey) { 
    if (skey <= 0) {
        throw invalid_argument("Ключ должен быть положительным числом");
    }
    key = skey; 
}

string RouteCipher::encrypt(const string& text) {
    if (text.empty()) {
        throw invalid_argument("Текст не может быть пустым");
    }
    
    // Удаляем пробелы для шифрования
    string clean_text;
    for (char c : text) {
        if (c != ' ') {
            clean_text += c;
        }
    }
    
    int length = clean_text.length();
    int rows = (length + key - 1) / key; // Округляем вверх
    
    // Создаем таблицу и заполняем по строкам слева направо
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (index < length) {
                table[i][j] = clean_text[index++];
            }
        }
    }
    
    // Читаем по столбцам сверху вниз
    string result;
    for (int j = 0; j < key; j++) {
        for (int i = 0; i < rows; i++) {
            if (table[i][j] != ' ') {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

string RouteCipher::decrypt(const string& text) {
    if (text.empty()) {
        throw invalid_argument("Текст не может быть пустым");
    }
    
    // Удаляем пробелы из зашифрованного текста
    string clean_text;
    for (char c : text) {
        if (c != ' ') {
            clean_text += c;
        }
    }
    
    int length = clean_text.length();
    int rows = (length + key - 1) / key; // Округляем вверх
    
    // Вычисляем количество полных столбцов (столбцов с rows символов)
    int full_cols = length % key;
    if (full_cols == 0) {
        full_cols = key; // Все столбцы полные
    }
    
    // Создаем пустую таблицу
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    // Заполняем таблицу по столбцам сверху вниз
    int index = 0;
    for (int j = 0; j < key; j++) {
        // Определяем сколько символов в этом столбце
        int symbols_in_col = (j < full_cols) ? rows : (rows - 1);
        
        for (int i = 0; i < symbols_in_col; i++) {
            if (index < length) {
                table[i][j] = clean_text[index++];
            }
        }
    }
    
    // Читаем таблицу по строкам слева направо
    string result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (table[i][j] != ' ') {
                result += table[i][j];
            }
        }
    }
    
    return result;
}
