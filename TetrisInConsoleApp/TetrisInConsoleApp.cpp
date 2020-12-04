// TetrisInConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <thread>

using namespace std;



wstring tetromino[7];
int fieldWidth = 12;
int fieldHeight = 18;

int screenWidth = 120;  // standard console screen X (columns)
int screenHeight = 30; // standard screen size Y (rows)

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

bool DoesTetrominoFit(int tetrominoParameter, int rotation, int posX, int posY)
{
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            // get index into piece
            int pi = Rotate(px, py, rotation);

            // get index into field
            int fi = (posY + py) * fieldWidth + (posX + px);

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

int main()
{
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");

    tetromino[2].append(L".X..");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"..X.");
    tetromino[2].append(L"....");

    tetromino[3].append(L"....");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"..X.");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L"..X.");
    tetromino[4].append(L"....");

    tetromino[5].append(L"....");
    tetromino[5].append(L".XX.");
    tetromino[5].append(L"..X.");
    tetromino[5].append(L"..X.");

    tetromino[6].append(L"....");
    tetromino[6].append(L".XX.");
    tetromino[6].append(L".X..");
    tetromino[6].append(L".X..");

    field = new unsigned char[fieldWidth*fieldHeight];
    for (int x = 0; x < fieldWidth; x++)
    {
        for (int y = 0; y < fieldHeight; y++)
        {
            field[y * fieldWidth + x] = (x == 0 || x == fieldWidth - 1 || y == fieldHeight - 1) ? 9 : 0;
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

    //input player
    bool bKey[4];
    bool rotateHold = false;

    //time var
    int speed = 20;
    int speedCounter = 0;
    bool forceDown = false;
    

    while (!gameOver)
    {
        // ===================== Game timing =====================
        this_thread::sleep_for(50ms); // game tick
        speedCounter++;
        forceDown = (speedCounter == speed);


        // ===================== Input: see if key is pressed ====================
        for (int key = 0; key < 4; key++)
        {
            // [0] hexdec = x27: right key
            // [1] hexdec = x25: left key
            // [2] hexdec = x28Z: Down key
            bKey[key] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[key]))) != 0;

        }

        // ===================== Game-Logic =====================
        if (bKey[0]) 
        {
            if (DoesTetrominoFit(currentPiece, currentRotation, currentX + 1, currentY)) 
            {
                currentX = currentX + 1;
            }
        }
        if (bKey[1])
        {
            if (DoesTetrominoFit(currentPiece, currentRotation, currentX - 1, currentY))
            {
                currentX = currentX - 1;
            }
        }
        if (bKey[2])
        {
            if (DoesTetrominoFit(currentPiece, currentRotation, currentX, currentY + 1))
            {
                currentY = currentY + 1;
            }
        }
        if (bKey[3])
        {
            if (!rotateHold && DoesTetrominoFit(currentPiece, currentRotation + 1, currentX, currentY))
            {
                currentRotation = currentRotation + 1;
                rotateHold = true;
            }
            else 
            {
                rotateHold = false;
            }
              
        }

        if (forceDown) 
        {
            if (DoesTetrominoFit(currentPiece, currentRotation, currentX, currentY + 1))
                currentY++; // translate tetromino down.
            else 
            {
                //lock the current piece in the field


                //Check have we got any lines


                // choose next piece


                // if piece does not fit
                gameOver = !DoesTetrominoFit(currentPiece, currentRotation, currentX, currentY);


            
            }
        }


        // render output

        //draw field
        for (int  x = 0; x < fieldWidth; x++)
        {
            for (int y = 0; y < fieldHeight; y++)
            {
                screen[(y + 2)*screenWidth + (x + 2)] = L" ABCDEFG=#"[field[y*fieldWidth + x]];
            }
        }

        //draw current piece
        for (int px = 0; px < 4; px++)
        {
            for (int py = 0; py < 4; py++)
            {
                if (tetromino[currentPiece][Rotate(px, py, currentRotation)] == L'X')
                    screen[(currentY + py + 2) * screenWidth + (currentX + px + 2)] = currentPiece + 65; // 65 is Ascii for A
            }
        }



        //display frame
        WriteConsoleOutputCharacter(console, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);

    }
    return 0;
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
