#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

void DrawBoard(char *spaces)
{
    std::cout << "\n"
              << std::endl;
    std::cout << "1    |2    |3    " << std::endl;
    std::cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << "  " << std::endl;
    std::cout << "_____|_____|_____" << std::endl;
    std::cout << "4    |5    |6    " << std::endl;
    std::cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  " << std::endl;
    std::cout << "_____|_____|_____" << std::endl;
    std::cout << "7    |8    |9    " << std::endl;
    std::cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  " << std::endl;
    std::cout << "     |     |     " << std::endl;
}

void PlayerMove(char *spaces, char player)
{
    int number;
    while (true)
    {
        std::cout << "\nEnter a spot to place the marker (1-9): ";
        std::cin >> number;
        number--;
        if (number >= 0 && number < 9 && spaces[number] == ' ')
        {
            spaces[number] = player;
            break;
        }
        else
        {
            std::cout << "Invalid input or spot already taken. Please try again.\n";
        }
    };
}

void ComputerMove(char *spaces, char secondPlayer)
{
    int number;
    srand(time(0));

    while (true)
    {
        number = rand() % 9;
        if (spaces[number] == ' ')
        {
            spaces[number] = secondPlayer;
            break;
        }
    }
}

void Wait(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool CheckWinner(char *spaces, char player, char secondPlayer, int twoPlayers)
{
    const int winningCombinations[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}};
    for (int i = 0; i < 8; ++i)
    {
        int a = winningCombinations[i][0];
        int b = winningCombinations[i][1];
        int c = winningCombinations[i][2];

        if ((spaces[a] != ' ') && (spaces[a] == spaces[b]) && (spaces[b] == spaces[c]))
        {
            if (spaces[a] == player)
            {
                std::cout << "YOU WIN!\n";
            }
            else if (spaces[a] == secondPlayer)
            {
                if (twoPlayers == 1)
                {
                    std::cout << "THE SECOND PLAYER WIN!\n";
                }
                else if (twoPlayers == 0)
                {
                    std::cout << "YOU LOST!\n";
                }
            }
            return true;
        }
    }
    return false;
}

bool CheckTie(char *spaces)
{
    for (int i = 0; i < 9; i++)
    {
        if (spaces[i] == ' ')
        {
            return false;
        }
    }
    std::cout << "It is a Tie!\n"
              << std::endl;
    return true;
}

int TwoPlayers()
{
    int twoPlayers;

    std::cout << "Play with Computer. Press 0" << std::endl;
    std::cout << "Play with Friend. Press 1" << std::endl;

    while (true)
    {
        std::cin >> twoPlayers;
        if (twoPlayers == 0)
        {
            std::cout << "Play with Computer\n"
                      << std::endl;
            break;
        }
        else if (twoPlayers == 1)
        {
            std::cout << "Play with Friend\n"
                      << std::endl;
            break;
        }
        else
        {
            std::cout << "Invalid input. Please try again.\n"
                      << std::endl;
        }
    }
    return twoPlayers;
}

void GameLoop(int twoPlayers)
{
    char spaces[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
    char player = 'X';
    char secondPlayer = 'O';
    bool running = true;

    DrawBoard(spaces);

    while (running)
    {
        PlayerMove(spaces, player);
        DrawBoard(spaces);
        if (CheckWinner(spaces, player, secondPlayer, twoPlayers))
        {
            running = false;
            break;
        }
        else if (CheckTie(spaces))
        {
            running = false;
            break;
        }

        if (twoPlayers == 0)
        {
            std::cout << "\nComputer is thinking" << std::endl;
            Wait(2000);
            ComputerMove(spaces, secondPlayer);
        }
        else if (twoPlayers == 1)
        {
            PlayerMove(spaces, secondPlayer);
        }
        DrawBoard(spaces);
        if (CheckWinner(spaces, player, secondPlayer, twoPlayers)) // Corrected the player parameter to secondPlayer
        {
            running = false;
            break;
        }
        else if (CheckTie(spaces))
        {
            running = false;
            break;
        }
    }
}

int main()
{
    while (true)
    {
        int twoPlayers = TwoPlayers();
        GameLoop(twoPlayers);

        char choice;
        Wait(1000);
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> choice;

        if ((choice == 'N') || (choice == 'n'))
        {
            std::cout << "Thank you for playing" << std::endl;
            break;
        }
        else if ((choice == 'Y') || (choice == 'y'))
        {
            std::cout << "The game is starting" << std::endl;
            Wait(2000);
            continue;
        }
        else
        {
            std::cout << "Invalid input. Please try again.\n"
                      << std::endl;
        }
    }

    std::cin.get();
    std::cin.get();
}