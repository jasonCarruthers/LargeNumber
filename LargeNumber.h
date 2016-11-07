//
//  LargeNumber.h
//  LargeNumber
//
//  Created by Griselda Rodriguez on 3/19/14.
//  Copyright (c) 2014 Jason Carruthers. All rights reserved.
//

#ifndef LargeNumber_LargeNumber_h
#define LargeNumber_LargeNumber_h

#include <iostream>


class LargeNumber
{
public:
    /*
     * Constructors
     */
    LargeNumber(const std::string &newNum = "");
    
    
    /*
     * Accessors
     */
    std::string GetNumAsString() const;
    void Display() const;
    
    
    /*
     * Mutators
     */
    void SetNum(const std::string &newNum);
    

    /*
     * Overloaded operators
     */
    LargeNumber& operator=(const LargeNumber &right);
    bool operator==(const LargeNumber &right) const;
    bool operator!=(const LargeNumber &right) const;
    LargeNumber& operator+(const LargeNumber &right) const;
    LargeNumber& operator-(int right) const;
    LargeNumber& operator-(const LargeNumber &right) const;
    LargeNumber& operator*(int right) const;
    LargeNumber& operator*(const LargeNumber &right) const;
    LargeNumber& operator/(const LargeNumber &right) const;
    LargeNumber& operator+=(const LargeNumber &right);
    LargeNumber& operator-=(const LargeNumber &right);
    LargeNumber& operator*=(int right);
    LargeNumber& operator*=(const LargeNumber &right);
    LargeNumber& operator/=(const LargeNumber &right);
    bool operator<(const LargeNumber &right) const;
    bool operator>(int right) const;
    bool operator>(const LargeNumber &right) const;
    bool operator<=(const LargeNumber &right) const;
    bool operator>=(const LargeNumber &right) const;
    
    
private:
    char itoa(int x) const;
    std::string itos(int x) const;
    int atoi(char c) const;
    int CharNumToInt(char c) const;
    void PadFrontWithZeroes(int padding);

    
    std::string mNum;
    int mSign;
};


#endif
