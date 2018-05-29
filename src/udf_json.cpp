//
// Created by root on 18-5-20.
//


#include <mysql.h>
#include <mysql_com.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include "Json.h"

extern "C"
{
// json_get_value
my_bool udf_json_get_value_init(UDF_INIT* initid, UDF_ARGS* args, char* message);
void udf_json_get_value_deinit(UDF_INIT* initid);
char* udf_json_get_value(UDF_INIT* initid, UDF_ARGS* args, char* result, unsigned long* length, char* is_null, char *error);

my_bool udf_json_array_length_init(UDF_INIT* initid, UDF_ARGS* args, char* message);
void udf_json_array_length_deinit(UDF_INIT* initid);
long long udf_json_array_length(UDF_INIT* initid, UDF_ARGS* args, char* result, unsigned long* length, char* is_null, char *error);
}

my_bool udf_json_get_value_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
    if (args->arg_count != 2)
    {
        strcpy(message,"wrong number of arguments: udf_json_get_value() requires two argument");
        return 1;
    }

    if (args->arg_type[0] != STRING_RESULT
        || args->arg_type[1] != STRING_RESULT
           )
    {
        strcpy(message,"udf_json_get_value() requires two string as parameter");
        return 1;
    }

    initid->maybe_null = 1;
    initid->max_length = 32;
    initid->ptr = (char*)malloc(4096*128);
    return 0;
}

void udf_json_get_value_deinit(UDF_INIT* initid)
{
    void *void_ptr = initid->ptr;
    char *data = static_cast<char*>(void_ptr);
    if (data)
        delete data;
}

char* udf_json_get_value(UDF_INIT* initid, UDF_ARGS* args, char* result, unsigned long* length, char* is_null, char *error)
{
    if (args->arg_type[0] != STRING_RESULT
        || args->arg_type[1] != STRING_RESULT
        || args->args[0] == NULL
        || args->args[1] == NULL    )
    {
        return NULL;
    }

    Json json(std::string(args->args[0], args->lengths[0]), std::string(args->args[1], args->lengths[1]));
    if (!json.IsValid()) {
        return NULL;
    }
    size_t len = json.Str().size();
    if (len < 256) {
        strncpy(result, json.Str().c_str(), len);
        *length = len;
        return result;
    } else {
        strncpy(initid->ptr, json.Str().c_str(), len);
        initid->ptr[len - 1] = 0;
        return initid->ptr;
    }
}

my_bool udf_json_array_length_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
    if (args->arg_count != 2)
    {
        strcpy(message,"wrong number of arguments: udf_json_array_length() requires two argument");
        return 1;
    }

    if (args->arg_type[0] != STRING_RESULT
        || args->arg_type[1] != STRING_RESULT
            )
    {
        strcpy(message,"udf_json_array_length() requires two string as parameter");
        return 1;
    }

    initid->maybe_null = 0;
    initid->max_length = 11;
    return 0;
}

void udf_json_array_length_deinit(UDF_INIT* initid)
{

}

long long udf_json_array_length(UDF_INIT* initid, UDF_ARGS* args, char* result, unsigned long* length, char* is_null, char *error)
{
    if (args->arg_type[0] != STRING_RESULT
        || args->arg_type[1] != STRING_RESULT
        || args->args[0] == NULL
        || args->args[1] == NULL    )
    {
        return 0;
    }
    Json json(std::string(args->args[0], args->lengths[0]), std::string(args->args[1], args->lengths[1]));
    if (!json.IsValid()) {
        return 0;
    }
    return json.GetArrayCount();
}