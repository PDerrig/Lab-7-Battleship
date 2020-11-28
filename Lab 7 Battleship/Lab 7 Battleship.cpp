/*
Preston Derrig
C++ Fall 2020
Due: December 2nd
Lab #7
This program allows a player to play the game battleship against the computer
*/

#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void resetboard(int playerb[][10], int computerb[][10]);
// This function sets all points in both arrays equal to the value of a water space

void playerboard(int boardplayer[][10]);
//This function prints out the player's board to the screen with each value on the array having the correct symbol

void computerboard(int boardcomputer[][10]);
// This function prints the computer's board to the screen

void playerplaceships(int playerbo[][10]);
// In this funtion the player goes through and place each of their ships

void placementerrormessages(int& row, int& column, int playerb[][10]);
// This funtion checks the placement of the players ship and makes sure it's valid and if not tells the player to change 
// their placement of that ship

void availabledirectionmessages(int playerrow, int playercolumn, int playerlength, int boardofplayer[][10]);
// This function sees where the player place the first point of the ships and checks which of the four directions 
// the ship can go and that tells the player which directions are available

void directionofplayerships(int playerbored[][10], char shipdirection, int rownumber, int columnnumber, int lengthship);
// In this functio, the player choose which of the available direction they want to place their ship and then this function,
// adds the ships to the array and makes sure the ship is the right length

void computerplaceships(int computerbo[][10]);
// This function, a random point on the array is assigned as the placement for the computer's ships

void directionofcomputerships(int computerbored[][10], int Comlength, int ComRow, int ComColumn);
// This function a random number is genereated to assign which of the four direction the computer's ship will go

void Firing(int computersboard[][10], int playersboard[][10], int& wins, int& losses);
// In This function, the player and computer take their turns firing at each other and it checks for when the game is over

void EndGame(int pwins, int plosses, bool& ContinuePlay);
// This function asks the player if they would like ot play again and if not it ends the program


int main()
{
    int PlayerBoard[10][10];
    int ComputerBoard[10][10];

    bool WantsToPlay = true;

    int playerwins = 0;
    int playerlosses = 0;


    resetboard(PlayerBoard, ComputerBoard);

    while (WantsToPlay == true)
    {
        playerplaceships(PlayerBoard);
        computerplaceships(ComputerBoard);
        Firing(ComputerBoard, PlayerBoard, playerwins, playerlosses);
        EndGame(playerwins, playerlosses, WantsToPlay);
        resetboard(PlayerBoard, ComputerBoard);
    }
    return 0;
}

void resetboard(int playerb[][10], int computerb[][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            playerb[i][j] = 0;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            computerb[i][j] = 0;
        }
    }

}

void playerboard(int boardplayer[][10])
{
    int z = 0;
    cout << "    ";
    while (z < 10)
    {
        cout << 1 + z << "  ";
        z++;
    }
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        if (i < 9)
        {
            cout << 1 + i << "   ";
        }
        if (i == 9)
        {
            cout << "10  ";
        }
        for (int j = 0; j < 10; j++)
        {
            if (boardplayer[i][j] == 0)
                cout << "~  ";
            if (boardplayer[i][j] == 1)
                cout << "#  ";
            if (boardplayer[i][j] == 2)
                cout << "M  ";
            if (boardplayer[i][j] == 3)
                cout << "H  ";
        }
        cout << endl;
    }
    cout << endl;
}

void computerboard(int boardcomputer[][10])
{
    int z = 0;
    cout << "    ";
    while (z < 10)
    {
        cout << 1 + z << "  ";
        z++;
    }
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        if (i < 9)
        {
            cout << 1 + i << "   ";
        }
        if (i == 9)
        {
            cout << "10  ";
        }
        for (int j = 0; j < 10; j++)
        {
            if (boardcomputer[i][j] < 2)
                cout << "~  ";
            if (boardcomputer[i][j] == 2)
                cout << "M  ";
            if (boardcomputer[i][j] == 3)
                cout << "H  ";
        }
        cout << endl;
    }
    cout << endl;
}

