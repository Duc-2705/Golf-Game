#include "Ball.h"
#include "TextureManager..h"
#include "Collision.h"
#include "Map.h"
#include "Utilities.h"

Ball::Ball(const float& xPos, const float& yPos, const std::vector<Obstacle*>& obstacles)
{
	position.x = xPos;
	position.y = yPos;

	this->obstacles = obstacles;
	for (int i = 0; i < obstacles.size(); i++)
	{
		isAbleToCollide.push_back(1);
	}
}

Ball::~Ball()
{
	delete cursor;
	SDL_DestroyTexture(texBall);
}

void Ball::init()
{
	texBall = TextureManager::LoadTexture("assets/BouncingBall.png");

	TextureManager::setSrcRect(texBall, srcBall);

	cursor = new Cursor(this);

	velocity.Zero();

	destBall.w = static_cast<float>(BALL_WIDTH);
	destBall.h = static_cast<float>(BALL_HEIGHT);

	radius = destBall.w * 0.5f;

	center.x = position.x + radius;
	center.y = position.y + radius;

	/*Game::camera.x = std::max(0.0f, std::min(center.x - Game::camera.w / 2, Map::MAP_WIDTH - Game::camera.w));
	Game::camera.y = std::max(0.0f, std::min(center.y - Game::camera.h / 2, Map::MAP_HEIGHT - Game::camera.h));*/
}

void Ball::handleEvent(SDL_Event& event)
{
	if (velocity.magnitude == 0) cursor->handleEvent(event);
}

void Ball::update()
{
	destBall.x = position.x;
	destBall.y = position.y;

	center.x = position.x + radius;
	center.y = position.y + radius;

	if (cursor->Pulled())
	{
		velocity.magnitude = cursor->Force().magnitude; // Do lon cua Force

		velocity.i = (cursor->Force().magnitude) ? - (cursor->Force().x / cursor->Force().magnitude) : 0; // Tranh viec chia cho 0

		velocity.j = (cursor->Force().magnitude) ? - (cursor->Force().y / cursor->Force().magnitude) : 0; // Tranh viec chia cho 0

		playChunk(Game::chunkHit, velocity.magnitude);

		Game::remainingShots--;
	}
	
	this->collisionHandling();

	this->motion();

	if (!cursor->MouseDown) this->updateCamera();

	cursor->update();
}

void Ball::collisionHandling()
{
	for (int i = 0; i < obstacles.size(); i++)
	{
		if (isAbleToCollide[i] && Collision::checkCollisionObstacle(*this, *obstacles[i]) != -1) // Va cham voi obstacle i
		{
			Obstacle* obstacle = obstacles[i];
			int index = Collision::checkCollisionObstacle(*this, *obstacle); // Va cham voi mp index

			//Phan xa guong
			float DotProduct = velocity.i * obstacle->normal.i + velocity.j * obstacle->normal.j; //Tich vo huong velocity va normal

			velocity.i = velocity.i - 2 * DotProduct * obstacle->normal.i;
			velocity.j = velocity.j - 2 * DotProduct * obstacle->normal.j;

			velocity.magnitude *= LOSS; //Giam do lon do va cham

			isAbleToCollide[i] = false;

			playChunk(Game::chunkCollide, velocity.magnitude);

			std::cout << obstacle->normal.i << " " << obstacle->normal.j << " Collision plane " << index << std::endl;
		}
		else if (!isAbleToCollide[i] && Collision::checkCollisionObstacle(*this, *obstacles[i]) == -1) isAbleToCollide[i] = true;
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

	if (position.x + destBall.w > Game::camera.x + Game::camera.w)
	{
		position.x = static_cast<float> (Game::camera.x + Game::camera.w - destBall.w);
		velocity.i *= -1.0f; //Doi chieu do va cham
		velocity.magnitude *= LOSS; //Giam nang luong do va cham

		playChunk(Game::chunkCollide, velocity.magnitude);
	}
	else if (position.x < 0)
	{
		position.x = 0.0f;
		velocity.i *= -1.0f;
		velocity.magnitude *= LOSS;

		playChunk(Game::chunkCollide, velocity.magnitude);
	}

	if (position.y + destBall.h > Game::camera.y + Game::camera.h)
	{
		position.y = static_cast<float> (Game::camera.y + Game::camera.h - destBall.h);
		velocity.j *= -1.0f;
		velocity.magnitude *= LOSS;

		playChunk(Game::chunkCollide, velocity.magnitude);
	}
	else if (position.y < 0)
	{
		position.y = 0.0f;
		velocity.j *= -1.0f;
		velocity.magnitude *= LOSS;

		playChunk(Game::chunkCollide, velocity.magnitude);
	}
}

void Ball::updateCamera()
{
	Game::camera.x = lerp(Game::camera.x, center.x - Game::WINDOW_WIDTH / 2, LERP_SPEED);
	Game::camera.y = lerp(Game::camera.y, center.y - Game::WINDOW_HEIGHT / 2, LERP_SPEED);

	Game::camera.x = std::max(0.0f, std::min(Game::camera.x, Map::MAP_WIDTH - Game::camera.w));
	Game::camera.y = std::max(0.0f, std::min(Game::camera.y, Map::MAP_HEIGHT - Game::camera.h));
}

void Ball::render()
{
	if (cursor->MouseDown) cursor->arrow->render();
	TextureManager::Draw(texBall, srcBall, destBall);
}

void Ball::playChunk(Mix_Chunk* chunk,const float& veloMag)
{
	Mix_VolumeChunk(chunk, static_cast<int>(veloMag / MAX_VELOCITY * MAX_VOLUME));
	Mix_PlayChannel(-1, chunk, 0);
}

void Ball::reset(const float& xPos, const float& yPos)
{
	position.x = xPos;
	position.y = yPos;

	velocity.Zero();

	center.x = position.x + radius;
	center.y = position.y + radius;

	Game::remainingShots = 3;
}

bool Ball::stop()
{
	return (velocity.magnitude == 0);
}