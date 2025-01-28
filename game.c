#include "game.h"
#include "raymath.h"

GameState InitGame(void) {
    GameState game = {0};
    game.paddle.rect = (Rectangle){SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2, SCREEN_HEIGHT - 50, PADDLE_WIDTH, PADDLE_HEIGHT};
    game.paddle.speed = 8.0f;
    game.ball.position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    game.ball.speed = (Vector2){5.0f, -5.0f};
    return game;
}

void UpdateGame(GameState *game) {
    // Paddle movement
    if (IsKeyDown(KEY_LEFT) && game->paddle.rect.x > 0) game->paddle.rect.x -= game->paddle.speed;
    if (IsKeyDown(KEY_RIGHT) && game->paddle.rect.x < SCREEN_WIDTH - PADDLE_WIDTH) game->paddle.rect.x += game->paddle.speed;

    // Ball movement
    game->ball.position = Vector2Add(game->ball.position, game->ball.speed);

    // Ball collisions with screen edges
    if (game->ball.position.x - BALL_RADIUS <= 0 || game->ball.position.x + BALL_RADIUS >= SCREEN_WIDTH) {
        game->ball.speed.x = -game->ball.speed.x;
    }
    if (game->ball.position.y - BALL_RADIUS <= 0 || game->ball.position.y + BALL_RADIUS >= SCREEN_HEIGHT) {
        game->ball.speed.y = -game->ball.speed.y;
    }
}

void DrawGame(GameState *game) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(game->paddle.rect, BLUE);
    DrawCircleV(game->ball.position, BALL_RADIUS, WHITE);
    EndDrawing();
}