void playerplaceships(int playerbo[][10])
{
    int row;
    int column;
    char direction;
    int boatlength = 5;
    playerboard(playerbo);

    cout << endl << "To start the game, please place your Carrier, which is five spaces long." << endl <<
        "First, choose which row you want to start your Carrier.  ";

    cin >> row;

    cout << "Now, which column do you want to place your Carrier.  ";

    cin >> column;

    placementerrormessages(row, column, playerbo);

    playerbo[row - 1][column - 1] = 1;
    playerboard(playerbo);

    availabledirectionmessages(row, column, boatlength, playerbo);

    cin >> direction;
    directionofplayerships(playerbo, direction, row, column, boatlength);

    playerboard(playerbo);
    boatlength--;

    cout << endl << "The next piece to be placed is the Battleship. This ship is four spaces long." << endl <<
        "First, choose which row you want to start your Battleship.  ";

    cin >> row;

    cout << "Now, which column do you want to place your Battleship.  ";

    cin >> column;

    placementerrormessages(row, column, playerbo);

    playerbo[row - 1][column - 1] = 1;
    playerboard(playerbo);

    availabledirectionmessages(row, column, boatlength, playerbo);

    cin >> direction;
    directionofplayerships(playerbo, direction, row, column, boatlength);

    playerboard(playerbo);
    boatlength--;

    cout << endl << "Next is the three space, Cruiser." << endl << "Choose which row to start your Cruiser.  ";

    cin >> row;

    cout << "Now, which column do you want to place your Cruiser.  ";

    cin >> column;

    placementerrormessages(row, column, playerbo);

    playerbo[row - 1][column - 1] = 1;
    playerboard(playerbo);

    availabledirectionmessages(row, column, boatlength, playerbo);

    cin >> direction;
    directionofplayerships(playerbo, direction, row, column, boatlength);

    playerboard(playerbo);

    cout << endl << "The Submarine is the next ship you need to place. The sub is three space long as well." << endl
        << "Pick the row where you want to start the submarine.   ";

    cin >> row;

    cout << "Now, which column do you want to place your Battleship.  ";

    cin >> column;

    placementerrormessages(row, column, playerbo);

    playerbo[row - 1][column - 1] = 1;
    playerboard(playerbo);

    availabledirectionmessages(row, column, boatlength, playerbo);

    cin >> direction;
    directionofplayerships(playerbo, direction, row, column, boatlength);

    playerboard(playerbo);
    boatlength--;

    cout << endl << "The final ship that needs to be placed is the two space long Destroyers." << endl <<
        "Chose the row where your Destroyer begins.   ";

    cin >> row;

    cout << "Now, which column do you want to place your Battleship.  ";

    cin >> column;

    placementerrormessages(row, column, playerbo);

    playerbo[row - 1][column - 1] = 1;
    playerboard(playerbo);

    availabledirectionmessages(row, column, boatlength, playerbo);

    cin >> direction;
    directionofplayerships(playerbo, direction, row, column, boatlength);

    playerboard(playerbo);
}

void placementerrormessages(int& row, int& column, int playerb[][10])
{
    if (row > 10)
    {
        cout << " The row you enter is invalid. Please enter a valid row.  ";
        cin >> row;
    }
    if (column > 10)
    {
        cout << "The column you enterer is invalid. Please enter a valid column.  ";
        cin >> column;
    }
    if (playerb[row - 1][column - 1] == 1)
    {
        cout << "The coordinate you typed in has already been used. Please enter new row and column" << endl;
        cout << "First a new row.  ";
        cin >> row;
        cout << "Now enter your new column.  ";
        cin >> column;
    }
}

void availabledirectionmessages(int playerrow, int playercolumn, int playerlength, int boardofplayer[][10])
{

    if (playercolumn - playerlength >= 0 && boardofplayer[playerrow - 1][playercolumn - 2] == 0 && boardofplayer[playerrow - 1][playercolumn - 3] == 0
        && boardofplayer[playerrow - 1][playercolumn - 4] == 0)
        cout << "You can place your Carrier horizontally to the left, to do so enter L.\n";
    if (playercolumn - 1 + playerlength <= 10 && boardofplayer[playerrow - 1][playercolumn] == 0 && boardofplayer[playerrow - 1][playercolumn + 1] == 0
        && boardofplayer[playerrow - 1][playercolumn + 2] == 0)
        cout << "You can place your Carrier horizontally to the right, to do so enter R.\n";
    if (playerrow - playerlength >= 0 && boardofplayer[playerrow - 2][playercolumn - 1] == 0 && boardofplayer[playerrow - 3][playercolumn - 1] == 0
        && boardofplayer[playerrow - 4][playercolumn - 1] == 0)
        cout << "You can place your Carrier veritcally up, to do so enter U.\n";
    if (playerrow - 1 + playerlength <= 10 && boardofplayer[playerrow][playercolumn - 1] == 0 && boardofplayer[playerrow + 1][playercolumn - 1] == 0
        && boardofplayer[playerrow + 2][playercolumn - 1] == 0)
        cout << "You can place your Carrier veritcally down, to do so enter D.\n";
}

