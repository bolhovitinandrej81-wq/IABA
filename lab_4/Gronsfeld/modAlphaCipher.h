/**
 * @file modAlphaCipher.h
 * @author Ваше Имя
 * @version 1.0
 * @date 04.12.2026
 * @copyright Ваша организация
 * @brief Заголовочный файл для класса шифрования методом Гронсфельда
 * @warning Реализация только для русского языка
 */

#pragma once
#include <map>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <stdexcept>

/**
 * @brief Класс исключения для ошибок шифрования
 */
class cipher_error : public std::runtime_error {
public:
    /**
     * @brief Конструктор исключения
     * @param what_arg Описание ошибки
     */
    explicit cipher_error(const std::string& what_arg) : std::runtime_error(what_arg) {}
};

/**
 * @brief Класс для шифрования методом Гронсфельда
 * @details Ключ устанавливается в конструкторе.
 * Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt.
 * @warning Реализация только для русского языка
 */
class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///< русский алфавит
    std::map<wchar_t, int> alphaNum;                               ///< ассоциативный массив "номер по символу"
    std::vector<int> key;                                          ///< ключ
    
    /**
     * @brief Преобразование строки в вектор чисел
     * @param s Исходная строка
     * @return Вектор числовых представлений символов
     */
    std::vector<int> convert(const std::wstring& s);
    
    /**
     * @brief Преобразование вектора чисел в строку
     * @param v Вектор числовых представлений
     * @return Результирующая строка
     */
    std::wstring convert(const std::vector<int>& v);
    
public:
    /**
     * @brief Запрещённый конструктор без параметров
     */
    modAlphaCipher() = delete;
    
    /**
     * @brief Конструктор для установки ключа
     * @param skey Ключ в виде строки
     * @throw cipher_error Если ключ пустой или содержит недопустимые символы
     */
    modAlphaCipher(const std::wstring& skey);
    
    /**
     * @brief Метод для зашифровывания текста
     * @param open_text Открытый текст для шифрования
     * @return Зашифрованная строка
     * @throw cipher_error Если текст пустой
     */
    std::wstring encrypt(const std::wstring& open_text);
    
    /**
     * @brief Метод для расшифровывания текста
     * @param cipher_text Зашифрованный текст
     * @return Расшифрованная строка
     * @throw cipher_error Если текст пустой или содержит недопустимые символы
     */
    std::wstring decrypt(const std::wstring& cipher_text);
};
