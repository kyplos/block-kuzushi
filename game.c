#include "game.h"
#include "raymath.h"
#include <stdlib.h>

GameState InitGame(void) {
    GameState game = {0};
    game.paddle.rect = (Rectangle){SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2, SCREEN_HEIGHT - 50, PADDLE_WIDTH, PADDLE_HEIGHT};
    game.paddle.speed = 8.0f;
    game.ball.position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    game.ball.speed = (Vector2){5.0f, -5.0f};
    for (int y = 0; y < BLOCK_ROWS; y++) {
        for (int x = 0; x < BLOCK_COLUMNS; x++) {
            game.blocks[y][x].rect = (Rectangle){x * BLOCK_WIDTH + 30, y * BLOCK_HEIGHT + 50, BLOCK_WIDTH, BLOCK_HEIGHT};
            game.blocks[y][x].durability = (rand() % 3) + 1;
            game.blocks[y][x].destroyed = false;
        }
    }

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

    if (CheckCollisionCircleRec(game->ball.position, BALL_RADIUS, game->paddle.rect)) {
        game->ball.speed.y = -fabsf(game->ball.speed.y);
    }

    for (int y = 0; y < BLOCK_ROWS; y++) {
        for (int x = 0; x < BLOCK_COLUMNS; x++) {
            Block *block = &game->blocks[y][x];
            if (!block->destroyed && CheckCollisionCircleRec(game->ball.position, BALL_RADIUS, block->rect)) {
                block->durability--;
                if (block->durability <= 0) {
                    block->destroyed = true;
                }
                game->ball.speed.y = -game->ball.speed.y;
            }
        }
    }

}

void DrawGame(GameState *game) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(game->paddle.rect, BLUE);
    DrawCircleV(game->ball.position, BALL_RADIUS, WHITE);

    for (int y = 0; y < BLOCK_ROWS; y++) {
        for (int x = 0; x < BLOCK_COLUMNS; x++) {
            Block *block = &game->blocks[y][x];
            if (!block->destroyed) {
                // Assign block color based on durability
                Color blockColor = (block->durability == 1) ? RED :
                                   (block->durability == 2) ? ORANGE : GREEN;

                // Draw block rectangle
                DrawRectangleRec(block->rect, blockColor);

                // Display block durability as text
                DrawText(TextFormat("%d", block->durability),
                         block->rect.x + BLOCK_WIDTH / 2 - 5,
                         block->rect.y + BLOCK_HEIGHT / 2 - 8,
                         12, WHITE);
            }
        }
    }

    EndDrawing();
}