void directionofplayerships(int playerbored[][10], char shipdirection, int rownumber, int columnnumber, int lengthship)
{

    int i = 1;
    switch (shipdirection)
    {
    case 'U':
        while (i <= lengthship)
        {
            playerbored[rownumber - i][columnnumber - 1] = 1;
            i++;
        }
        break;
    case 'D':
        while (i < lengthship)
        {
            playerbored[rownumber + i - 1][columnnumber - 1] = 1;
            i++;
        }
        break;
    case 'R':
        while (i < lengthship)
        {
            playerbored[rownumber - 1][columnnumber + i - 1] = 1;
            i++;
        }
        break;
    case 'L':
        while (i <= lengthship)
        {
            playerbored[rownumber - 1][columnnumber - i] = 1;
            i++;
        }
        break;
    case 'u':
        while (i <= lengthship)
        {
            playerbored[rownumber - i][columnnumber - 1] = 1;
            i++;
        }
        break;
    case 'd':
        while (i < lengthship)
        {
            playerbored[rownumber + i - 1][columnnumber - 1] = 1;
            i++;
        }
        break;
    case 'r':
        while (i < lengthship)
        {
            playerbored[rownumber - 1][columnnumber + i - 1] = 1;
            i++;
        }
        break;
    case 'l':
        while (i <= lengthship)
        {
            playerbored[rownumber - 1][columnnumber - i] = 1;
            i++;
        }
        break;
    default: cout << "An error has occured.";
        break;
    }

}

void computerplaceships(int computerbo[][10])
{
    int computerrow;
    int computercolumn;
    int ComShipLength = 5;
    srand(time(NULL));

    computerrow = rand() % 10 + 1;
    computercolumn = rand() % 10 + 1;

    directionofcomputerships(computerbo, ComShipLength, computerrow, computercolumn);


    ComShipLength--;


    computerrow = rand() % 10;
    computercolumn = rand() % 10;

    directionofcomputerships(computerbo, ComShipLength, computerrow, computercolumn);


    ComShipLength--;


    computerrow = rand() % 10;
    computercolumn = rand() % 10;

    directionofcomputerships(computerbo, ComShipLength, computerrow, computercolumn);



    computerrow = rand() % 10;
    computercolumn = rand() % 10;

    directionofcomputerships(computerbo, ComShipLength, computerrow, computercolumn);

    ComShipLength--;



    computerrow = rand() % 10;
    computercolumn = rand() % 10;

    directionofcomputerships(computerbo, ComShipLength, computerrow, computercolumn);

}

void directionofcomputerships(int computerbored[][10], int Comlength, int ComRow, int ComColumn)
{
    int z = 0;
    int success = 0;
    int fails = 0;
    int comDirection = rand() % 4 + 1;


    do
        switch (comDirection)
        {
        case 1:
            if (ComColumn - Comlength <= 1 || computerbored[ComRow - 1][ComColumn - 1] == 1 || computerbored[ComRow - 1][ComColumn - 2] == 1
                || computerbored[ComRow - 1][ComColumn - 3] == 1 || computerbored[ComRow - 1][ComColumn - 4] == 1)
            {
                comDirection++;
            }
            else
            {
                while (z < Comlength)
                {
                    computerbored[ComRow - 1][ComColumn - 1 - z] = 1;
                    z++;
                    success++;
                }
            }
            break;
        case 2:
            if (ComColumn + Comlength > 9 || computerbored[ComRow - 1][ComColumn - 1] == 1 || computerbored[ComRow - 1][ComColumn] == 1
                || computerbored[ComRow - 1][ComColumn + 1] == 1 || computerbored[ComRow - 1][ComColumn + 2] == 1)
            {
                comDirection++;
            }
            else
            {
                while (z < Comlength)
                {
                    computerbored[ComRow - 1][ComColumn - 1 + z] = 1;
                    z++;
                    success++;
                }
            }
            break;
        case 3:
            if (ComRow - Comlength <= 3 || computerbored[ComRow - 1][ComColumn - 1] == 1 || computerbored[ComRow - 2][ComColumn - 1] == 1
                || computerbored[ComRow - 3][ComColumn - 1] == 1 || computerbored[ComRow - 4][ComColumn - 1] == 1)
            {
                comDirection++;
            }
            else
                while (z < Comlength)
                {
                    computerbored[ComRow - 1 - z][ComColumn - 1] = 1;
                    z++;
                    success++;
                }
            break;
        case 4:
            if (ComRow + Comlength > 9 || computerbored[ComRow - 1][ComColumn - 1] == 1 || computerbored[ComRow][ComColumn - 1] == 1
                || computerbored[ComRow + 1][ComColumn - 1] == 1 || computerbored[ComRow + 2][ComColumn - 1] == 1)
            {
                comDirection = 1;
                fails++;
                if (fails >= 5)
                {
                    ComRow = rand() % 10 + 1;
                    ComColumn = rand() % 10 + 1;
                    fails = 0;
                    continue;
                }
            }
            else
                while (z < Comlength)
                {
                    computerbored[ComRow - 1 + z][ComColumn - 1] = 1;
                    z++;
                    success++;
                }
            break;
        default: cout << "error";
            break;

        }
    while (success < 1);
}

