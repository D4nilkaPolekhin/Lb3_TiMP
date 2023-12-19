#include <UnitTest++/UnitTest++.h>
#include <string>
#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher(L"В");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};
//setup converter
using convert_type = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_type, wchar_t> converter;

SUITE(Costructor)
{

    TEST(NormalKey) {
        std::wstring wres=modAlphaCipher(L"БВГ").encrypt(L"ААААА");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("БВГБВ", res);
    }
    TEST(LowerlKey) {
        std::wstring wres=modAlphaCipher(L"бвг").encrypt(L"ААААА");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("БВГБВ", res);
    }
    TEST(LongKey) {
        std::wstring wres=modAlphaCipher(L"БВГДЕЁЖЗ").encrypt(L"ААААА");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("БВГДЕ", res);
    }

    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp(L"Б1"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp(L"Б,В"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp(L"Б В"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(L""),cipher_error);
    }
}
SUITE(encrypt)
{
    TEST_FIXTURE(KeyB_fixture, UpperString) {
        std::wstring wres=p->encrypt(L"ВЕСЕННИЙЛЕС");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ДЖУЖППКЛНЖУ", res);
    }
    TEST_FIXTURE(KeyB_fixture, LowerString) {
        std::wstring wres=p->encrypt(L"Весеннийлес");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ДЖУЖППКЛНЖУ", res);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceInString) {
        CHECK_THROW(p->encrypt(L"ВЕСЕННИЙ ЛЕС"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctuationInString) {
        CHECK_THROW(p->encrypt(L"ВЕСЕ!!НН.,ИЙЛЕС!!"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsInString) {
        CHECK_THROW(p->encrypt(L"ВЕСЕННИЙ456ЛЕС"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
    }
    TEST(MaxStep) {
        std::wstring wres=modAlphaCipher(L"Я").encrypt(L"АРБУЗ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ЯПАТЖ", res);
    }
}
SUITE(decrypt)
{
    TEST_FIXTURE(KeyB_fixture, UpperString) {
        std::wstring wres=p->decrypt(L"ДЖУЖППКЛНЖУ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ВЕСЕННИЙЛЕС", res);
    }
    TEST_FIXTURE(KeyB_fixture, LowerString) {
        std::wstring wres=p->decrypt(L"ДжУЖппКЛнЖу");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ВЕСЕННИЙЛЕС", res);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceInString) {
        CHECK_THROW(p->decrypt(L"Д ЖУЖ ППК ЛНЖУ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctuationInString) {
        CHECK_THROW(p->decrypt(L"ДЖУ,ЖП!!ПКЛН.ЖУ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsInString) {
        CHECK_THROW(p->decrypt(L"ДЖ5УЖ34ПП1КЛНЖУ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, MaxStep) {
        std::wstring wres=modAlphaCipher(L"Я").decrypt(L"ЯПАТЖ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("АРБУЗ", res);
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}