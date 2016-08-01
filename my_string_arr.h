#ifndef MY_STRING_ARR_H
#define MY_STRING_ARR_H

#include "my_string.h"

typedef struct string_arr {
    int size;
    int cap;
    string* arr;
} string_arr;

string_arr ini_str_arr(string_arr* this_arr);
string_arr ini_str_arr_other(string_arr* this_arr, string_arr* other);
string_arr del_str_arr(string_arr* this_arr);
string_arr push_str_other(string_arr* this_arr, char* str);
string_arr push_str_copy(string_arr* this_arr, string* str);
int arr_size(string_arr* this_arr);
char* get_string(string_arr* this_arr, int index);
string_arr set_string(string_arr* this_arr, int index, char* str);

string_arr ini_str_arr(string_arr* this_arr) {
    (*this_arr).size = 0;
    (*this_arr).cap = 10;
    (*this_arr).arr = (string*) malloc(sizeof (string) * 10);
    return *this_arr;
}

string_arr ini_str_arr_other(string_arr* this_arr, string_arr* other) {
    (*this_arr).size = 0;
    (*this_arr).cap = 10;
    (*this_arr).arr = (string*) malloc(sizeof (string) * 10);
    
    int i;
    for (i = 0; i < (*other).size; ++i) {
        *this_arr = push_str_other(this_arr, ((*other).arr[i]).arr);
    }
    
    return *this_arr;
}

string_arr del_str_arr(string_arr* this_arr) {
    int i;
    for (i = 0; i < (*this_arr).size; ++i) {
        (*this_arr).arr[i] = del_string(&(*this_arr).arr[i]);
    }
    (*this_arr).size = 0;
    (*this_arr).cap = 0;
    free((*this_arr).arr);
    (*this_arr).arr = NULL;
    return *this_arr;
}

// The caller should know that my array would only push a copy to the string
// i.e. if other was malloc()ed, then the caller have to free it itself
// i.e. the array is isolated from the outside

string_arr push_str_other(string_arr* this_arr, char* str) {
    string new_string = ini_string_other(&new_string, str);

    if ((*this_arr).size >= (*this_arr).cap) {
        (*this_arr).cap = (*this_arr).cap + 10;
        string* new_arr = (string*) malloc(sizeof (string) * (*this_arr).cap);
        int i;
        for (i = 0; i < (*this_arr).size; ++i) {

            new_arr[i] = (*this_arr).arr[i];

        }
        free((*this_arr).arr);
        (*this_arr).arr = new_arr;
    }

    string* temp = (*this_arr).arr;
    temp[(*this_arr).size].arr = new_string.arr;
    temp[(*this_arr).size].size = new_string.size;
    temp[(*this_arr).size].cap = new_string.cap;

    ++(*this_arr).size;
    return *this_arr;
}

// The caller should know that my array would only push a copy to the string
// i.e. if other was malloc()ed, then the caller have to free it itself
// i.e. the array is isolated from the outside

string_arr push_str_copy(string_arr* this_arr, string* str) {
    string new_string = ini_string_other(&new_string, (*str).arr);

    if ((*this_arr).size >= (*this_arr).cap) {
        (*this_arr).cap = (*this_arr).cap + 10;
        string* new_arr = (string*) malloc(sizeof (string) * (*this_arr).cap);
        int i;
        for (i = 0; i < (*this_arr).size; ++i) {

            new_arr[i] = (*this_arr).arr[i];

        }
        free((*this_arr).arr);
        (*this_arr).arr = new_arr;
    }

    string* temp = (*this_arr).arr;
    temp[(*this_arr).size].arr = new_string.arr;
    temp[(*this_arr).size].size = new_string.size;
    temp[(*this_arr).size].cap = new_string.cap;

    ++(*this_arr).size;
    return *this_arr;
}

int arr_size(string_arr* this_arr) {
    return (*this_arr).size;
}

char* get_string(string_arr* this_arr, int index) {
    return ((*this_arr).arr[index]).arr;
}

string_arr set_string(string_arr* this_arr, int index, char* str) {
    free(((*this_arr).arr[index]).arr);
    string new_string = ini_string_other(&new_string, str);
    ((*this_arr).arr[index]).arr = new_string.arr;
    ((*this_arr).arr[index]).size = new_string.size;
    ((*this_arr).arr[index]).cap = new_string.cap;
    return *this_arr;
}

#endif