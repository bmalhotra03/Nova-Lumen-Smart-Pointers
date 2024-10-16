// Author: Brij Malhotra
// Filename: nova.h
// Version: Version 1
// Description: This is the class definition of the Nova object

#include "lumen.h"
#include <iostream>

using namespace std;

#ifndef NOVA_H
#define NOVA_H

class Nova{
    
    private:
        int arrSize;
        Lumen * lumenArr;
        int max = 0;
        int min = 0;
        void novaCopy(const Nova&);

    public:
        Nova(Lumen * arr, int x);
        Nova(const Nova&);
        ~Nova();
        void operator=(const Nova&);    // Assignment operator
        void operator=(Nova&&);         // Move assignment operator
        Nova(Nova&&);                   // Move copy constructor
        void glow(int);
        void recharge();
        int getMax();
        int getMin();
        
        // Operator overloading for addition
        Nova operator+(unsigned int) const;
        Nova operator+(const Nova&) const;
        Nova operator++();
        Nova operator++(int);
        Nova operator+=(unsigned int);
        Nova operator+=(const Nova&);

        // Operator overloading for comparison
        bool operator>(const Nova&);
        bool operator>=(const Nova&);
        bool operator<(const Nova&);
        bool operator<=(const Nova&);
        bool operator==(const Nova&);
        bool operator!=(const Nova&);        
};

#endif 