//
//  LargeNumber.cpp
//  LargeNumber
//
//  Created by Griselda Rodriguez on 3/19/14.
//  Copyright (c) 2014 Jason Carruthers. All rights reserved.
//

#include <iostream>
#include "LargeNumber.h"




/*
 * Constructors
 */
LargeNumber::LargeNumber(const std::string &newNum)
{
    mNum = newNum;
    mSign = ( newNum != "" && newNum[0] == '-' ) ? -1 : 1;
}


/*
 * Accessors
 */
std::string LargeNumber::GetNumAsString() const
{
    return mNum;
}

void LargeNumber::Display() const
{
    if( mSign == -1 )
        std::cout << "-";
    
    for(int i = 0; i < mNum.size(); i++)
        std::cout << mNum[i];
    
    std::cout << "\n";
}


/*
 * Mutators
 */
void LargeNumber::SetNum(const std::string &newNum)
{
    mNum = newNum;
}


/*
 * Overloaded operators
 */
LargeNumber& LargeNumber::operator=(const LargeNumber &right)
{
    SetNum(right.mNum);
    mSign = right.mSign;
    return *this;
}

bool LargeNumber::operator==(const LargeNumber &right) const
{
    return (mNum == right.mNum && mSign == right.mSign);
}

bool LargeNumber::operator!=(const LargeNumber &right) const
{
    return !(*this == right);
}

LargeNumber& LargeNumber::operator+(const LargeNumber &right) const
{
    int carry = 0;
    int digitSum = 0;
    int digitVal = 0;

    int commonLength = 0;
    LargeNumber smallerNum = (*this < right) ? *this : right;
    LargeNumber largerNum = (*this < right) ? right : *this;
    LargeNumber* sum = new LargeNumber;
    
    
    
    /*
     * If the outcome is a negative number, use subtraction to
     * find the sum by subtracting the absolute-value shortest number
     * from the absolute-value longest number and then multiplying
     * that result by -1.
     */
    if( smallerNum.mSign == 1 && largerNum.mSign == -1 )
    {
        return (largerNum - smallerNum) * -1;
    }
    
    /*
     * If both numbers are negative, take the sum of the absolute-value
     * of both numbers and then multiply the sum by -1.
     */
    if( smallerNum.mSign == -1 && largerNum.mSign == -1 )
    {
        smallerNum.mSign = 1;
        largerNum.mSign = 1;
        return (smallerNum + largerNum) * -1;
    }
    
    /*
     * Pad the least-digit number with zeroes so that it's the same length as
     * the greatest-digit number
     */
    smallerNum.PadFrontWithZeroes(
                    static_cast<int>(largerNum.mNum.length() - smallerNum.mNum.length()));
    
    
    //Sum numbers
    commonLength = static_cast<int>(largerNum.mNum.length());
    for(int i = commonLength - 1; i >= 0; i--)
    {
        digitSum = CharNumToInt(largerNum.mNum[i]) + CharNumToInt(smallerNum.mNum[i]) + carry;
        digitVal = digitSum % 10;
        sum->mNum.insert(0, itos(digitVal));
        
        carry = digitSum / 10;
        
        /*
         * For testing purposes
         */
        std::cout << "digitSum:" << "\t" << digitSum << "\n";
        std::cout << "carry:" << "\t" << carry << "\n";
        std::cout << "sum:" << "\t" << sum->mNum << "\n";
    }
    
    std::string temp = "";
    temp += itoa(carry);
    if(temp != "0")
        sum->mNum.insert(0, temp);
    
    
    return *sum;
}



LargeNumber& LargeNumber::operator-(int right) const
{
    LargeNumber newRight = LargeNumber( itos(right) );
    return *this - newRight;
}

LargeNumber& LargeNumber::operator-(const LargeNumber &right) const
{
    int borrow = 0;
    int digitSum = 0;
    int digitVal = 0;
    
    int commonLength = 0;
    LargeNumber left = *this;
    LargeNumber rightCopy = right;
    LargeNumber* difference = new LargeNumber;
    
    /*
     * If there's a double-negative, change the sign of the
     * right number to positive and the problem becomes an addition
     * problem.
     */
    if( rightCopy.mSign == -1 )
    {
        return (*this + rightCopy);
    }
    
    /*
     * If it's a negative minus a positive, the difference of those
     * two numbers is the same as the sum of the absolute value of
     * both numbers times -1.
     */
    if( left.mSign == -1 && rightCopy.mSign == 1 )
    {
        left.mSign = 1;
        return (left + rightCopy) * -1;
    }
    
    /*
     * Get the resultant sign on the difference of numbers.
     */
    if( ((left < rightCopy) && (left.mSign == 1 && rightCopy.mSign == -1)) ||
        ((left < rightCopy) && (left.mSign == -1 && rightCopy.mSign == -1)) ||
        ((left > rightCopy) && (left.mSign == 1 && rightCopy.mSign == 1)) ||
        ((left > rightCopy) && (left.mSign == 1 && rightCopy.mSign == -1)) )
    {
        difference->mSign = 1;
    }
    else if( ((left < rightCopy) && (left.mSign == 1 && rightCopy.mSign == 1)) ||
             ((left < rightCopy) && (left.mSign == -1 && rightCopy.mSign == 1)) ||
             ((left > rightCopy) && (left.mSign == -1 && rightCopy.mSign == 1)) ||
             ((left > rightCopy) && (left.mSign == -1 && rightCopy.mSign == -1)) )
    {
        difference->mSign = -1;
    }
    
    LargeNumber smallerNum = (left < rightCopy) ? left : rightCopy;
    LargeNumber largerNum = (left < rightCopy) ? rightCopy : left;
    
    
    /*
     * Pad the least-digit number with zeroes so that it's the same length as
     * the greatest-digit number
     */
    /*
    int lengthDifference = abs( static_cast<int>(left.mNum.length() - rightCopy.mNum.length()) );
    if( left < rightCopy )
        left.PadFrontWithZeroes( lengthDifference );
    else
        rightCopy.PadFrontWithZeroes( lengthDifference );
     */
    int lengthDifference = abs( static_cast<int>(left.mNum.length() - rightCopy.mNum.length()) );
    smallerNum.PadFrontWithZeroes(lengthDifference);
    
    
    //Sum numbers
    commonLength = static_cast<int>( left.mNum.length() );
    for(int i = commonLength - 1; i >= 0; i--)
    {
        if( CharNumToInt(largerNum.mNum[i]) < (CharNumToInt(smallerNum.mNum[i])) )
        {
            largerNum.mNum[i - 1] = (itoa( atoi(largerNum.mNum[i - 1]) - 1 - 48) );
            borrow = 10;
        }
        
        digitSum = (CharNumToInt(largerNum.mNum[i]) + borrow) -
                            CharNumToInt(smallerNum.mNum[i]);
        borrow = 0;
        
        digitVal = digitSum % 10;
        difference->mNum.insert(0, itos(digitVal));
    }
    
    return *difference;
}



