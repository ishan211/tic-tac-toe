#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function prototypes
void displayBoard(char board[3][3]);
bool checkWin(char board[3][3], char player);
bool checkDraw(char board[3][3]);
void playerMove(char board[3][3], vector<int>& x, vector<int>& y, vector<int>& x_p, vector<int>& y_p);
void cpuMove(char board[3][3], vector<int>& x, vector<int>& y, vector<int>& x_c, vector<int>& y_c);

int main() {
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    // all possible positions stored in vectors
    vector<int> x = {0, 0, 0, 1, 1, 1, 2, 2, 2};
    vector<int> y = {0, 1, 2, 0, 1, 2, 0, 1, 2};

    // vectors to write the position for player and cpu 
    vector<int> x_p, y_p; // Player 
    vector<int> x_c, y_c; // CPU 

    char currentPlayer = 'X'; // player is x, cpu is o
    bool gameWon = false; //boolean var for if game is won or drawn, initially set as false
    bool gameDraw = false;

    srand(time(0)); // randomly generate cpu

    while (!gameWon && !gameDraw) {
        displayBoard(board);

        if (currentPlayer == 'X') {
            playerMove(board, x, y, x_p, y_p); // Player move
            gameWon = checkWin(board, currentPlayer);
            currentPlayer = 'O'; // Switch to CPU
        } else {
            cpuMove(board, x, y, x_c, y_c); // CPU move
            gameWon = checkWin(board, 'O');
            currentPlayer = 'X'; // Switch to Player
        }

        gameDraw = checkDraw(board);
    }

    displayBoard(board); // Show the final board state

    if (gameWon) {
        if (currentPlayer == 'O') {
            cout << "Player wins!" << endl;
        } else {
            cout << "CPU wins!" << endl;
        }
    } else if (gameDraw) {
        cout << "It's a draw!" << endl;
    }

    return 0;
}

// Display the board
void displayBoard(char board[3][3]) {
    cout << "-------------" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << endl << "-------------" << endl;
    }
}

// Player move function
void playerMove(char board[3][3], vector<int>& x, vector<int>& y, vector<int>& x_p, vector<int>& y_p) {
    int choice;
    cout << "Enter the number of the cell where you'd like to place X: ";
    cin >> choice;

    int xi = (choice - 1) / 3; // Get the x position
    int yi = (choice - 1) % 3; // Get the y position

    if (board[xi][yi] != 'X' && board[xi][yi] != 'O') {
        board[xi][yi] = 'X'; // Place player's move
        x_p.push_back(xi); // Store player move in x_p, y_p
        y_p.push_back(yi);

        // Remove the position from available positions
        for (int i = 0; i < x.size(); i++) {
            if (x[i] == xi && y[i] == yi) {
                x.erase(x.begin() + i);
                y.erase(y.begin() + i);
                break;
            }
        }
    } else {
        cout << "Invalid move! Try again." << endl;
        playerMove(board, x, y, x_p, y_p); // Re-prompt for move
    }
}

// CPU move function (random selection from available positions)
void cpuMove(char board[3][3], vector<int>& x, vector<int>& y, vector<int>& x_c, vector<int>& y_c) {
    if (x.empty()) return; // No moves left

    int randIndex = rand() % x.size(); // Pick a random available position
    int xi = x[randIndex];
    int yi = y[randIndex];

    board[xi][yi] = 'O'; // Place CPU's move
    x_c.push_back(xi); // Store CPU move in x_c, y_c
    y_c.push_back(yi);

    // Remove the position from available positions
    x.erase(x.begin() + randIndex);
    y.erase(y.begin() + randIndex);
}

// Check if the current player has won
bool checkWin(char board[3][3], char player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || // Rows
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {  // Columns
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || // Diagonal 1
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {  // Diagonal 2
        return true;
    }
    return false;
}

// Check if the game is a draw (no empty spaces left)
bool checkDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false; // Empty spot found
            }
        }
    }
    return true; // No empty spots, it's a draw
}
