#pragma once

#include <cinttypes>
#include "Number.h"

class Additor
{
public:
    Additor();
    ~Additor();

    Number* Add(Number* addend1, Number* addend2);
private:
    Number* biggerAddend;
    Number* smallerAddend;
    
};