#ifndef STRING_PROCESSOR
#define STRING_PROCESSOR
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>
#include <stdio.h>
#include "sort.h"
#define STRING_MAX 512ull

const int32_t get_str(const char const* msg, char* str, const int32_t limit)
{
    if (msg != NULL)
    {
        printf("%s", msg);
    }

    // Зчитуємо рядок
    if (fgets(str, limit, stdin) == NULL)
    {
        return 0;
    }

    // Знаходимо реальну довжину та видаляємо символ переносу рядка '\n', якщо він є
    int32_t count = 0;
    while (str[count] != '\0')
    {
        if (str[count] == '\n')
        {
            str[count] = '\0';
            break;
        }
        count++;
    }
    return count;
}

const size_t strlenn(const char* str)
{
    const char* s = str;
    while (*s)
    {
        s++;
    }
    return (size_t)(s - str);
}

void strcopy(char* fStr, char* sStr, size_t until)
{
    size_t i = 0;
    // Копіюємо символи, поки не досягнемо ліміту або кінця вхідного рядка
    while (i < until && sStr[i] != '\0')
    {
        fStr[i] = sStr[i];
        i++;
    }
    // Обов'язково додаємо термінальний нуль
    fStr[i] = '\0';
}

int32_t strcmpp(const char* fStr, const char* sStr)
{
    while (*fStr && (*fStr == *sStr))
    {
        fStr++;
        sStr++;
    }
    // Повертаємо різницю значень (від'ємне, якщо fStr < sStr, 0 якщо рівні, додатне якщо fStr > sStr)
    return *(const unsigned char*)fStr - *(const unsigned char*)sStr;
}

// ... [Далі йде ваш існуючий код: strcatt, is_string_valid, process_string без змін] ...

char* strcatt(char* fStr, const char* sStr)
{
    char* ptr = fStr + strlenn(fStr);
    while (*sStr != '\0')
    {
        *ptr++ = *sStr++;
    }
    *ptr = '\0';
    return fStr;
}

bool is_string_valid(char* str)
{
    bool isThereString = false;
    bool isThereColon = false;
    const size_t size = strlenn(str);
    for (size_t i = 0; i < size; i++)
    {
        if ((str[i] == ':' || str[i] == ';' || str[i] == ',') && i == 0ull)
        {
            return false;
        }
        if (str[i] == ':')
        {
            isThereColon = true;
        }
        else if (isThereColon)
        {
            if (str[i] == ',')
            {
                if (!isalpha(str[i - 1ull]) && str[i - 1ull] != ' ')
                {
                    return false;
                }
                else
                {
                    isThereString = true;
                }
            }
            if (str[i] == ';')
            {
                if (!isThereString || (!isalpha(str[i - 1ull]) && str[i - 1ull] != ' '))
                {
                    return false;
                }
                else
                {
                    isThereColon = false;
                }
            }
            if (str[i] == ':')
            {
                return false;
            }
        }
        else
        {
            isThereString = false;
        }
    }
    return true;
}

char* process_string(char* str)
{
    const size_t length = strlenn(str);
    char* result = (char*)calloc(length, sizeof(char));
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] != ':')
        {
            char temp[2] = { str[i], '\0' };
            strcatt(result, temp);
            continue;
        }
        if (str[i + 1] != ' ')
        {
            return NULL;
        }
        strcatt(result, ": ");
        const size_t strsPreCnt = 100;
        char** arr = (char**)calloc(strsPreCnt, sizeof(char*));
        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++)
        {
            arr[strsCnt] = (char*)calloc(STRING_MAX, sizeof(char));
        }
        for (size_t j = i + 2ull, strRealCnt = 0ull; j < length; j++)
        {
            if (str[j] == ',')
            {
                ++strRealCnt;
                ++j;
            }
            else if (str[j] == ';')
            {
                quick_sort(arr, ++strRealCnt);
                for (size_t k = 0; k < strRealCnt; k++)
                {
                    strcatt(result, arr[k]);
                    if (k == strRealCnt - 1ull)
                    {
                        strcatt(result, ";");
                    }
                    else
                    {
                        strcatt(result, ", ");
                    }
                }
                i = j;
                break;
            }
            else
            {
                char temp[2] = { str[j], '\0' };
                strcatt(arr[strRealCnt], temp);
            }
        }
        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++)
        {
            free(arr[strsCnt]);
        }
        free(arr);
    }
    return result;
}
#endif