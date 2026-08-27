#include<iostream>
#include<string>

using namespace std;

char board[9] = {
    '1', '2', '3',
    '4', '5', '6',
    '7', '8', '9'
};

int playerXwins = 0;
int playerOwins = 0;
int draws = 0;

// Function prototypes
void printCell(char cell);
void clearScreen();
void displayTurn(string playerName, char player);
void displayBoard();
void resetBoard();
void playerMove(char player, string playerName);
bool checkWin(char player);
bool checkDraw();
void displayScore(string playerXname, string playerOname);
void displayRules();
void displayWinner(string playerName, char player);
void displayDraw();
bool askPlayAgain();
void startGame(string playerXName, string playerOName);
string getPlayerName(char player);
int getMenuChoice();
void displayWelcome();
bool isSameName(string playerXName, string playerOName);
void exitGame();

// عرض لوحة اللعبة بشكل منظم وإظهار أرقام الخانات أو X و O
void displayBoard()
{
    cout << "\n================================\n";
    cout << "        TIC TAC TOE\n";
    cout << "================================\n";

    cout << "     ";
    printCell(board[0]);
    cout << " | ";
    printCell(board[1]);
    cout << " | ";
    printCell(board[2]);
    cout << endl;

    cout << "    ---------\n";

    cout << "     ";
    printCell(board[3]);
    cout << " | ";
    printCell(board[4]);
    cout << " | ";
    printCell(board[5]);
    cout << endl;

    cout << "    ---------\n";

    cout << "     ";
    printCell(board[6]);
    cout << " | ";
    printCell(board[7]);
    cout << " | ";
    printCell(board[8]);
    cout << endl;
}

// إعادة لوحة اللعبة إلى حالتها الأصلية قبل بداية مباراة جديدة
void resetBoard()
{
    board[0] = '1';
    board[1] = '2';
    board[2] = '3';
    board[3] = '4';
    board[4] = '5';
    board[5] = '6';
    board[6] = '7';
    board[7] = '8';
    board[8] = '9';
}

// أخذ اختيار اللاعب والتأكد أن الإدخال صحيح والخانة غير محجوزة
void playerMove(char player, string playerName)
{
    int choice;

    while(true)
    {
        cout << playerName << " (" << player << ") choose a number: ";
        cin >> choice;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input! Please enter a number.\n";

            continue;
        }

        if(choice < 1 || choice > 9)
        {
            cout << "Invalid choice! choose a number from 1 to 9.\n";
        }

        else if(board[choice - 1] == 'X' ||
                board[choice - 1] == 'O')
        {
            cout << "This place is already taken!\n";
        }

        else
        {
            board[choice - 1] = player;
            break;
        }
    }
}

// التحقق إذا كان اللاعب الحالي قد حقق ثلاثة رموز متتالية
bool checkWin(char player)
{
    // Rows
    if(board[0] == player && board[1] == player && board[2] == player)
    {
        return true;
    }

    if(board[3] == player && board[4] == player && board[5] == player)
    {
        return true;
    }

    if(board[6] == player && board[7] == player && board[8] == player)
    {
        return true;
    }

    // Columns
    if(board[0] == player && board[3] == player && board[6] == player)
    {
        return true;
    }

    if(board[1] == player && board[4] == player && board[7] == player)
    {
        return true;
    }

    if(board[2] == player && board[5] == player && board[8] == player)
    {
        return true;
    }

    // Diagonals
    if(board[0] == player && board[4] == player && board[8] == player)
    {
        return true;
    }

    if(board[2] == player && board[4] == player && board[6] == player)
    {
        return true;
    }

    return false;
}

// التحقق إذا كانت كل الخانات ممتلئة ولم يفز أي لاعب
bool checkDraw()
{
    for(int i = 0; i < 9; i++)
    {
        if(board[i] >= '1' && board[i] <= '9')
        {
            return false;
        }
    }

    return true;
}

// عرض نتيجة المباريات وعدد مرات الفوز والتعادل لكل لاعب
void displayScore(string playerXname, string playerOname)
{
    cout << "\n========== SCORE ==========\n";
    cout << playerXname << " (X): " << playerXwins << endl;
    cout << playerOname << " (O): " << playerOwins << endl;
    cout << "Draws: " << draws << endl;
    cout << "===========================\n\n";
}

// عرض قوانين لعبة Tic Tac Toe للمستخدم
void displayRules()
{
    cout << "\n========== RULES ==========\n";

    cout << "1. The game is played on a 3x3 board.\n";
    cout << "2. Player X goes first.\n";
    cout << "3. Players take turns choosing a number from 1 to 9.\n";
    cout << "4. The first player to get 3 symbols in a row wins.\n";
    cout << "5. A row can be horizontal, vertical, or diagonal.\n";
    cout << "6. If all spaces are filled and nobody wins, it's a draw.\n";

    cout << "===========================\n\n";
}

// عرض رسالة فوز اللاعب مع اسمه والرمز الخاص به
void displayWinner(string playerName, char player)
{
    cout << "\n========================\n";
    cout << playerName << " (" << player << ") wins!\n";
    cout << "========================\n";
}

