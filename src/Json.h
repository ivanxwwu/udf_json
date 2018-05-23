//
// Created by root on 18-5-21.
//

#ifndef UDF_JSON_JSON_H
#define UDF_JSON_JSON_H
#include "rapidjson/pointer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "stdarg.h"
using namespace rapidjson;


class Json
{
public:
    Json(const std::string& content, const std::string& uri)
            :p(uri.c_str())
    {
        d.Parse(content.c_str());
    }
    bool IsValid()
    {
        if (!p.IsValid()) {
            SetErrorMsg("wrong uri:%s", GetParseUriErrorStr(p.GetParseErrorCode()).c_str());
            return false;
        }
        if (d.HasParseError()) {
            SetErrorMsg("wrong json: offset:%ld. %s", d.GetErrorOffset(), GetParseJsonErrorStr(d.GetParseError()).c_str());
            return false;
        }
        return true;
    }
    void SetErrorMsg(const char *fmt, ...) __attribute__((format(printf, 2, 3)))
    {
        va_list ap;
        va_start(ap, fmt);
        char buf[4096] = {0};
        int size = vsnprintf(buf, sizeof(buf), fmt, ap);
        if (size>4096)
            msg.assign(buf, 4096);
        else
            msg.assign(buf, size);
    }
    std::string GetErrorMsg() const
    {
        return msg;
    }
    std::string Str()
    {
        Value* v = p.Get(d);
        if (v==nullptr)
            return "";
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        v->Accept(writer);
        return std::string(buffer.GetString(), buffer.GetSize());
    }
    long long GetArrayCount()
    {
        Value* v = p.Get(d);
        if (v==nullptr)
            return 0;
        if(!v->IsArray())
            return 0;
        return v->Size();
    }

private:
    std::string GetParseUriErrorStr(int errorCode)
    {
        switch (errorCode)
        {
            case kPointerParseErrorTokenMustBeginWithSolidus:
                return "A token must begin with a '/'";
            case kPointerParseErrorInvalidEscape:
                return "Invalid escape";
            case kPointerParseErrorInvalidPercentEncoding:
                return "Invalid percent encoding in URI fragment";
            case kPointerParseErrorCharacterMustPercentEncode:
                return "A character must percent encoded in URI fragment";
            default:
                return "Unknown";
        }
    }

    std::string GetParseJsonErrorStr(int errorCode)
    {
        switch (errorCode)
        {
            case kParseErrorDocumentEmpty:
                return "The document is empty.";
            case kParseErrorDocumentRootNotSingular:
                return "The document root must not follow by other values.";
            case kParseErrorValueInvalid:
                return "Invalid value.";
            case kParseErrorObjectMissName:
                return "Missing a name for object member.";
            case kParseErrorObjectMissColon:
                return "Missing a colon after a name of object member.";
            case kParseErrorObjectMissCommaOrCurlyBracket:
                return "Missing a comma or '}' after an object member.";
            case kParseErrorArrayMissCommaOrSquareBracket:
                return "Missing a comma or ']' after an array element.";
            case kParseErrorStringUnicodeEscapeInvalidHex:
                return "Incorrect hex digit after \\\\u escape in string.";
            case kParseErrorStringUnicodeSurrogateInvalid:
                return "The surrogate pair in string is invalid.";
            case kParseErrorStringEscapeInvalid:
                return "Invalid escape character in string.";
            case kParseErrorStringMissQuotationMark:
                return "Missing a closing quotation mark in string.";
            case kParseErrorStringInvalidEncoding:
                return "Invalid encoding in string.";
            case kParseErrorNumberTooBig:
                return "Number too big to be stored in double.";
            case kParseErrorNumberMissFraction:
                return "Miss fraction part in number.";
            case kParseErrorNumberMissExponent:
                return "Miss exponent in number.";
            case kParseErrorTermination:
                return "Parsing was terminated.";
            case kParseErrorUnspecificSyntaxError:
                return "Unspecific syntax error.";
            default:
                return "Unknown";
        }
    }

private:
    Pointer p;
    Document d;
    std::string msg;
};


#endif //UDF_JSON_JSON_H