void Firing(int computersboard[][10], int playersboard[][10], int& wins, int& losses)
{
    bool gameplay = true;
    int computerfirerow;
    int computerfirecolumn;
    int playerfirerow;
    int playerfirecolumn;
    int playeroptions;
    bool playerfired = false;
    bool computerfired = false;
    int playerhits = 0;
    int computerhits = 0;

    cout << "Now that the boards are set up, you and the computer will take turns firing at each others ship.";



    do
    {
        cout << "It is now your turn." << endl << "You can start your shots by pressing 1." << endl
            << "You can look at your board by pressing 2." << endl << "You can also choose to surrender by pressing 3.  ";

        cin >> playeroptions;

        do
        {
            switch (playeroptions)
            {
            case 1:
                cout << "\033[2J\033[1;1H";
                computerboard(computersboard);
                cout << "First choose which row you want to fire at.  ";
                cin >> playerfirerow;
                if (playerfirerow > 10)
                {
                    cout << "The row you entered isn't valid, please enter a new valid row to fire at.  ";
                    cin >> playerfirerow;
                }
                cout << "Now Choose which column you want to fire at.   ";
                cin >> playerfirecolumn;
                if (playerfirecolumn > 10)
                {
                    cout << "The column you entered isn't valid, please enter a new valid row to fire at.  ";
                    cin >> playerfirecolumn;
                }


                if (computersboard[playerfirerow - 1][playerfirecolumn - 1] == 0)
                {
                    cout << "Miss!\n\n\n\n";
                    computersboard[playerfirerow - 1][playerfirecolumn - 1] += 2;
                    playerfired = true;
                }
                if (computersboard[playerfirerow - 1][playerfirecolumn - 1] == 1)
                {
                    cout << "Hit!\n\n\n\n";
                    computersboard[playerfirerow - 1][playerfirecolumn - 1] += 2;
                    playerfired = true;
                    playerhits++;
                }
                computerboard(computersboard);
                break;
            case 2: playerboard(playersboard);
                cout << "Now to fire at the computer press 1." << endl << "To surrender press 3. ";
                cin >> playeroptions;
                break;
            case 3:gameplay = false;
                playerfired = true;
                break;
            default: cout << "The option you input isn't valid. Please input a valid option."
                << "You can start your shots by pressing 1." << endl
                << "You can look at your board by pressing 2." << endl
                << "You can also choose to surrender by pressing 3.  ";
                cin >> playeroptions;
                break;
            }
        } while (playerfired == false);


        playerfired = false;


        computerfirerow = rand() % 10 + 1;
        computerfirecolumn = rand() % 10 + 1;

        do
        {
            if (playersboard[computerfirerow - 1][computerfirecolumn - 1] == 0)
            {
                cout << "The Computer fired at row " << computerfirerow << ",and column " << computerfirecolumn << " and Missed!\n\n";
                playersboard[computerfirerow - 1][computerfirecolumn - 1] += 2;
                computerfired = true;
            }
            if (playersboard[computerfirerow - 1][computerfirecolumn - 1] == 1)
            {
                cout << "The Computer fired at row " << computerfirerow << ",and column " << computerfirecolumn << " and Hit!\n\n";
                playersboard[computerfirerow - 1][computerfirecolumn - 1] += 2;
                computerfired = true;
                computerhits++;
            }
            if (playersboard[computerfirerow - 1][computerfirecolumn - 1] >= 2)
            {
                computerfirerow = rand() % 10 + 1;
                computerfirecolumn = rand() % 10 + 1;
            }
        } while (computerfired == false);

        if (playerhits == 15)
        {
            cout << "*******You have won the game********\n\n\n";
            gameplay = false;
            wins++;
        }
        if (computerhits == 15)
        {
            cout << "*******You have lost the game********\n\n\n";
            gameplay = false;
            losses++;
        }

    } while (gameplay == true);
}

void EndGame(int pwins, int plosses, bool& ContinuePlay)
{
    int endgameoptions;
    cout << "The game is over.\nPress 1 to play again.\nPress 2 to finish playing the game. ";

    cin >> endgameoptions;

    switch (endgameoptions)
    {
    case 1: cout << "Okay. Let's play again.\n\n\n\n\n\n\n\n";
        break;
    case 2: cout << "Thank you for playing." << endl << "You won " << pwins << " games." << endl <<
        "You lost " << plosses << "games.";
        ContinuePlay = false;
        break;
    default:
        break;
    }

}