LargeNumber& LargeNumber::operator*(int right) const
{
    LargeNumber newRight = LargeNumber( itos(right) );
    return *this * newRight;
}

LargeNumber& LargeNumber::operator*(const LargeNumber &right) const
{
    LargeNumber product = *this;
    LargeNumber *retVal = new LargeNumber;
    LargeNumber base = *this;
    
    if( right.mNum == "0" )
    {
        product.mNum = "0";
        product.mSign = 1;
        *retVal = product;
        return *retVal;
    }
    
    product.mSign *= right.mSign;
    
    LargeNumber temp = (right - 1);
    for(int i = 0; temp > i; i++)
        product = product + base;
    
    *retVal = product;
    return *retVal;
}
 





LargeNumber& LargeNumber::operator/(const LargeNumber &right) const
{
    LargeNumber foo = *this;
    return foo;
}

 
LargeNumber& LargeNumber::operator+=(const LargeNumber &right)
{
    *this = *this + right;
    return *this;
}

LargeNumber& LargeNumber::operator-=(const LargeNumber &right)
{
    *this = *this - right;
    return *this;
}


LargeNumber& LargeNumber::operator*=(int right)
{
    LargeNumber newRight = LargeNumber( itos(right) );
    return (*this *= newRight);
}

LargeNumber& LargeNumber::operator*=(const LargeNumber &right)
{
    *this = *this * right;
    return *this;
}

LargeNumber& LargeNumber::operator/=(const LargeNumber &right)
{
    LargeNumber foo = *this;
    return foo;
}

 
bool LargeNumber::operator<(const LargeNumber &right) const
{
    if( (mSign == -1 && right.mSign == 1) ||
       ((mSign == 1 && right.mSign == 1) && (mNum.length() < right.mNum.length())) ||
       ((mSign == -1 && right.mSign == -1) && (mNum.length() > right.mNum.length())) )
        return true;
    else if( (mSign == 1 && right.mSign == -1) ||
            ((mSign == 1 && right.mSign == 1) && (mNum.length() > right.mNum.length())) ||
            ((mSign == -1 && right.mSign == -1) && (mNum.length() < right.mNum.length())) )
        return false;
    
    /*
     * The left and right numbers are the same length.
     * commonLength is the length of each number.
     */
    unsigned int commonLength = static_cast<unsigned int>( mNum.length() );
    for(unsigned int i = 0; i < commonLength; i++)
    {
        if( mNum[i] < right.mNum[i] )
            return true;
        else if( mNum[i] > right.mNum[i] )
            return false;
    }
    
    /*
     * The two numbers are equal
     */
    return false;
}

bool LargeNumber::operator>(int right) const
{
    LargeNumber newRight = LargeNumber( itos(right) );
    return *this > newRight;
}

bool LargeNumber::operator>(const LargeNumber &right) const
{
    return !(*this <= right);
}

bool LargeNumber::operator<=(const LargeNumber &right) const
{
    return (*this < right || *this == right);
}
 
bool LargeNumber::operator>=(const LargeNumber &right) const
{
    return !(*this < right);
}


/*
 * Private member functions
 */
char LargeNumber::itoa(int x) const
{
    if(x < 0 || x > 9)
    {
        std::cout << "Can't convert that number to ASCII" << "\n";
        return '?';
    }
    
    //On the ASCII table, the digits 0-9 start at 48 and end at 57
    return static_cast<char>(x + 48);
}

std::string LargeNumber::itos(int x) const
{
    if( x == 0 )
        return "0";
    
    x = abs( x );
    std::string retVal = "";
    int digitVal = 0;
    std::string temp = "";
    
    while(x != 0)
    {
        digitVal = x % 10;
        temp += itoa(digitVal);
        
        retVal.insert(0, temp);
        
        x /= 10;
    }
    
    return retVal;
}

int LargeNumber::atoi(char c) const
{
    return static_cast<int>(c);
}

int LargeNumber::CharNumToInt(char c) const
{
    return (static_cast<int>(c) - 48);
}

void LargeNumber::PadFrontWithZeroes(int padding)
{
    for(int i = 0; i < padding; i++)
        mNum.insert(0, "0");
    
    
    /*
     * For testing purposes
     */
    std::cout << "\n\n";
    std::cout << "After padding the smaller number with zeroes, it is..." << "\n";
    std::cout << mNum << "\n";
}












