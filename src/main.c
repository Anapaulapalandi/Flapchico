#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "resource_dir.h"

#define GRAVITY 500
#define MAX_PIPES 900
#define SPAWN_MIN 2.0f
#define PIPE_SPEED 50
#define MULTI 10
#define SPAWN_MAX 6.0f

int count = 0;
float timer = 0;
float spawn_rate = SPAWN_MIN;


typedef struct Chico {
    Vector2 pos;
    float velocity;
    float col_radius;
    int hg;
    int wt;
} Chico;

typedef struct Pipe {
    Vector2 pos;
    float velocity;
    int hg;
    int wt;
    Color color;
} Pipe;

typedef struct PipeInvert {
    Vector2 pos;
    float velocity;
    int hg;
    int wt;
    Color color;
} PipeInvert;

Chico player;
Pipe pipe;
PipeInvert pipei;

Pipe* pipes[MAX_PIPES];

Color GetRandomColor(void)
{
    Color c = {
        GetRandomValue(0, 255),
        GetRandomValue(0, 255),
        GetRandomValue(0, 255),
        255
    };
    return c;
}

void spawnpipe() {
    Pipe* p = malloc(sizeof(Pipe));
    p->pos.x =GetScreenWidth();
    p->pos.y = 300;
    p->velocity = PIPE_SPEED;
    p->wt = 32* MULTI;
    p->hg = 64* MULTI;
    p->color = GetRandomColor();
    pipes[count++] = p;

}

void updatepipe(float dt) {
    for (int p = 0; p < count; p++) {
        Pipe* pipeaccess = pipes[p];
        pipeaccess->pos.x -= pipeaccess->velocity * dt;
    }
}

void drawpipes(Texture2D tex) {
    for (int p = 0; p < count; p++) {
        Pipe* pipeaccess = pipes[p];
        float pipeScale = (float)pipeaccess->wt / tex.width;
        DrawTextureEx(tex, pipeaccess->pos, 0, pipeScale,pipeaccess->color);
    }
}
int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 600, "Play Flapchico");
    SearchAndSetResourceDir("resources");

    player.pos.x = 150;
    player.pos.y = 100;
    player.velocity = 0;
    player.wt = 100;
    player.hg = 100;



    Texture2D chicoTex = LoadTexture("Chicao.png");
    Texture2D pipeTex = LoadTexture("pipe.png");
    Texture2D pipeiTex = LoadTexture("pipeInvert.png");

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        timer += dt;

        if (timer > spawn_rate)
        {
            if (count <= MAX_PIPES)
            {
                spawnpipe();
            }
            spawn_rate = GetRandomValue(SPAWN_MIN, SPAWN_MAX);
            timer = 0;
        }

        if (IsKeyPressed(KEY_SPACE)) {
            player.velocity = -300.0f;
        }

        player.velocity += GRAVITY * dt;
        player.pos.y += player.velocity * dt;
        updatepipe(dt);


        BeginDrawing();
        ClearBackground(WHITE);


        // Textura do pipe com scale proporcional
        
        drawpipes(pipeTex);

        DrawTextureEx(chicoTex, player.pos, 0, 100.0f / chicoTex.width , WHITE);



        EndDrawing();
    }

    UnloadTexture(chicoTex);
    UnloadTexture(pipeTex);
    UnloadTexture(pipeiTex);

    CloseWindow();
    return 0;
}