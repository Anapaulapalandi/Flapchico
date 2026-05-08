#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "resource_dir.h"	

#define GRAVITY 50

typedef struct Chico {
	Vector2 pos;
	float velocity;
	float col_radius;
}Chico;

typedef struct Pipe {
	Vector2 pos;
	float velocity;
	int hg;
	int wt;
}Pipe;

Chico player;
Pipe test;

int main ()
{

	//Setup raylib//
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(800, 600, "Play Flapchico");
	SearchAndSetResourceDir("resources");

	//game init//
	player.pos.x = 400;
	player.pos.y = 300;

	test.pos.x = 600;
	test.pos.y = 300;
	test.wt = 64;
	test.hg = 128;
	test.velocity = 35;

	//Texture chico = LoadTexture("Chicao.png");
	Texture2D chico = LoadTexture("Chicao.png");
	
	
	while (!WindowShouldClose())		
	{
		//velocity
		float dt = GetFrameTime();
		player.velocity += GRAVITY*dt;
		player.pos.y += player.velocity*dt;

		//pipe walk
		test.pos.x -= test.velocity * dt;

		//drawing
		BeginDrawing();

		
		ClearBackground(WHITE);

		DrawRectangle(test.pos.x, test.pos.y, test.wt, test.hg, YELLOW);
		//DrawTexture(chico, player.pos.x,player.pos.y, GREEN);
		DrawTextureEx(chico, player.pos, 0, 32.0f / chico.width, WHITE);
		
		
		EndDrawing();
	}

	
	UnloadTexture(chico);

	
	CloseWindow();
	return 0;
}
