
#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>
#include <sstream>

//The Original resolution of Space Invaders was 224 x 260 
//For comparison the Nintendo DS has a resolution of 292 x 192
//We're going to render this out at three times the original resolution (because we can)

enum gameState {MENU, GAME, END};
enum invaderState {INVADER1, INVADER2, INVADER3, DEAD};


int main( int argc, char* argv[] )
{	
	gameState myGameState = MENU;

	int screenWidth = 3 * 224;
	int screenHeight = 3 * 260;

	Initialise(screenWidth, screenHeight, false, "Space Invaders!");

	int cannon = CreateSprite("./images/cannon.png", 64, 32, false);

	int alien1 = CreateSprite("./images/invaders/invaders_1_00.png", 128, 96, false, SColour(0, 0, 255, 255));

	//int endGame = CreateSprite("./images/end_game.png", 500, 700, true);

	int startGame = CreateSprite("./images/start_screen.png", 500, 700, true);

	AddFont("./fonts/invaders.fnt");


	//float alien1Speed = 0.08;
	//bool isAlive = true;
	

	//////////////////////////////////////////////////////////////////////////////////
	const int numAliensPerRow = 8;
	const int numAlienRows = 5;

	int alienWidth = 32;
	int alienHeight = 32;

	int alienSprites [4][2];

	float aliensXPos[numAlienRows][numAliensPerRow];
	float aliensYPos[numAlienRows][numAliensPerRow];

	invaderState alienTypes [numAlienRows][numAliensPerRow];

	float alienXMargin = 48;
	float alienYMargin = 64;
	
	float alienMove = 0;
	float alienVelocity = alienWidth;

	int animationFrame = 0;
	/////////////////////////////////////////////////////////////////////////////
	for (int row = 0; row < numAlienRows; row++)
	{
		for (int i = 0; i < numAliensPerRow; i++)
		{
			aliensXPos[row][i] = alienXMargin + i * alienWidth * 2;
			aliensYPos[row][i] = screenHeight - alienYMargin - (row * alienHeight * 2);
		}
	}
	////////////////////////////////////////////////////////////////////////////
	for (int row = 0; row < numAlienRows; row++)
	{
		for (int i = 0; i < numAliensPerRow; i++)
		{
			switch (row % 3)
			{
				case 0:
					alienTypes[row][i] = INVADER1;
					break;
				case 1:
					alienTypes[row][i] = INVADER2;
					break;
				case 2:
					alienTypes[row][i] = INVADER3;
					break;
				default:
					break;
			}
		}
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Alien Sprite animation

	alienSprites[0][0] = CreateSprite("./images/invaders/invaders_1_00.png", alienWidth, alienHeight, false);
	alienSprites[0][1] = CreateSprite("./images/invaders/invaders_1_01.png", alienWidth, alienHeight, false);

	alienSprites[1][0] = CreateSprite("./images/invaders/invaders_2_00.png", alienWidth, alienHeight, false);
	alienSprites[1][1] = CreateSprite("./images/invaders/invaders_2_01.png", alienWidth, alienHeight, false);

	alienSprites[2][0] = CreateSprite("./images/invaders/invaders_6_00.png", alienWidth, alienHeight, false);
	alienSprites[2][1] = CreateSprite("./images/invaders/invaders_6_01.png", alienWidth, alienHeight, false);

	alienSprites[3][0] = CreateSprite("./images/invaders/invaders_7_01.png", alienWidth, alienHeight, false);
	alienSprites[3][1] = CreateSprite("./images/invaders/invaders_7_01.png", alienWidth, alienHeight, false);

	////////////////////////////////////////////////////////////////////////////
	float cannonXPos = 336 - 32;
	float cannonYPos = 100;
	float cannonSpeed = 1;

	bool bulletShot = false;
	float bulletPosX = 0; 
	float bulletPosY = 0;
	float bulletSpeed = 1;

	do
	{
		SetBackgroundColour(SColour(0, 0, 0, 255));
		ClearScreen();
		//Sets background colour for window to black
	if (myGameState == MENU)
		{	
			MoveSprite(startGame, 336, 390);
			DrawSprite(startGame);

			if (IsKeyDown(KEY_ENTER))
			{
				myGameState = GAME;
			}
		}
		else if (myGameState == GAME)
		{

		for (int row = 0; row < numAlienRows; row++)
		{
			for (int i = 0; i < numAliensPerRow; i++)
			{
				MoveSprite(alienSprites[alienTypes[row][i]][animationFrame], aliensXPos[row][i], aliensYPos[row][i]);
				DrawSprite(alienSprites[alienTypes[row][i]][animationFrame]);
			}
		}

		SetFont("./fonts/invaders.fnt");
		DrawString("Score: 0", 0, 3 * 260);

		MoveSprite(cannon, cannonXPos, cannonYPos);
		DrawSprite(cannon);

		/*MoveSprite(alien1, alien1PosX, alien1PosY);
		DrawSprite(alien1);
		*/
		
	

		if(IsKeyDown(KEY_LEFT))
		{
			cannonXPos = cannonXPos - cannonSpeed;
		}
		else if(IsKeyDown(KEY_RIGHT))
		{
			cannonXPos = cannonXPos + cannonSpeed;
		}
		//Detects keypress for Left and Right keys

		if(IsKeyDown(KEY_SPACE) && bulletShot == false)
		{
			
			bulletPosX  = cannonXPos+ 32;
			bulletPosY = cannonYPos + 20;
			bulletShot = true;
		}
		// Shooting the bullet

		if(bulletShot == true)
		{
 			DrawLine(bulletPosX, bulletPosY - 20, bulletPosX, bulletPosY);
			bulletPosY += bulletSpeed; 
		}
		//Bullet Movement

		if(bulletPosY > 800)
			bulletShot = false;

		//Bullet Reset

		if(cannonXPos >= 672)
		{
			 cannonXPos = 0;
		}
		else if(cannonXPos < -50)
		{
			cannonXPos = 672;
		}
		//Detects if Cannon is at border edge and moves it to correspoding opposite for X axis

	/*	if(isAlive == true)
		{
			aliensXPos[numAlienRows][numAliensPerRow] = aliensXPos[numAlienRows][numAliensPerRow] + alien1Speed;
			
				if(aliensXPos[numAlienRows][numAliensPerRow] >= 672 - 128)
			{
				alien1Speed = -alien1Speed;
				aliensXPos[numAlienRows][numAliensPerRow] += alien1Speed;
			}
				else if(aliensXPos[numAlienRows][numAliensPerRow] < 0)
			{
				alien1Speed = -alien1Speed;
				aliensXPos[numAlienRows][numAliensPerRow] += alien1Speed;
			}

		}
		

		
		//Automatic Alien movement

		if(bulletPosX > aliensXPos[numAlienRows][numAliensPerRow] && bulletPosX < aliensXPos[numAlienRows][numAliensPerRow] + 128 && bulletPosY < aliensYPos[numAlienRows][numAliensPerRow] && bulletPosY > aliensYPos[numAlienRows][numAliensPerRow] - 96 && bulletShot)
		{
			DestroySprite(alien1);
			bulletShot = false;
			isAlive = false;
		}
		//Bullet collision with single alien sprite, removes alien sprite and sets alien life status to false.

		if(isAlive == false)
		{	
			MoveSprite(endGame, 336, 390);
			DrawSprite(endGame);
		}
		//Shows end game screen as alien sprite is destroyed
		*/

		alienMove += GetDeltaTime();
		if (alienMove > 0.5)
		{
			// Moves aliens across
			animationFrame = (animationFrame + 1) % 2;
			alienMove = 0;
			alienXMargin += alienVelocity;
			if ((alienXMargin + numAliensPerRow * alienWidth * 2 - alienWidth) > (screenWidth - alienWidth) || 
				(alienXMargin) < (alienWidth))
			{
				// undoes the movement
				alienXMargin -= alienVelocity;

				alienYMargin += alienHeight;
				alienVelocity = -alienVelocity;
			}
		}
		for (int row = 0; row < numAlienRows; row++)
		{
			for (int i = 0; i < numAliensPerRow; i++)
			{
				if (alienTypes[row][i] != DEAD)
				{
					aliensXPos[row][i] = alienXMargin + i * alienWidth * 2;
					aliensYPos[row][i] = screenHeight - alienYMargin - (row * alienHeight * 2);
				}
				else
				{
					// Moves dead aliens off screen
					if (alienMove == 0)
					{
						aliensXPos[row][i] = screenWidth;
						aliensYPos[row][i] = 0;
					}
				}
			}
		}
		}
	} while (FrameworkUpdate() == false);


	Shutdown();
	return 0;
}

