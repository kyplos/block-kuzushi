#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20
#define BALL_RADIUS 10
#define BLOCK_ROWS 5
#define BLOCK_COLUMNS 12
#define BLOCK_WIDTH 60
#define BLOCK_HEIGHT 30
#define MAX_POWERUPS 3

typedef struct Block {
    Rectangle rect;
    int durability;
    bool destroyed;
} Block;

typedef struct Ball {
    Vector2 position;
    Vector2 speed;
} Ball;

typedef struct Paddle {
    Rectangle rect;
    float speed;
} Paddle;

typedef struct PowerUp {
    Rectangle rect;
    bool active;
} PowerUp;

typedef struct GameState {
    Ball ball;
    Paddle paddle;
    Block blocks[BLOCK_ROWS][BLOCK_COLUMNS];
    int lives;
    int score;
    PowerUp powerUps[MAX_POWERUPS];
} GameState;

GameState InitGame(void);
void UpdateGame(GameState *game);
void DrawGame(GameState *game);

#endif // GAME_H
