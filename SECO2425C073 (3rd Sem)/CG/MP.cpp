#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>

// Screen dimensions
const int screenWidth = 640;
const int screenHeight = 480;

// Player spaceship attributes
int playerX = screenWidth / 2;
int playerY = screenHeight - 50;
const int playerWidth = 30;
const int playerHeight = 20;

// Bullet attributes
struct Bullet {
    int x, y;
    bool isActive;
};
Bullet bullets[10];
int bulletCount = 0;
int bulletCooldown = 0;

// Enemy attributes
struct Enemy {
    int x, y;
    bool isAlive;
};
Enemy enemy;

// Game control
bool isRunning = true;
bool gameOver = false;
int score = 0;
int missedEnemies = 0;

// Function to initialize graphics and game elements
void initGame() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Reset game variables
    playerX = screenWidth / 2;
    score = 0;
    missedEnemies = 0;
    gameOver = false;

    // Initialize enemy
    enemy.x = rand() % screenWidth;
    enemy.y = 0;
    enemy.isAlive = true;

    // Initialize bullets
    for (int i = 0; i < 10; i++) {
        bullets[i].isActive = false;
    }
}

// Function to draw player spaceship, enemy, bullets, and score
void drawGame() {
    cleardevice();

    // Draw player spaceship
    line(playerX, playerY - 10, playerX - 15, playerY + 10);   // Left wing
    line(playerX, playerY - 10, playerX + 15, playerY + 10);   // Right wing
    line(playerX - 15, playerY + 10, playerX + 15, playerY + 10); // Base
    line(playerX, playerY - 20, playerX, playerY - 10); // Nose
    
    // Draw enemy
    if (enemy.isAlive) {
        rectangle(enemy.x - 10, enemy.y - 10, enemy.x + 10, enemy.y + 10);
    }

    // Draw bullets
    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i].isActive) {
            line(bullets[i].x, bullets[i].y, bullets[i].x, bullets[i].y - 10);
        }
    }

    // Display score
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    outtextxy(10, 10, scoreText);

    // Display game over message if game is over
    if (gameOver) {
        outtextxy(screenWidth / 2 - 60, screenHeight / 2, "Game Over!");
        outtextxy(screenWidth / 2 - 100, screenHeight / 2 + 20, "Press Space to Restart");
    }
}

// Function to move bullets
void moveBullets() {
    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i].isActive) {
            bullets[i].y -= 10;
            if (bullets[i].y < 0) {
                bullets[i].isActive = false;
            }

            // Check for collision with enemy
            if (enemy.isAlive &&
                bullets[i].x > enemy.x - 10 && bullets[i].x < enemy.x + 10 &&
                bullets[i].y > enemy.y - 10 && bullets[i].y < enemy.y + 10) {
                
                enemy.isAlive = false;
                bullets[i].isActive = false;
                score += 10;

                // Respawn enemy at top with random x position
                enemy.x = rand() % screenWidth;
                enemy.y = 0;
                enemy.isAlive = true;
            }
        }
    }
}

// Function to automatically fire bullets from spaceship
void autoFireBullet() {
    if (bulletCooldown == 0) {
        if (bulletCount < 10) {
            bullets[bulletCount].x = playerX;
            bullets[bulletCount].y = playerY - 20;
            bullets[bulletCount].isActive = true;
            bulletCount++;
        } else {
            // Reset bullet count to reuse bullet slots
            bulletCount = 0;
        }
        bulletCooldown = 10; // Set cooldown time for next bullet
    } else {
        bulletCooldown--;
    }
}

// Main game loop
void gameLoop() {
    while (isRunning) {
        if (!gameOver) {
            // Draw game elements
            drawGame();

            // Move bullets
            moveBullets();

            // Auto-fire bullets
            autoFireBullet();

            // Move enemy downward
            if (enemy.isAlive) {
                enemy.y += 2;
                if (enemy.y > screenHeight) {
                    missedEnemies++;
                    enemy.isAlive = false;

                    // Respawn enemy at the top
                    enemy.x = rand() % screenWidth;
                    enemy.y = 0;
                    enemy.isAlive = true;
                }

                // Check if player missed too many enemies
                if (missedEnemies >= 3) {
                    gameOver = true;
                }
            }

            // Player controls for movement
            if (GetAsyncKeyState(VK_LEFT) && playerX > 0) {
                playerX -= 5;
            }
            if (GetAsyncKeyState(VK_RIGHT) && playerX < screenWidth) {
                playerX += 5;
            }
        } else {
            // If game over, wait for spacebar to restart
            if (GetAsyncKeyState(VK_SPACE)) {
                initGame();
            }
        }

        delay(30); // Control the frame rate
    }
}

int main() {
    srand(time(0));  // Seed for random enemy positions
    initGame();
    gameLoop();
    closegraph();
    return 0;
}