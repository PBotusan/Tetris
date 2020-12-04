// TetrisInConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

using namespace std;



wstring tetromino[7];
int fieldWidth = 12;
int fieldHeight = 18;

int screenWidth = 80;
int screenHeight = 30;

unsigned char *field = nullptr;


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

    field = new unsigned char[fieldWidth*fieldHeight];
    for (int i = 0; i < fieldWidth; i++)
    {
        for (int x = 0; x < fieldHeight; x++)
        {
            field[x * fieldWidth + x] = (x == 0 || x == fieldWidth - 1 || x == fieldHeight - 1) ? 9 : 0;
        }
    }

    wchar_t* screen = new wchar_t[screenWidth * screenHeight];
    for (int i = 0; i < screenWidth * screenHeight; i++) screen[i] = L' ';

    HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );
    SetConsoleActiveScreenBuffer(console);
    DWORD dwBytesWritten = 0;

    // Game logic
    bool gameOver = false;

    int currentPiece = 0;
    int currentRotation = 0;
    int currentX = fieldWidth / 2;
    int currentY = 0;


    while (!gameOver)
    {
        // game timing

        // Input

        // game logic

        // render output

        //draw field
        for (int  x = 0; x < fieldWidth; x++)
        {
            for (int y = 0; y < fieldHeight; y++)
            {
                screen[(y + 0)*screenWidth + (x + 2)] = L" ABCDEFG=#"[field[y*fieldWidth + x]];

            }

        }


        //display frame
        WriteConsoleOutputCharacter(console, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);

    }
    return 0;
}

bool DoesTetrominoFit(int tetrominoParameter, int rotation, int posX, int posY) 
{
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            // get index into piece
            int pi = Rotate(px, py, rotation);

            int fi = (posY + py) * fieldWidth + px;

            if (posX + px >= 0 && posX + px < fieldWidth)
            {
                if (posY + py >= 0 && posY + py < fieldHeight) 
                {
                    if (tetromino[tetrominoParameter][pi] == L'X' && field[fi] != 0) 
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
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
