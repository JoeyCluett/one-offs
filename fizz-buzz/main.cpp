#include <iostream>
#include <string>

//
// fizzbuzz using a big ole' character string as a lookup table
//
//  to build:
// >> bash build.bash
//

using namespace std;

const int max_i = 150;

int main(int argc, char* argv[]) {

    const char* lut =
        "FizzBuzz\0        \0        \0Fizz    \0        \0"
        "Buzz    \0Fizz    \0        \0        \0Fizz    \0"
        "Buzz    \0        \0Fizz    \0        \0 ";

    for(int i = 0; i <= max_i; i++) {
        const char* ptr = lut+(9*(i%15));
        (*ptr==' '?cout<<i:cout<<ptr)<<endl;
    }

    return 0;
}
