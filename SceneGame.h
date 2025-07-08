#pragma once
#include "Scene.h"

class Player;
class Zombie;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	std::list<Zombie*> zombieList; // Ȱ��ȭ�� ����
	std::list<Zombie*> zombiePool; // ��Ȱ��ȭ�� ����

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