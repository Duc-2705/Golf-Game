#include "Ball.h"
#include "TextureManager..h"
#include "Collision.h"


Ball::~Ball()
{
	cursor->clean();
	delete cursor;
	SDL_DestroyTexture(texBall);
}

void Ball::init()
{
	texBall = TextureManager::LoadTexture("assets/BouncingBall.png");

	TextureManager::setSrcRect(texBall, srcBall);

	cursor = new Cursor(this);

	velocity.Zero();
	
	position.x = static_cast<float>(Game::WINDOW_WIDTH/2 - BALL_WIDTH/2);
	position.y = static_cast<float>(Game::WINDOW_HEIGHT/2 -BALL_HEIGHT/2);

	destBall.w = static_cast<float>(BALL_WIDTH);
	destBall.h = static_cast<float>(BALL_HEIGHT);

	radius = destBall.w * 0.5f;

	center.x = position.x + radius;
	center.y = position.y + radius;

	for (int i = 0; i < obstacles.size(); i++)
	{
		isAbleToCollide.push_back(1);
	}
}

void Ball::update()
{
	destBall.x = position.x;
	destBall.y = position.y;

	center.x = position.x + radius;
	center.y = position.y + radius;

	cursor->handleEvents();

	if (cursor->isPulling())
	{
		velocity.magnitude = cursor->Force().magnitude; // Do lon cua Force

		// Vector don vi cua Force chieu len Ox
		velocity.i = (cursor->Force().magnitude) ? - (cursor->Force().x / cursor->Force().magnitude) : 0; // Tranh viec chia cho 0

		// Vector don vi cua Force chieu len Oy
		velocity.j = (cursor->Force().magnitude) ? - (cursor->Force().y / cursor->Force().magnitude) : 0; // Tranh viec chia cho 0
	}

	for (int i = 0; i < obstacles.size(); i++)
	{
		if (isAbleToCollide[i] && Collision::checkCollision(*this, *obstacles[i]) != -1) // Va cham voi obstacle i
			{
				Obstacle* obstacle = obstacles[i];
				int index = Collision::checkCollision(*this, *obstacle); // Va cham voi mp index

				//Phan xa guong
				float DotProduct = velocity.i * obstacle->planes[index].first.i + velocity.j * obstacle->planes[index].first.j; //Tich vo huong

				velocity.i = velocity.i - 2 * DotProduct * obstacle->planes[index].first.i;
				velocity.j = velocity.j - 2 * DotProduct * obstacle->planes[index].first.j;

				velocity.magnitude *= LOSS; //Giam do lon do va cham

				isAbleToCollide[i] = false;
				std::cout << "Collision plane " << index << std::endl;
			}
		else if (!isAbleToCollide[i] && Collision::checkCollision(*this, *obstacles[i]) == -1) isAbleToCollide[i] = true;
	}


}

void Ball::motion()
{
	if (velocity.magnitude > 0)
	{
		velocity.magnitude += FRICTION * dTime; // Giam do lon cua van toc
		if (velocity.magnitude < 0) velocity.Zero();
	}

	position.x += velocity.i * velocity.magnitude * dTime;
	position.y += velocity.j * velocity.magnitude * dTime;

	if (position.x + destBall.w > Game::WINDOW_WIDTH)
	{
		position.x = static_cast<float> ( Game::WINDOW_WIDTH - destBall.w);
		velocity.i *= -1.0f; //Doi chieu do va cham
		velocity.magnitude *= LOSS; //Giam nang luong do va cham
	}
	else if (position.x < 0)
	{
		position.x = 0.0f;
		velocity.i *= -1.0f;
		velocity.magnitude *= LOSS;
	}

	if (position.y + destBall.h > Game::WINDOW_HEIGHT)
	{
		position.y = static_cast<float> (Game::WINDOW_HEIGHT - destBall.h);
		velocity.j *= -1.0f;
		velocity.magnitude *= LOSS;
	}
	else if (position.y < 0)
	{
		position.y = 0.0f;
		velocity.j *= -1.0f;
		velocity.magnitude *= LOSS;
	}	

}

void Ball::render()
{
	cursor->update();
	TextureManager::Draw(texBall, srcBall, destBall);
}

