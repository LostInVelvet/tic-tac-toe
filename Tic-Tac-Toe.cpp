// Version 5

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
    Return Code:
    -1
    -2  Spot Taken on Grid
    -3  No best move
    -4
    -5  Input out of Range
    -6  Input is Valid
    -7  Draw
    -8  No Win
    -9  Win
*/

const char PLAYERCHAR = 'X';
const char BOTCHAR  = 'O';
const char BLANK = ' ';
const int MAXROUNDS = 5;

void DefaultDisplay();
void Display(char board[3][3]);
int GetInput();
int CheckInput(int input, char turnID);
void Convert(char turnID, int input, char board[3][3]);
int CheckGridVacancy(char turnID, int input, char board[3][3]);
int CheckWin(char turnID, char board[3][3]);
int CheckDraw(char board[3][3]);
void ClearBoard(char board[3][3]);

//BotCheck


int main ()
{
    srand(time(NULL));  // seeding random number generator
    char board[3][3];
    char turnID;
    int input, test=-5, win=-8;

    ClearBoard(board);
    DefaultDisplay();
    for(int x=0; x<MAXROUNDS; x++)
    {
        // Player Turn----------------------------------------------------------------------------------------------
        turnID = PLAYERCHAR;
        while(test == -5 or test == -2)
        {
            input = GetInput();
            test = CheckInput(input, turnID);
            if(test == -6) test = CheckGridVacancy(turnID, input, board);
        }
        Convert(turnID, input, board);

        // Check for Win-Player
        win = CheckWin(turnID, board);
        if(win == -9)
        {
            cout << "Player Wins!" << endl;
            Display(board);
            return 0;
        }

        win = CheckDraw(board);
        if(win == -7)
        {
            cout << "The game is a Draw!" << endl;
            Display(board);
            return 0;
        }

        // Bot Turn -------------------------------------------------------------------------------------------------
        test = -5; // Bot Number should never be out of range.
        turnID = BOTCHAR;
        while(test == -5 or test == -2)
        {   
               input = rand()%9;
               test = CheckInput(input, turnID);
               if(test == -6)
                  test = CheckGridVacancy(turnID, input, board);
        }
        cout << "Bot plays " << input << endl;
        Convert(turnID, input, board);

        // Check for Win-Bot
        win = CheckWin(turnID, board);
        if(win == -9)
        {
            cout << "Bot Wins!" << endl;
            Display(board);
            return 0;
        }

        Display(board);
        test = -5;  // Resting the test value
    }
    return 0;
}

void ClearBoard(char board[3][3])
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            board[i][j]=BLANK;

    return;
}

int CheckWin(char turnID, char board[3][3])
{
    if(board[0][0] == turnID and board[0][1] == turnID and board[0][2] == turnID) return -9;  // Horizontal
    if(board[1][0] == turnID and board[1][1] == turnID and board[1][2] == turnID) return -9;  // Horizontal
    if(board[2][0] == turnID and board[2][1] == turnID and board[2][2] == turnID) return -9;  // Horizontal
    if(board[0][0] == turnID and board[1][0] == turnID and board[2][0] == turnID) return -9;  // Vertical
    if(board[0][1] == turnID and board[1][1] == turnID and board[2][1] == turnID) return -9;  // Vertical
    if(board[0][2] == turnID and board[1][2] == turnID and board[2][2] == turnID) return -9;  // Vertical
    if(board[0][0] == turnID and board[1][1] == turnID and board[2][2] == turnID) return -9;  // Right to Left
    if(board[0][2] == turnID and board[1][1] == turnID and board[2][0] == turnID) return -9;  // Left to Right

    return -8;
}

int CheckDraw(char board[3][3])
{
    if(board[0][0] != BLANK and board[0][1] != BLANK and board[0][2] != BLANK and
       board[1][0] != BLANK and board[1][1] != BLANK and board[1][2] != BLANK and
       board[2][0] != BLANK and board[2][1] != BLANK and board[2][2] != BLANK) return -7;
    else return -8;
}

int CheckGridVacancy(char turnID, int input, char board[3][3])
{
    switch(input)
    {
       case 1: if(board[0][0] == BLANK) return -6;
       break;
       case 2: if(board[0][1] == BLANK) return -6;
       break;
       case 3: if(board[0][2] == BLANK) return -6;
       break;
       case 4: if(board[1][0] == BLANK) return -6;
       break;
       case 5: if(board[1][1] == BLANK) return -6;
       break;
       case 6: if(board[1][2] == BLANK) return -6;
       break;
       case 7: if(board[2][0] == BLANK) return -6;
       break;
       case 8: if(board[2][1] == BLANK) return -6;
       break;
       case 9: if(board[2][2] == BLANK) return -6;
    }
    if(turnID == PLAYERCHAR)
        cout << "The grid you chose is taken, pick another." << endl;
    return -2;
}

void Convert(char turnID, int input, char board[3][3])
{
    switch(input)
    {
       case 1: board[0][0] = turnID;
       break;
       case 2: board[0][1] = turnID;
       break;
       case 3: board[0][2] = turnID;
       break;
       case 4: board[1][0] = turnID;
       break;
       case 5: board[1][1] = turnID;
       break;
       case 6: board[1][2] = turnID;
       break;
       case 7: board[2][0] = turnID;
       break;
       case 8: board[2][1] = turnID;
       break;
       case 9: board[2][2] = turnID;
    }
    return;
}

int GetInput()
{
    int input;
    cout << "Enter position to play: ";
    cin >> input;
    return input;
}

int CheckInput(int input, char turnID)
{
    if(input > 9 or input < 1)
    {
        if(turnID == PLAYERCHAR) cout << "Input out of Range, input a correct grid to play." << endl;
        cin.clear();
        cin.ignore(80, '\n');
        return -5;
    }
    else return -6;
}

void Display(char board[3][3])
{
    cout << board[0][0] << '|' << board[0][1] << '|' << board[0][2] << endl;
    cout << '-' << '+' << '-' << '+' << '-' << endl;
    cout << board[1][0] << '|' << board[1][1] << '|' << board[1][2] << endl;
    cout << '-' << '+' << '-' << '+' << '-' << endl;
    cout << board[2][0] << '|' << board[2][1] << '|' << board[2][2] << endl;
    cout << endl;
}

void DefaultDisplay()
{
    cout << "1" << '|' << "2" << '|' << "3" << endl;
    cout << '-' << '+' << '-' << '+' << '-' << endl;
    cout << "4" << '|' << "5" << '|' << "6" << endl;
    cout << '-' << '+' << '-' << '+' << '-' << endl;
    cout << "7" << '|' << "8" << '|' << "9" << endl;
    cout << endl;
}
