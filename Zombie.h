#pragma once
#include "GameObject.h"
#include "HitBox.h"

class Player;

class Zombie : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chase,
		Crawler,
	};

	static const int TotalTypes = 3;

protected:
	Types type = Types::Bloater;

	sf::Sprite body;
	std::string texId;

	sf::Vector2f direction;

	int maxHp = 0;
	float speed = 0.0f;
	int damage = 0;
	float attackIntervale = 0.0f;

	int hp;

	Player* player;

	HitBox hitBox;

public:
	Zombie(const std::string& name = "");
	virtual ~Zombie() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}
};