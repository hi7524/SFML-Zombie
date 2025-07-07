#include "stdafx.h"
#include "Tilemap.h"

Tilemap::Tilemap(const std::string& name)
	: GameObject(name)
{
}

void Tilemap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);

	sf::Vector2f posOffset[4] =
	{
		{ 0.0f, 0.0f },
		{ size.x, 0.0f },
		{ size.x, size.y },
		{ 0.0f, size.y }
	};

	sf::Vector2f texCoords[4] =
	{
		{ 0.0f, 0.0f },
		{ 50.0f, 0.0f },
		{ 50.0f, 50.0f },
		{ 0.0f, 50.0f }
	};

	for (int i = 0; i < count.y; i++)
	{
		for (int j = 0; j < count.x; j++)
		{
			int texIndex = Utils::RandomRange(0, 3);

			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;
			}

			int quadIndex = i * count.x + j; // 이차원 좌표계를 일차원 좌표계로 변환시 사용
			sf::Vector2f quadPos(j * size.x, i * size.y);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = quadPos + posOffset[k];
				va[vertexIndex].texCoords = texCoords[k];
				va[vertexIndex].texCoords.y += texIndex * 50.0f;
			}
		}
	}
}

void Tilemap::UpdateTransform()
{
	transform = sf::Transform::Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
	// 역순 적용, 순서 중요
}

void Tilemap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}

void Tilemap::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	UpdateTransform();
}

void Tilemap::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	UpdateTransform();
}

void Tilemap::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	UpdateTransform();
}

void Tilemap::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		sf::FloatRect rect;
		rect.width = cellCount.x * cellSize.x;
		rect.height = cellCount.y * cellSize.y;

		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
	}

	UpdateTransform();
}

void Tilemap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;

	Set({ 50, 50 }, { 50.0f, 50.0f });
}

void Tilemap::Release()
{
}

void Tilemap::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetId);

	SetOrigin(Origins::MC);
	SetScale({ 1.0f, 1.0f });
	SetPosition({ 0.0f, 0.0f });
}

void Tilemap::Update(float dt)
{
}

void Tilemap::Draw(sf::RenderWindow& window)
{
	// 텍스쳐를 별개로 넘겨주어야 함
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);
}