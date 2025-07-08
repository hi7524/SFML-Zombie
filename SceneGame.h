#pragma once
#include "Scene.h"

class Player;
class Zombie;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	std::list<Zombie*> zombieList; // 활성화된 좀비
	std::list<Zombie*> zombiePool; // 비활성화된 좀비

	sf::Sprite cursor;

public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Draw(sf::RenderWindow& window) override;
	void Update(float dt) override;

	void SpawnZombies(int count);

	const std::list<Zombie*>& GetZombies() const
	{
		return zombieList;
	}
};