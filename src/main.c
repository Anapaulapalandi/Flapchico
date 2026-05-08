#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "resource_dir.h"

#define GRAVITY 500

typedef struct Chico {
    Vector2 pos;
    float velocity;
    float col_radius;
} Chico;

typedef struct Pipe {
    Vector2 pos;
    float velocity;
    int hg;
    int wt;
} Pipe;

Chico player;
Pipe pipe;

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 600, "Play Flapchico");
    SearchAndSetResourceDir("resources");

    player.pos.x = 400;
    player.pos.y = 300;
    player.velocity = 0;

    pipe.pos.x = 600;
    pipe.pos.y = 300;
    pipe.wt = 64;
    pipe.hg = 128;
    pipe.velocity = 35;

    Texture2D chicoTex = LoadTexture("Chicao.png");
    Texture2D pipeTex = LoadTexture("pipe.png");

    // ✅ Verifica se carregou
    if (pipeTex.id == 0) {
        TraceLog(LOG_ERROR, "FALHOU ao carregar pipe.png");
    }

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        player.velocity += GRAVITY * dt;
        player.pos.y += player.velocity * dt;
        pipe.pos.x -= pipe.velocity * dt;

        if (IsKeyPressed(KEY_SPACE)) {
            player.velocity = -300.0f;
        }

        BeginDrawing();
        ClearBackground(WHITE);

        // 🟩 Retângulo debug - se aparecer verde o problema é na textura
        DrawRectangle(pipe.pos.x, pipe.pos.y, pipe.wt, pipe.hg, GREEN);

        // Textura do pipe com scale proporcional
        float pipeScale = (float)pipe.wt / pipeTex.width;
        DrawTextureEx(pipeTex, pipe.pos, 0, pipeScale, WHITE);

        DrawTextureEx(chicoTex, player.pos, 0, 32.0f / chicoTex.width, WHITE);

        EndDrawing();
    }

    UnloadTexture(chicoTex);
    UnloadTexture(pipeTex);

    CloseWindow();
    return 0;
}