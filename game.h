#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20
#define BALL_RADIUS 10

typedef struct Ball {
    Vector2 position;
    Vector2 speed;
} Ball;

typedef struct Paddle {
    Rectangle rect;
    float speed;
} Paddle;

typedef struct GameState {
    Ball ball;
    Paddle paddle;
} GameState;

GameState InitGame(void);
void UpdateGame(GameState *game);
void DrawGame(GameState *game);

#endif // GAME_H
