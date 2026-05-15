#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "resource_dir.h"

#define GRAVITY 500
#define MAX_PIPES 900
#define SPAWN_MIN 5.0f
#define PIPE_SPEED 150
#define MULTI 10
#define SPAWN_MAX 8.0f

int count = 0;
int counti = 0;
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

Chico player;

Pipe* pipes[MAX_PIPES];
Pipe* inverts[MAX_PIPES];

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
    Color c = GetRandomColor();
    Pipe* p = malloc(sizeof(Pipe));
    Pipe* i = malloc(sizeof(Pipe));

    p->pos.x =GetScreenWidth();
    p->pos.y = 300;
    p->velocity = PIPE_SPEED;
    p->wt = 32* MULTI;
    p->hg = 64* MULTI;
    p->color = c;

    i->pos.x = GetScreenWidth();
    i->pos.y = 0;
    i->velocity = PIPE_SPEED;
    i->wt = 32 * MULTI;
    i->hg = 64 * MULTI;
    i->color = c;
    pipes[count] = p;
    inverts[count] = i;
    count++;

}

void updatepipe(float dt) {
    for (int p = 0; p < count; p++) {
        Pipe* pipeaccess = pipes[p];
        Pipe* i = inverts[p];
        pipeaccess->pos.x -= pipeaccess->velocity * dt;
        i->pos.x -= i->velocity * dt;
    }
}


void drawpipes(Texture2D tex, Texture2D itex) {
    for (int p = 0; p < count; p++) {
        Pipe* pipeaccess = pipes[p];
        Pipe* i = inverts[p];
        float pipeScale = (float)pipeaccess->wt / tex.width;
        DrawTextureEx(tex, pipeaccess->pos, 0, pipeScale,pipeaccess->color);
        DrawTextureEx(itex, i->pos, 0, pipeScale, i->color);
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
        
        drawpipes(pipeTex, pipeiTex);
       

        DrawTextureEx(chicoTex, player.pos, 0, 100.0f / chicoTex.width , WHITE);





        EndDrawing();
    }

    UnloadTexture(chicoTex);
    UnloadTexture(pipeTex);
    UnloadTexture(pipeiTex);

    CloseWindow();
    return 0;
}