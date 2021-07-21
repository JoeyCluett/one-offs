#pragma once

//
// no error checking
// can use the print() function as
//
//  print("${0} ${0} ${2} ${1}", { 0, "ZE-RO", 3.14159, "this one is unused" });
//
//  which would print:
//
//  0 0 3.14159 ZE-RO
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

const int many_type_char   = 0;
const int many_type_uchar  = 1;
const int many_type_short  = 2;
const int many_type_ushort = 3;
const int many_type_int    = 4;
const int many_type_uint   = 5;
const int many_type_long   = 6;
const int many_type_ulong  = 7;
const int many_type_float  = 8;
const int many_type_double = 9;
const int many_type_vptr   = 10;
const int many_type_cptr   = 11;
const int many_type_string = 12;

struct many_type {

    int type;

    union {
        char              i8;
        short             i16;
        int               i32;
        long int          i64;

        unsigned char     u8;
        unsigned short    u16;
        unsigned int      u32;
        unsigned long int u64;
        
        float  f32;
        double f64;

        // pointer types
        void* vptr;
        char* cptr; // c string type
    };

    std::string str;

    many_type(char i);
    many_type(short i);
    many_type(int i);
    many_type(long int i);
    many_type(unsigned char u);
    many_type(unsigned short u);
    many_type(unsigned int u);
    many_type(unsigned long int u);
    many_type(float f);
    many_type(double f);
    many_type(void* vptr);
    many_type(const char* cptr);
    many_type(std::string str);

    std::string get_as_string(void) const;

};

void print(const char* format_string, const std::vector<many_type>& items);

