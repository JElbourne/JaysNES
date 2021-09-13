// JaysNES.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>


int main()
{
    int a = 5;

    //uint16_t b = (0b1001110111111111 >> 8) & 0b0000000011111111;
    uint16_t b = (0x9DFF >> 8) & 0x00FF;
    std::cout << std::bitset<17>(b) << std::endl;
}
