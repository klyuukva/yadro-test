//
// Created by Maria on 13.05.2024.
//

#include "Delays.h"
#include <iostream>

std::istream& operator>>(std::istream& is, Delays& delays) {
    is >> delays.read >> delays.write >> delays.move >> delays.rewind;
    if(delays.read < 0 || delays.write < 0 || delays.move < 0 || delays.rewind < 0) {
        is.setstate(std::ios::failbit);
    }
    return is;
}