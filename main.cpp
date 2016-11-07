//
//  main.cpp
//  LargeNumber
//
//  Created by Griselda Rodriguez on 3/19/14.
//  Copyright (c) 2014 Jason Carruthers. All rights reserved.
//

#include <iostream>
#include "LargeNumber.h"



/*
 * Global function prototypes
 */
void TestAddition();
void TestSubtraction();
void TestMultiplication();





int main(int argc, const char * argv[])
{
    //TestAddition();
    TestSubtraction();
    //TestMultiplication();
    
    
    return 0;
}





/*
 * Global function implementations
 */
void TestAddition()
{
    LargeNumber largeNum("5689");
    
    largeNum.Display();
    largeNum.SetNum("55555");
    largeNum.Display();
    largeNum = largeNum + LargeNumber("88");
    largeNum.Display();
}



void TestSubtraction()
{
    LargeNumber num1("55");
    LargeNumber num2("33");
    LargeNumber num3;
    LargeNumber num4("46");
    LargeNumber num5;
    
    
    num1.Display();
    num2.Display();
    
    num3 = num1 - num2;
    num3.Display();
    
    num5 = num1 - num4;
    num5.Display();
}



void TestMultiplication()
{
    LargeNumber num1("50");
    LargeNumber num2("3");
    LargeNumber num3;
    LargeNumber num4;
    LargeNumber num5( num1 );
    LargeNumber num6( num5 );
    
    num1.Display();
    num2.Display();
    
    num3 = num1 * num2;
    num3.Display();
    
    num4 = num1 * 3;
    num4.Display();
    
    num5 *= num2;
    num5.Display();
    
    num6 *= 3;
    num6.Display();
}









