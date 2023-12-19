#include "table.h"

Table::Table(const int skey)
{
    if(skey<=0){
        throw cipher_error("Bad key");
    }
    if(skey==1)
        throw cipher_error("Senceless key");
    key = skey;
}

std::wstring Table::toValidtext(const std::wstring& s)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    if (s.empty())
        throw cipher_error("Empty text");
    std::wstring tmp(s);
    std::string st = converter.to_bytes(s);
    for (auto & c:tmp) {
        if (!is_rus(c))
            throw cipher_error(std::string("Text has invalid symbols: ")+st);
        if (is_low_rus(c)!=-1)
            c = numAlpha[is_low_rus(c)];
    }
    return tmp;
}

bool Table::is_rus(wchar_t wch)
{
    std::wstring alf=lnumAlpha+numAlpha;
    for (uint i=0; i<alf.length(); i++) {
        if (wch == alf[i])
            return true;
    }
    return false;
}

int Table::is_low_rus(wchar_t wch)
{
    for (uint i=0; i<lnumAlpha.length(); i++) {
        if (wch == lnumAlpha[i])
            return i;
    }
    return -1;
}

std::wstring Table::encrypt(const std::wstring& open_text)
{
    
    std::wstring text(open_text);
    std::wstring valid_text=toValidtext(text);
    if(key>=valid_text.length())
        key = valid_text.length()/2;
    size_t pos = 0;
    std::wstring dectext=L"";
    std::wstring alpha;
    while (valid_text.size()%key!=0) {
        valid_text+=L" ";
    }
    size_t size=valid_text.size()/key;
    for (size_t i=1; i<=size; i++) {
        std::wstring sub = valid_text.substr(pos, key);
        subNum[i]=sub;
        pos=pos+key;
    }
    for (int stolb=key; stolb>=1; stolb--) {
        for (size_t str=1; str<=size; str++) {
            alpha = subNum[str][stolb-1];
            if(alpha==L" ")
                dectext+=L"*";
            else
                dectext+=alpha;
        }
    }
    return dectext;
}

std::wstring Table::decrypt(const std::wstring& cipher_text)
{
    numAlpha+=L"*";
    std::wstring ctext(cipher_text);
    std::wstring valid_text=toValidtext(ctext);
    numAlpha.erase(numAlpha.length()-1,1);
    size_t size=valid_text.size()/key;
    size_t pos = 0;
    std::wstring text=L"", restext;
    std::wstring alpha;
    for (uint i=1; i<=key; i++) {
        std::wstring sub = valid_text.substr(pos, size);
        resubNum[i]=sub;
        pos=pos+size;
    }
    for (size_t stolb=1; stolb<=size; stolb++) {
        for (size_t str=key; str>=1; str--) {
            text+=resubNum[str][stolb-1];
        }
    }
    restext=text;
    for (size_t i= text.size()-1; i>=0; i--) {
        alpha=text[i];
        if (alpha==L"*") {
            restext.erase(i, 1);
        } else {
            break;
        }
    }
    return restext;
}
