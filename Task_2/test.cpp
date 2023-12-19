#include <UnitTest++/UnitTest++.h>
#include <string>
#include "table.h"
#include <locale>
#include <codecvt>
struct Key2_fixture {
    Table * p;
    Key2_fixture()
    {
        p = new Table(2);
    }
    ~Key2_fixture()
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
        std::wstring wres=Table(2).encrypt(L"КУРТКА");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("УТАКРК", res);
    }
    TEST(NegativeKey) {
        CHECK_THROW(Table tb(-1), cipher_error);
    }
    TEST(SencelessKey) {
        CHECK_THROW(Table tb(1), cipher_error);
    }
    TEST(BigKey) {
        std::wstring wres=Table(100).encrypt(L"КУРТКА");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("РАУККТ", res);
    }
    TEST(AwkwardKey) {
        std::wstring wres=Table(4).encrypt(L"КУРТКА");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("Т*Р*УАКК", res);
    }

}
SUITE(encrypt)
{
    TEST_FIXTURE(Key2_fixture, UpperString) {
        std::wstring wres=p->encrypt(L"АТТЕСТАЦИЯ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ТЕТЦЯАТСАИ", res);
    }
    TEST_FIXTURE(Key2_fixture, LowerString) {
        std::wstring wres=p->encrypt(L"аттестация");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ТЕТЦЯАТСАИ", res);
    }
    TEST_FIXTURE(Key2_fixture, WhitespaceInString) {
        CHECK_THROW(p->encrypt(L"А ТТЕСТ АЦИЯ"), cipher_error);
    }
    TEST_FIXTURE(Key2_fixture, PunctuationInString) {
        CHECK_THROW(p->encrypt(L"АТТЕ.СТ,!!АЦИЯ"), cipher_error);
    }
    TEST_FIXTURE(Key2_fixture, DigitsInString) {
        CHECK_THROW(p->encrypt(L"АТТЕСТ45АЦИЯ"), cipher_error);
    }
    TEST_FIXTURE(Key2_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
    }
    TEST(MaxStep) {
        std::wstring wres=Table(9).encrypt(L"АТТЕСТАЦИЯ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("И*Ц*А*Т*С*Е*Т*Т*АЯ", res);
    }
} 
SUITE(decrypt)
{
    TEST_FIXTURE(Key2_fixture, UpperString) {
        std::wstring wres=p->decrypt(L"ТЕТЦЯАТСАИ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("АТТЕСТАЦИЯ", res);
    }
    TEST_FIXTURE(Key2_fixture, LowerString) {
        std::wstring wres=p->decrypt(L"тетцяатсаи");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("АТТЕСТАЦИЯ", res);
    }
    TEST_FIXTURE(Key2_fixture, WhitespaceInString) {
        CHECK_THROW(p->decrypt(L"ТЕТ ЦЯАТС АИ"), cipher_error);
    }
    TEST_FIXTURE(Key2_fixture, PunctuationInString) {
        CHECK_THROW(p->decrypt(L"ТЕТЦ.№%ЯАТСА!И"), cipher_error);
    }
    TEST_FIXTURE(Key2_fixture, DigitsInString) {
        CHECK_THROW(p->decrypt(L"ТЕТЦЯАТ362САИ"), cipher_error);
    } 
    TEST_FIXTURE(Key2_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
    }
    TEST(MaxStep) {
        std::wstring wres=Table(9).decrypt(L"И*Ц*А*Т*С*Е*Т*Т*АЯ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("АТТЕСТАЦИЯ", res);
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
