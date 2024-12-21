#include <iostream>
#include <graphics.h>
#include <conio.h>

void drawCircle(int x, int y, int rad) {
    circle(75 + x, 75 + y, rad);
}

void drawCross(int x, int y) {
    line(50 + x, 50 + y, 100 + x, 100 + y);
    line(100 + x, 50 + y, 50 + x, 100 + y);
}

void drawBoard() {
    line(150, 0, 150, 400);
    line(300, 0, 300, 400);
    line(50, 150, 400, 150);
    line(50, 300, 400, 300);
}

// Base class for Player
class Player {
public:
    virtual void drawMove(int x, int y) = 0;  // Pure virtual function for drawing move
    virtual char getSymbol() = 0;              // Virtual function to return player symbol
};

// Derived class for Player O
class PlayerO : public Player {
public:
    void drawMove(int x, int y) override {
        drawCircle(x, y, 50);  // Draw Circle for Player O
    }
    
    char getSymbol() override {
        return 'O';
    }
};

// Derived class for Player X
class PlayerX : public Player {
public:
    void drawMove(int x, int y) override {
        drawCross(x, y);  // Draw Cross for Player X
    }
    
    char getSymbol() override {
        return 'X';
    }
};

int checker(int arr[3][3]) {
    // Check for a win condition
    if ((arr[0][0] == arr[0][1] && arr[0][1] == arr[0][2] && arr[0][0] != -1) ||
        (arr[1][0] == arr[1][1] && arr[1][1] == arr[1][2] && arr[1][0] != -1) ||
        (arr[2][0] == arr[2][1] && arr[2][1] == arr[2][2] && arr[2][0] != -1) ||
        (arr[0][0] == arr[1][0] && arr[1][0] == arr[2][0] && arr[0][0] != -1) ||
        (arr[0][1] == arr[1][1] && arr[1][1] == arr[2][1] && arr[0][1] != -1) ||
        (arr[0][2] == arr[1][2] && arr[1][2] == arr[2][2] && arr[0][2] != -1) ||
        (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[0][0] != -1) ||
        (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0] && arr[0][2] != -1)) {
        return 1;  // Someone won
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == -1) {
                return 0;  // Game is still ongoing
            }
        }
    }

    return -1;  // It's a draw
}

int main() {
    int gdriver = DETECT, gmode, errorcode;
    initgraph(&gdriver, &gmode, "C:\\turboc3\\bgi");

    int arr[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};  // Game board
    int block, invalid = 0;
    Player* currentPlayer;  // Pointer to base class Player
    PlayerO playerO;        // Player O instance
    PlayerX playerX;        // Player X instance

    drawBoard();  // Draw the Tic-Tac-Toe board

    int code;
    do {
        // Set current player
        if (arr[0][0] == -1) {
            currentPlayer = &playerO;  // Player O's turn
        } else {
            currentPlayer = &playerX;  // Player X's turn
        }

        cout << "Player " << currentPlayer->getSymbol() << "'s turn" << endl;
        cout << "Enter Block No (1-9): ";
        cin >> block;

        invalid = 0;
        int row = (block - 1) / 3;
        int col = (block - 1) % 3;

        // Check for invalid block
        if (block < 1 || block > 9 || arr[row][col] != -1) {
            cout << "Invalid Block" << endl;
            invalid = 1;
        }

        if (!invalid) {
            arr[row][col] = currentPlayer->getSymbol() == 'O' ? 0 : 1;  // Update board with O(0) or X(1)
            int x = col * 150;
            int y = row * 150;

            // Draw the move using polymorphism
            currentPlayer->drawMove(x, y);
        }

        code = checker(arr);
    } while (code == 0);

    if (code == 1) {
        cout << "Winner is Player " << (arr[0][0] == 0 ? "O" : "X") << endl;
    } else {
        cout << "It's a Draw!" << endl;
    }

    getch();
    closegraph();
    return 0;
}
