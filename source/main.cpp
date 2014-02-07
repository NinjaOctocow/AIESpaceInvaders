
#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>

//The Original resolution of Space Invaders was 224 x 260 
//For comparison the Nintendo DS has a resolution of 292 x 192
//We're going to render this out at three times the original resolution (because we can)

int main( int argc, char* argv[] )
{	
	Initialise(672, 780, false, "Space Invaders!");

	int cannon = CreateSprite("./images/cannon.png", 64, 32, false);

	int alien1 = CreateSprite("./images/invaders/invaders_1_00.png", 128, 96, false, SColour(0, 0, 255, 255));

	/*int alien1Anim = CreateSprite("./images/invaders_1_01.png", 128, 96, false, SColour(0, 0, 255, 255)); */

	int endGame = CreateSprite("./images/end_game.png", 500, 700, true);

	/*time_t timer;
	bool animate = false;
	float animateTime;
	float waitTime = 1.0; */

	float alien1PosX = 272;
	float alien1PosY = 456;
	float alien1Speed = 0.08;
	bool isAlive = true;


	float cannonXPos = 336 - 32;
	float cannonYPos = 100;
	float cannonSpeed = 0.1;

	bool bulletShot = false;
	float bulletPosX = 0; 
	float bulletPosY = 0;
	float bulletSpeed = 0.15;

	do
	{
		SetBackgroundColour(SColour(0, 0, 0, 255));
		ClearScreen();
		//Sets background colour for window to black


		MoveSprite(cannon, cannonXPos, cannonYPos);
		DrawSprite(cannon);

		MoveSprite(alien1, alien1PosX, alien1PosY);
		DrawSprite(alien1);
		
		/*time(&timer);
		//Updates timer

		if(animate == false)
		{
			animateTime = timer + waitTime;
		}
		
		if(animateTime > timer)
		{
			animate = true;
		}
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

		if(isAlive == true)
		{
			alien1PosX = alien1PosX + alien1Speed;
			
				if(alien1PosX >= 672 - 128)
			{
				alien1Speed = -alien1Speed;
				alien1PosX + alien1Speed;
			}
				else if(alien1PosX < 0)
			{
				alien1Speed = -alien1Speed;
				alien1PosX + alien1Speed;
			}

		}

		
		//Automatic Alien movement

		if(bulletPosX > alien1PosX && bulletPosX < alien1PosX + 128 && bulletPosY < alien1PosY && bulletPosY > alien1PosY - 96 && bulletShot)
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

	} while (FrameworkUpdate() == false);


	Shutdown();
	return 0;
}

