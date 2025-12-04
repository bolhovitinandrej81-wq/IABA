/**
 * @file TableRouteCipher.h
 * @author Ваше Имя
 * @version 1.0
 * @date 04.12.2026
 * @brief Заголовочный файл для табличного маршрутного шифра
 * @warning Реализация только для английского языка
 */

#pragma once
#include <string>

using namespace std;

/**
 * @brief Класс исключения для ошибок шифрования
 */
class cipher_error : public std::exception {
private:
    string message; ///< Сообщение об ошибке
public:
    /**
     * @brief Конструктор исключения
     * @param msg Сообщение об ошибке
     */
    explicit cipher_error(const string& msg) : message(msg) {}
    
    /**
     * @brief Получение сообщения об ошибке
     * @return Строка с описанием ошибки
     */
    const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @brief Класс для шифрования табличным маршрутным методом
 * @details Шифрование осуществляется путём записи текста в таблицу
 *          по строкам и чтения по столбцам.
 * @warning Реализация только для английского языка
 */
class TableRouteCipher {
private:
    int key; ///< Количество столбцов (ключ шифрования)
    
public:
    /**
     * @brief Запрещённый конструктор без параметров
     */
    TableRouteCipher() = delete;
    
    /**
     * @brief Конструктор с установкой ключа
     * @param skey Количество столбцов
     * @throw cipher_error Если ключ некорректен
     */
    TableRouteCipher(int skey);
    
    /**
     * @brief Метод для шифрования текста
     * @param text Текст для шифрования
     * @return Зашифрованная строка
     * @throw cipher_error При ошибках валидации
     */
    string encrypt(string &text);
    
    /**
     * @brief Метод для расшифрования текста
     * @param text Текст для расшифрования
     * @return Расшифрованная строка
     * @throw cipher_error При ошибках валидации
     */
    string decrypt(string &text);
};
