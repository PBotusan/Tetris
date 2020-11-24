// TetrisInConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;


wstring tetromino[7];

// positionx, positiony
int Rotate(int px, int py, int rotate) 
{
    switch (rotate % 4)
    {
        case 0: return py * 4 + px;         // 0 degrees
        case 1: return 12 + py - (px * 4);  // 90 degrees
        case 2: return 15 - (py * 4) - px;  // 180 degrees
        case 3: return 3 - py + (px * 4);   // 270 degrees
    }
    return 0;

}

int main()
{
    tetromino[0].append(L"..x.");
    tetromino[0].append(L"..x.");
    tetromino[0].append(L"..x.");
    tetromino[0].append(L"..x.");

    tetromino[1].append(L"..x.");
    tetromino[1].append(L".xx.");
    tetromino[1].append(L".x..");
    tetromino[1].append(L"....");

    tetromino[2].append(L".x..");
    tetromino[2].append(L".xx.");
    tetromino[2].append(L"..x.");
    tetromino[2].append(L"....");

    tetromino[3].append(L"....");
    tetromino[3].append(L".xx.");
    tetromino[3].append(L".xx.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"..x.");
    tetromino[4].append(L".xx.");
    tetromino[4].append(L"..x.");
    tetromino[4].append(L"....");

    tetromino[5].append(L"....");
    tetromino[5].append(L".xx.");
    tetromino[5].append(L"..x.");
    tetromino[5].append(L"..x.");

    tetromino[6].append(L"....");
    tetromino[6].append(L".xx.");
    tetromino[6].append(L".x..");
    tetromino[6].append(L".x..");




    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
