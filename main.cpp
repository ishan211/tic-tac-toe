#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function prototypes
void displayBoard(char board[3][3]); // disp board
bool checkWin(char board[3][3], char player); // check win
bool checkDraw(char board[3][3]); // check draw
void playerMove(char board[3][3], std::vector<int>& x, std::vector<int>& y, std::vector<int>& x_p, std::vector<int>& y_p); // player move
void cpuMove(char board[3][3], std::vector<int>& x, std::vector<int>& y, std::vector<int>& x_c, std::vector<int>& y_c); // cpu move

int main() {
    // Init board
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    // vec for pos board
    std::vector<int> x = {0, 0, 0, 1, 1, 1, 2, 2, 2};
    std::vector<int> y = {0, 1, 2, 0, 1, 2, 0, 1, 2};

    // vec for player and cpu move
    std::vector<int> x_p, y_p;    
    std::vector<int> x_c, y_c;

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
            currentPlayer = '0'; // cpu turn
        } else {
            std::cout << "Player's turn" << std::endl;
            cpuMove(board, x, y, x_c, y_c); // cpu move
            gameWon = checkWin(board, '0'); // Check if cpu won
            currentPlayer = 'X'; // player turn
        }

        gameDraw = checkDraw(board); // Check if draw
    }

    displayBoard(board); // disp board

    // give game(res)
    if (gameWon) {
        if (currentPlayer == '0') { // If the currentPlayer 'O' player 'X' won
            std::cout << "Player wins!" << std::endl;
        } else { // otherwise cpu won
            std::cout << "CPU wins!" << std::endl;
        }
    } else if (gameDraw) {
        std::cout << "It's a draw!" << std::endl; // If gameDraw is true then its a draw
    }

    return 0; // Exit with 0
}

// disp current board
void displayBoard(char board[3][3]) {
    std::cout << "-------------" << std::endl; //board frame
    for (int i = 0; i < 3; i++) {
        std::cout << "| ";
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j] << " | "; // disp each board(cell)
        }
        std::cout << std::endl << "-------------" << std::endl; //separate rows
    }
}

// player moves
void playerMove(char board[3][3], std::vector<int>& x, std::vector<int>& y, std::vector<int>& x_p, std::vector<int>& y_p) {
    int choice;
    std::cout << "Enter the number of the cell where you'd like to place X: ";
    std::cin >> choice;

    // find board coords (xi,yi) from user inp
    int xi = (choice - 1) / 3; // row
    int yi = (choice - 1) % 3; // column

    // if spot is free
    if (board[xi][yi] != 'X' && board[xi][yi] != '0') {
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
        std::cout << "Invalid move! Try again." << std::endl;
        playerMove(board, x, y, x_p, y_p); // recurse until inp = valid move 
    }
}



// cpu moves
void cpuMove(char board[3][3], std::vector<int>& x, std::vector<int>& y, std::vector<int>& x_c, std::vector<int>& y_c) {
    if (x.empty()) return; // do nothing if nothing can be done

    int randIndex = rand() % x.size(); // rand find move
    int xi = x[randIndex]; // get x of move
    int yi = y[randIndex]; // get y of move

    board[xi][yi] = '0'; // put o on board
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
            if (board[i][j] != 'X' && board[i][j] != '0') {
                return false; // if empty cell, != draw
            }
        }
    }
    return true; // no empty cell, = draw
}
