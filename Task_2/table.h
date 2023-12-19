#pragma once
#include <vector>
#include <string>
#include <map>
#include <codecvt>
#include <iostream>
#include <locale>

class Table
{
private:
    std::wstring numAlpha =
        L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит по порядку
    std::wstring lnumAlpha =
        L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"; //алфавит по порядку
    std::map <int, std::wstring> subNum; //ассоциативный массив "субстрока по номеру"
    std::map <int, std::wstring> resubNum; //ассоциативный массив "субстрока по номеру"
    uint key; //ключ
public:
    std::wstring toValidtext(const std::wstring& s);// метод валидации текста
    Table()=delete; //запретим конструктор без параметров
    Table(const int skey); //конструктор для установки ключа
    std::wstring encrypt(const std::wstring& open_text); //зашифрование
    std::wstring decrypt(const std::wstring& cipher_text);//расшифрование
    bool is_rus(wchar_t wc); //проверка символа, принадлежит ли он русскому алфавиту
    int is_low_rus(wchar_t wch); //проверка символа, принадлежит ли он к строчным буквам
}; 

class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
