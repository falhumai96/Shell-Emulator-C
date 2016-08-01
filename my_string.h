#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

typedef struct string {
    int size;
    int cap;
    char* arr;
} string;

string ini_string(string* this_str);
string ini_string_other(string* this_str, char* other);
string del_string(string* this_str);
string push_char(string* this_str, char other);
string concat(string* this_str, char* other);
char* to_string(string* this_str);
int str_size(string* this_str);
char get_char(string* this_str, int index);
string set_char(string* this_str, int index, char ch);

string ini_string(string* this_str) {
    (*this_str).size = 0;
    (*this_str).cap = 10;
    (*this_str).arr = (char*) malloc(sizeof (char) * 10);
    return *this_str;
}

string ini_string_other(string* this_str, char* other) {
    (*this_str).size = 0;
    (*this_str).cap = 10;
    (*this_str).arr = (char*) malloc(sizeof (char) * 10);
    *this_str = concat(this_str, other);
    return *this_str;
}

string del_string(string* this_str) {
    (*this_str).size = 0;
    (*this_str).cap = 0;
    free((*this_str).arr);
    (*this_str).arr = NULL;
    return *this_str;
}

string push_char(string* this_str, char other) {
    if ((*this_str).size >= (*this_str).cap) {
        (*this_str).cap = (*this_str).cap + 10;
        char* new_str = (char*) malloc(sizeof (char) * ((*this_str).cap) + 1);
        int i;
        for (i = 0; i < (*this_str).size; ++i) {
            new_str[i] = (*this_str).arr[i];
        }
        free((*this_str).arr);
        (*this_str).arr = new_str;
    }
    (*this_str).arr[(*this_str).size] = other;
    ++(*this_str).size;
    (*this_str).arr[(*this_str).size] = '\0';
    return *this_str;
}

string concat(string* this_str, char* other) {
    int i;
    for (i = 0; i < strlen(other); ++i) {
        *this_str = push_char(this_str, other[i]);
    }
    return *this_str;
}

char* to_string(string* this_str) {
    return (*this_str).arr;
}

int str_size(string* this_str) {
    return (*this_str).size;
}

char get_char(string* this_str, int index) {
    return (*this_str).arr[index];
}

string set_char(string* this_str, int index, char ch) {
    (*this_str).arr[index] = ch;
    return *this_str;
}

#endif