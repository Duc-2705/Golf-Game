#include "Ball.h"
#include "TextureManager..h"
#include "Collision.h"
#include "Map.h"
#include "Utilities.h"

extern Map* map;

Ball::Ball(const float& xPos, const float& yPos)
{
	position.x = xSpawn = xPos;
	position.y = ySpawn = yPos;


	for (int i = 0; i < map->obstacles.size(); i++)
	{
		isAbleToCollide.push_back(1);
	}

	Game::camera = { (Map::MAP_WIDTH - Game::WINDOW_WIDTH) * 0.5f , (Map::MAP_HEIGHT - Game::WINDOW_HEIGHT) * 0.5f, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT };
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

	cursor = new Cursor();

	velocity.Zero();

	destBall.w = static_cast<float>(BALL_WIDTH);
	destBall.h = static_cast<float>(BALL_HEIGHT);

	radius = destBall.w * 0.5f;

	center.x = position.x + radius;
	center.y = position.y + radius;
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

		playChunk(Game::chunkHit, velocity.magnitude, 0);

		Game::remainingShots--;
	}
	
	this->collisionHandling();

	this->handleCollisionTiles();

	this->teleport();

	this->motion();

	if (!cursor->MouseDown) this->updateCamera();

	cursor->update();
}

void Ball::collisionHandling()
{
	for (int i = 0; i < map->obstacles.size(); i++)
	{
		if (isAbleToCollide[i] && Collision::checkCollisionObstacle(*this, *(map->obstacles[i])) != -1) // Va cham voi obstacle i
		{
			Obstacle* obstacle = map->obstacles[i];
			int index = Collision::checkCollisionObstacle(*this, *obstacle); // Va cham voi mp index

			//Phan xa guong
			float DotProduct = velocity.i * obstacle->normal.i + velocity.j * obstacle->normal.j; //Tich vo huong velocity va normal

			velocity.i = velocity.i - 2 * DotProduct * obstacle->normal.i;
			velocity.j = velocity.j - 2 * DotProduct * obstacle->normal.j;

			velocity.magnitude *= LOSS; //Giam do lon do va cham

			isAbleToCollide[i] = false;

			playChunk(Game::chunkCollide, velocity.magnitude, 0);

			std::cout << obstacle->normal.i << " " << obstacle->normal.j << " Collision plane " << index << std::endl;
		}
		else if (!isAbleToCollide[i] && Collision::checkCollisionObstacle(*this, *(map->obstacles[i])) == -1) isAbleToCollide[i] = true;
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

		playChunk(Game::chunkCollide, velocity.magnitude, 0);
	}
	else if (position.x < 0)
	{
		position.x = 0.0f;
		velocity.i *= -1.0f;
		velocity.magnitude *= LOSS;

		playChunk(Game::chunkCollide, velocity.magnitude, 0);
	}

	if (position.y + destBall.h > Game::camera.y + Game::camera.h)
	{
		position.y = static_cast<float> (Game::camera.y + Game::camera.h - destBall.h);
		velocity.j *= -1.0f;
		velocity.magnitude *= LOSS;

		playChunk(Game::chunkCollide, velocity.magnitude, 0);
	}
	else if (position.y < 0)
	{
		position.y = 0.0f;
		velocity.j *= -1.0f;
		velocity.magnitude *= LOSS;

		playChunk(Game::chunkCollide, velocity.magnitude, 0);
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

void Ball::playChunk(Mix_Chunk* chunk,const float& veloMag, const int& loops)
{
	Mix_VolumeChunk(chunk, static_cast<int>(veloMag / MAX_VELOCITY * MAX_VOLUME));
	Mix_PlayChannel(-1, chunk, loops);
}

void Ball::reset()
{
	Game::camera = { (Map::MAP_WIDTH - Game::WINDOW_WIDTH) * 0.5f , (Map::MAP_HEIGHT - Game::WINDOW_HEIGHT) * 0.5f, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT };

	position.x = xSpawn;
	position.y = ySpawn;

	velocity.Zero();

	center.x = position.x + radius;
	center.y = position.y + radius;

	Game::remainingShots = 3;
	waterDrop = false;

}

bool Ball::stop()
{
	return (velocity.magnitude == 0);
}

void Ball::teleport()
{
	if ((position.x >= map->EntryPortal->position.x && position.x <= map->EntryPortal->position.x + map->EntryPortal->PORTAL_WIDTH) &&
		(position.y >= map->EntryPortal->position.y && position.y <= map->EntryPortal->position.y + map->EntryPortal->PORTAL_HEIGHT))
	{
		std::cout << "Teleport" << std::endl;
		position.x += map->ExitPortal->position.x - map->EntryPortal->position.x + BALL_WIDTH/2;
		position.y += map->ExitPortal->position.y - map->EntryPortal->position.y + BALL_HEIGHT/2;
	}
}

void Ball::handleCollisionTiles()
{
	bool check = false;

	for (auto sand : map->sandTiles)
	{
		if (Collision::checkCollisionTile(this, sand))
		{
			check = true;
			break;
		}
	}
	FRICTION = (check) ? -200.0f : -80.0f;

	std::cout << FRICTION << std::endl;
}

bool Ball::checkWaterDrop()
{
	for (auto water : map->waterTiles)
	{
		if (Collision::checkCollisionTile(this, water))
		{
			waterDrop = true;
			break;
		}
	}
	return waterDrop;
}
