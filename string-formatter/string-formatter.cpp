#include "string-formatter.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

void print(const char* format_string, const std::vector<many_type>& items) {
    
    std::ostream& os = std::cout;

    std::string format(format_string);
    std::string idx_string = "";

    const int state_default              = 0;
    const int state_expecting_open_brace = 1;
    const int state_wait_close_brace     = 2;

    int state_current = state_default;

    for(int i = 0; i < format.size();) {
        char c = format[i];

        switch(state_current) {
            case state_default:
                if(c == '$') {
                    state_current = state_expecting_open_brace;
                }
                else {
                    os << c;
                }

                i++;
                break;

            case state_expecting_open_brace:
                if(c == '{') {
                    state_current = state_wait_close_brace;
                }

                i++;
                break;

            case state_wait_close_brace:
                if(c >= '0' && c <= '9') {
                    idx_string.push_back( c );
                }
                else if(c == '}') {

                    int idx = std::stoi(idx_string);
                    os << items[idx].get_as_string();
                    idx_string.clear();

                    state_current = state_default;

                }
                else {
                    throw std::runtime_error("pformat invalid format specifier index");
                }

                i++;
                break;

            default:
                throw std::runtime_error( "pformat : invalid internal state" );
        }

    }
}

many_type::many_type(char i) {
    this->type = many_type_char;
    this->i8 = i;
}

many_type::many_type(short i) {
    this->type = many_type_short;
    this->i16 = i;
}

many_type::many_type(unsigned char u) {
    this->type = many_type_uchar;
    this->u8 = u;
}

many_type::many_type(unsigned short u) {
    this->type = many_type_ushort;
    this->u16 = u;
}

many_type::many_type(int i) {
    this->type = many_type_int;
    this->i32 = i;
}

many_type::many_type(long int i) {
    this->type = many_type_long;
    this->i64 = i;
}

many_type::many_type(unsigned int u) {
    this->type = many_type_uint;
    this->u32 = u;
}

many_type::many_type(unsigned long int u) {
    this->type = many_type_ulong;
    this->u64 = u;
}

many_type::many_type(float f) {
    this->type = many_type_float;
    this->f32 = f;
}

many_type::many_type(double f) {
    this->type = many_type_double;
    this->f64 = f;
}

many_type::many_type(void* vptr) {
    this->type = many_type_vptr;
    this->vptr = vptr;
}

many_type::many_type(const char* cptr) {
    this->type = many_type_cptr;
    this->cptr = (char*)cptr;
}

many_type::many_type(std::string str) {
    this->type = many_type_string;
    this->str = str;
}

std::string many_type::get_as_string(void) const {

    switch(this->type) {
        case many_type_char:   return std::to_string( this->i8 );
        case many_type_uchar:  return std::to_string( this->u8 );
        case many_type_short:  return std::to_string( this->i16 );
        case many_type_ushort: return std::to_string( this->u16 );
        case many_type_int:    return std::to_string( this->i32 );

        case many_type_uint:   return std::to_string( this->u32 );
        case many_type_long:   return std::to_string( this->i64 );
        case many_type_ulong:  return std::to_string( this->u64 );
        case many_type_float:  return std::to_string( this->f32 );
        case many_type_double: return std::to_string( this->f64 );
        case many_type_vptr:
            {
                std::string tmp;
                const char* lut = "0123456789ABCDEF";

                union {
                    unsigned long int u;
                    void* ptr;
                };

                ptr = this->vptr;

                for(int i = 60; i >= 0; i -= 4) {
                    tmp.push_back( lut[(u >> i) & 0x0F] );
                }

                return tmp;
            }
        case many_type_cptr:   return std::string( this->cptr );
        case many_type_string: return this->str;
        default:
            throw std::runtime_error( "many_type::get_as_string : invalid internal type" );
    }

}
