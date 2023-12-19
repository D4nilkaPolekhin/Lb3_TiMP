#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <cwctype>
class modAlphaCipher
{
private:
    std::wstring numAlpha =
        L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит по порядку
    std::wstring lnumAlpha =
        L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"; //алфавит по порядку
    std::map <char,int> alphaNum; //ассоциативный массив "номер по символу"
    std::vector <int> key; //ключ
    std::vector<int> convert(const std::wstring& s); //преобразование строка-вектор
    std::wstring convert(const std::vector<int>& v); //преобразование вектор-строка
    //std::wstring getValidKey(const std::wstring & s); //метод проверки ключа
    std::wstring toValidtext(const std::wstring& s, std::string obj); //метод проверки строки
    bool is_rus(wchar_t wc); //проверка символа, принадлежит ли он русскому алфавиту
    int is_low_rus(wchar_t wch); //проверка символа, принадлежит ли он к строчным буквам
public:
    modAlphaCipher()=delete; //запретим конструктор без параметров
    modAlphaCipher(const std::wstring& skey) //конструктор для установки ключа
    {
        for (unsigned i=0; i<numAlpha.size(); i++) {
            alphaNum[numAlpha[i]]=i;
        }
        key = convert(toValidtext(skey, "key"));
    }
    std::wstring encrypt(const std::wstring& open_text); //зашифрование
    std::wstring decrypt(const std::wstring& cipher_text);//расшифрование
};
class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};