#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"


Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Zombie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Zombie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Zombie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetType(type);
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	body.setTexture(TEXTURE_MGR.Get(texId));
	SetOrigin(Origins::MC);
	SetPosition({ 0.0f, 0.0f });
	SetRotation(0.0f);
	SetScale({ 1.0f, 1.0f });
}

void Zombie::Update(float dt)
{
	direction = Utils::GetNormal(player->GetPosition() - GetPosition());
	SetRotation(Utils::Angle(direction));

	if (Utils::Distance(player->GetPosition(), GetPosition()) > 0.5f)
	{
		SetPosition(GetPosition() + direction * speed * dt);
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Zombie::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Bloater:
		texId = "graphics/bloater.png";
		maxHp = 200;
		speed = 50.0f;
		damage = 100.0f;
		attackIntervale = 1.0f;

		break;
	case Types::Chase:
		texId = "graphics/chaser.png";
		maxHp = 100;
		speed = 100.0f;
		damage = 100.0f;
		attackIntervale = 1.0f;
		break;

	case Types::Crawler:
		texId = "graphics/crawler.png";
		maxHp = 100;
		speed = 50.0f;
		damage = 100.0f;
		attackIntervale = 1.0f;
		break;
	}
}