// عرض رسالة عند انتهاء اللعبة بالتعادل
void displayDraw()
{
    cout << "\n========================\n";
    cout << "          DRAW!\n";
    cout << "========================\n";
}

// سؤال اللاعبين إذا كانوا يريدون بدء مباراة جديدة
bool askPlayAgain()
{
    char choice;

    while(true)
    {
        cout << "Do you want to play again? (Y/N): ";
        cin >> choice;

        if(choice == 'Y' || choice == 'y')
        {
            return true;
        }

        else if(choice == 'N' || choice == 'n')
        {
            return false;
        }

        else
        {
            cout << "Invalid choice! Please enter Y or N.\n";
        }
    }
}

// تشغيل المباراة والتحكم في الأدوار والفوز والتعادل وإعادة اللعب
void startGame(string playerXName, string playerOName)
{
    do
    {
        clearScreen();

        resetBoard();

        for(int i = 0; i < 9; i++)
        {
            displayBoard();

            if(i % 2 == 0)
            {
                displayTurn(playerXName, 'X');

                playerMove('X', playerXName);

                if(checkWin('X'))
                {
                    displayBoard();

                    displayWinner(playerXName, 'X');

                    playerXwins++;

                    break;
                }
            }

            else
            {
                displayTurn(playerOName, 'O');

                playerMove('O', playerOName);

                if(checkWin('O'))
                {
                    displayBoard();

                    displayWinner(playerOName, 'O');

                    playerOwins++;

                    break;
                }
            }

            if(checkDraw())
            {
                displayBoard();

                displayDraw();

                draws++;

                break;
            }
        }

        displayScore(playerXName, playerOName);

    } while(askPlayAgain());
}

// أخذ اسم اللاعب والتأكد أن الاسم ليس فارغًا
string getPlayerName(char player)
{
    string name;

    while(true)
    {
        cout << "Enter Player " << player << " name: ";
        getline(cin, name);

        if(name.empty())
        {
            cout << "Name cannot be empty!\n";
        }

        else
        {
            return name;
        }
    }
}

// أخذ اختيار المستخدم من القائمة والتأكد أنه رقم من 1 إلى 4
int getMenuChoice()
{
    int choice;

    while(true)
    {
        cout << "Choose an option: ";
        cin >> choice;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input! Please enter a number.\n";

            continue;
        }

        if(choice >= 1 && choice <= 4)
        {
            return choice;
        }

        cout << "Invalid option! Choose 1, 2, 3 or 4.\n";
    }
}

// عرض شاشة الترحيب باللاعبين عند تشغيل البرنامج
void displayWelcome()
{
    cout << "\n================================\n";
    cout << "          WELCOME TO\n";
    cout << "         TIC TAC TOE\n";
    cout << "================================\n";

    cout << "Get ready to play!\n\n";
}

// مقارنة اسم اللاعب X باسم اللاعب O للتأكد أنهما مختلفان
bool isSameName(string playerXName, string playerOName)
{
    return playerXName == playerOName;
}

// مسح شاشة الـ Console
void clearScreen()
{
    system("cls");
}

// طباعة الخانة مع إعطاء X و O ألوان مختلفة
void printCell(char cell)
{
    if(cell == 'X')
    {
        cout << "\033[31m" << cell << "\033[0m";
    }

    else if(cell == 'O')
    {
        cout << "\033[32m" << cell << "\033[0m";
    }

    else
    {
        cout << cell;
    }
}

// عرض اسم اللاعب الذي عليه الدور حاليًا
void displayTurn(string playerName, char player)
{
    cout << "\n--------------------------------\n";
    cout << "Turn: " << playerName << " (" << player << ")\n";
    cout << "--------------------------------\n";
}

// عرض رسالة الخروج من اللعبة وإيقاف الشاشة حتى يضغط المستخدم
void exitGame()
{
    cout << "\n================================\n";
    cout << "       Thanks For Playing!\n";
    cout << "================================\n";

    system("pause");
}

// الدالة الرئيسية التي تبدأ البرنامج وتتحكم في القائمة الرئيسية
int main()
{
    int choice;

    string playerXName;
    string playerOName;

    displayWelcome();

    playerXName = getPlayerName('X');
    playerOName = getPlayerName('O');

    while(isSameName(playerXName, playerOName))
    {
        cout << "\nPlayers cannot have the same name!\n";

        playerOName = getPlayerName('O');
    }

    while(true)
    {
        clearScreen();

        cout << "\n========================\n";
        cout << "       TIC TAC TOE\n";
        cout << "========================\n";
        cout << "1. Start Game\n";
        cout << "2. View Score\n";
        cout << "3. Rules\n";
        cout << "4. Exit\n";
        cout << "========================\n";

        choice = getMenuChoice();

        if(choice == 1)
        {
            startGame(playerXName, playerOName);
        }

        else if(choice == 2)
        {
            displayScore(playerXName, playerOName);

            system("pause");
        }

        else if(choice == 3)
        {
            displayRules();

            system("pause");
        }

        else if(choice == 4)
        {
            exitGame();
            break;
        }
    }

    return 0;
}