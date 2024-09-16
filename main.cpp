#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function prototypes
void displayBoard(char board[3][3]); // disp board
bool checkWin(char board[3][3], char player); // check win
bool checkDraw(char board[3][3]); // check draw
void playerMove(char board[3][3], vector<int>& x, vector<int>& y, vector<int>& x_p, vector<int>& y_p); // player move
void cpuMove(char board[3][3], vector<int>& x, vector<int>& y, vector<int>& x_c, vector<int>& y_c); // cpu move

int main() {
    // Init board
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    // vec for pos board
    vector<int> x = {0, 0, 0, 1, 1, 1, 2, 2, 2};
    vector<int> y = {0, 1, 2, 0, 1, 2, 0, 1, 2};

    // vec for player and cpu move
    vector<int> x_p, y_p;    
    vector<int> x_c, y_c;

    char currentPlayer = 'X';
    bool gameWon = false; // bool for win
    bool gameDraw = false; // bool for draw

    srand(time(0)); // rng for cpu move

    // loop until win || draw
    while (!gameWon && !gameDraw) {
        displayBoard(board); // disp current board

        if (currentPlayer == 'X') {
            playerMove(board, x, y, x_p, y_p); // player move
            gameWon = checkWin(board, currentPlayer); // check if player won
            currentPlayer = 'O'; // cpu turn
        } else {
            cpuMove(board, x, y, x_c, y_c); // cpu move
            gameWon = checkWin(board, 'O'); // Check if cpu won
            currentPlayer = 'X'; // player turn
        }

        gameDraw = checkDraw(board); // Check if draw
    }

    displayBoard(board); // disp board

    // give game(res)
    if (gameWon) {
        if (currentPlayer == 'O') { // If the currentPlayer 'O' player 'X' won
            cout << "Player wins!" << endl;
        } else { // otherwise cpu won
            cout << "CPU wins!" << endl;
        }
    } else if (gameDraw) {
        cout << "It's a draw!" << endl; // If gameDraw is true then its a draw
    }

    return 0; // Exit with 0
}

// disp current board
void displayBoard(char board[3][3]) {
    cout << "-------------" << endl; //board frame
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | "; // disp each board(cell)
        }
        cout << endl << "-------------" << endl; //separate rows
    }
}

// player moves
void playerMove(char board[3][3], vector<int>& x, vector<int>& y, vector<int>& x_p, vector<int>& y_p) {
    int choice;
    cout << "Enter the number of the cell where you'd like to place X: ";
    cin >> choice;

    // find board coords (xi,yi) from user inp
    int xi = (choice - 1) / 3; // row
    int yi = (choice - 1) % 3; // column

    // if spot is free
    if (board[xi][yi] != 'X' && board[xi][yi] != 'O') {
        board[xi][yi] = 'X'; // put x on board
        x_p.push_back(xi); // store move x
        y_p.push_back(yi); // store move y

        // rm selection from possible pos
        for (int i = 0; i < x.size(); i++) {
            if (x[i] == xi && y[i] == yi) {
                x.erase(x.begin() + i);
                y.erase(y.begin() + i);
                break; // Exit the loop after rm
            }
        }
    } else {
        // If the move is invalid ask for new inp
        cout << "Invalid move! Try again." << endl;
        playerMove(board, x, y, x_p, y_p); // recurse until inp = valid move 
    }
}

// cpu moves
void cpuMove(char board[3][3], vector<int>& x, vector<int>& y, vector<int>& x_c, vector<int>& y_c) {
    if (x.empty()) return; // do nothing if nothing can be done

    int randIndex = rand() % x.size(); // rand find move
    int xi = x[randIndex]; // get x of move
    int yi = y[randIndex]; // get y of move

    board[xi][yi] = 'O'; // put o on board
    x_c.push_back(xi); // store move x
    y_c.push_back(yi); // store move y

    // rm move from all possible moves
    x.erase(x.begin() + randIndex);
    y.erase(y.begin() + randIndex);
}

// check if player won
bool checkWin(char board[3][3], char player) {
    // check win cond
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || // check row i
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {  // check column i
            return true; // player win
        }
    }
    // check diagonals for a win condition
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || // main diagonal
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {  // anti-diagonal
        return true; // player win
    }
    return false; // no win
}

// check draw
bool checkDraw(char board[3][3]) {
    // loop thru all cells
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false; // if empty cell, != draw
            }
        }
    }
    return true; // no empty cell, = draw
}
