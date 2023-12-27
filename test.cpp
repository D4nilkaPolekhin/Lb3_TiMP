#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include "includer.h"
#include <locale>
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

SUITE(modAlpha_test)
{
    SUITE(KeyTest) {
        TEST(ValidKey) {
            std::wstring res =modAlphaCipher(L"АБВ").encrypt(L"ААААА") ;
            std::wstring temp = L"АБВАБ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
            
        }
     TEST(LongKey) {
            std::wstring res = modAlphaCipher(L"АБВГДЕЁЖЗИ").encrypt(L"ААААА");
            std::wstring temp = L"АБВГД";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST(LowCaseKey) {
            std::wstring res = modAlphaCipher(L"бвг").encrypt(L"ААААА");
            std::wstring temp = L"БВГБВ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST(DigitsInKey) {
            CHECK_THROW(modAlphaCipher cp(L"Б1"),cipher_error);
        }
        TEST(PunctuationInKey) {
            CHECK_THROW(modAlphaCipher cp(L"Б,Г"),cipher_error);
        }
        TEST(WhitespaceInKey) {
            CHECK_THROW(modAlphaCipher cp(L"Б Г"),cipher_error);
        }
        TEST(EmptyKey) {
            CHECK_THROW(modAlphaCipher cp(L""),cipher_error);
        }
        TEST(WeakKey) {
            CHECK_THROW(modAlphaCipher(L"ААА").encrypt(L"ДЛИННЫЙТЕКСТДЛЯПРОВЕРКИ"),cipher_error);
        }
        TEST(KeyFromWrongAlphabet) {
            CHECK_THROW(modAlphaCipher cp(L"ABC"),cipher_error);
        }
    }
    SUITE(EncryptTest) {
        TEST_FIXTURE(KeyB_fixture, UpCaseString) {
            std::wstring res = p->encrypt(L"ПОЕШЬЭТИХФРАНЦУЗСКИХБУЛОК");
            std::wstring temp = L"СРЖЪЮЯФКЧЦТВПШХЙУМКЧГХНРМ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, LowCaseString) {
            std::wstring res = p->encrypt(L"поешьэтихфранцузскихбулок") ;
            std::wstring temp = L"СРЖЪЮЯФКЧЦТВПШХЙУМКЧГХНРМ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
            std::wstring res = p->encrypt(L"поешь этих французских булок !!!") ;
            std::wstring temp = L"СРЖЪЮЯФКЧЦТВПШХЙУМКЧГХНРМ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
            std::wstring res = p->encrypt(L"С новым 2024 годом!");
            std::wstring temp = L"УПРДЭОЕРЁРО";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, EmptyString) {
            CHECK_THROW(p->encrypt(L""),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
            CHECK_THROW(p->encrypt(L"1234+8765=9999"),cipher_error);
        }
        TEST(MaxShiftKey) {
            std::wstring res = modAlphaCipher(L"Я").encrypt(L"ПОЕШЬЭТИХФРАНЦУЗСКИХБУЛОК");
            std::wstring temp = L"ОНДЧЫЬСЗФУПЯМХТЖРЙЗФАТКНЙ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture,EnglishString) {
            CHECK_THROW(p->encrypt(L"EATHTHOSEFRENCHPIES"),cipher_error);
        }
    }
    SUITE(DecryptText) {
        TEST_FIXTURE(KeyB_fixture, UpCaseString) {
            std::wstring res = p->decrypt(L"СРЖЪЮЯФКЧЦТВПШХЙУМКЧГХНРМ") ;
            std::wstring temp = L"ПОЕШЬЭТИХФРАНЦУЗСКИХБУЛОК";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, LowCaseString) {
            CHECK_THROW(p->decrypt(L"срЖЪЮЯФКЧЦТВПШХЙУМКЧГХНРМ"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
            CHECK_THROW(p->decrypt(L"СРЖЪЮ ЯФКЧ ЦТВПШХЙУМКЧ ГХНРМ"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, DigitsString) {
            CHECK_THROW(p->decrypt(L"УПРДЭО2024ЕРЁРО"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, PunctString) {
            CHECK_THROW(p->decrypt(L"СТКДЖФ,ВПЁТЖЛ"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, EmptyString) {
            CHECK_THROW(p->decrypt(L""),cipher_error);
        }
        TEST(MaxShiftKey) {
            std::wstring res = modAlphaCipher(L"Я").decrypt(L"ОНДЧЫЬСЗФУПЯМХТЖРЙЗФАТКНЙ") ;
            std::wstring temp = L"ПОЕШЬЭТИХФРАНЦУЗСКИХБУЛОК";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture,EnglishString) {
            CHECK_THROW(p->encrypt(L"ASDGFDHRTWSFD"),cipher_error);
        }
    }
}
SUITE(table_cipher_test){
    SUITE(initialization_test){
        TEST(right_key){
            std::string test = "helloworld";
            std::string test2="";
            CHECK_THROW(table_cipher t (test,4,test2),table_error);
        }
        TEST(long_key){
            std::string test = "helloworld";
            std::string test2="";
            CHECK_THROW(table_cipher t (test,12,test2),table_error);
        }
        TEST(short_key){
            std::string test = "helloworld";
            std::string test2="";
            CHECK_THROW(table_cipher t (test,1,test2),table_error);
        }
        TEST(text_with_spaces){
            std::string test = "hello world";
            std::string test2="";
            CHECK_THROW(table_cipher t (test,4,test2),table_error);
        }
        TEST(text_with_spsymbols){
            std::string test = "helloworld!@#$%";
            std::string test2="";
            CHECK_THROW(table_cipher t (test,4,test2),table_error);
        }
        TEST(text_with_numbers){
            std::string test = "helloworld1234";
            std::string test2="";
            CHECK_THROW(table_cipher t (test,4,test2),table_error);
        }
    }
    SUITE(encrypt_test){
        TEST(upcase_text){
            std::string test = "HELLOWORLD";
            std::string test2="";
            table_cipher t (test,4,test2);
            CHECK_EQUAL("LRLOEWDHOL",t.encrypt());
        }
        TEST(lowcase_text){
            std::string test = "helloworld";
            std::string test2="";
            table_cipher t (test,4,test2);
            CHECK_EQUAL("LRLOEWDHOL",t.encrypt());
        }
        TEST(text_with_spaces){
            std::string test = "hello world";
            std::string test2="";
            table_cipher t (test,4,test2);
            CHECK_EQUAL("LRLOEWDHOL",t.encrypt());
        }
        TEST(non_int_key){
            std::string test = "HELLOWORLD";
            std::string test2="";
            table_cipher t (test,4.9,test2);
            CHECK_EQUAL("LRLOEWDHOL",t.encrypt());
        }
    }
    SUITE(decrypt_test){
        TEST(upcase_text){
            std::string test = "LRLOEWDHOL";
            std::string test2=" ";
            table_cipher t (test,4,test2);
            CHECK_EQUAL("HELLOWORLD",t.decrypt());
        }
        TEST(lowcase_text){
            std::string test = "lrloewdhol";
            std::string test2=" ";
            table_cipher t (test,4,test2);
            CHECK_EQUAL("HELLOWORLD",t.decrypt());
        }
        TEST(text_with_spaces){
            std::string test = "LRLOE WDHOL";
            std::string test2=" ";
            table_cipher t (test,4,test2);
            CHECK_EQUAL("HELLOWORLD",t.decrypt());
        }
        TEST(non_int_key){
            std::string test = "LRLOEWDHOL";
            std::string test2=" ";
            table_cipher t (test,4.9,test2);
            CHECK_EQUAL("HELLOWORLD",t.decrypt());
        }
    }
}
int main(){
    std::locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    return UnitTest::RunAllTests();
}
