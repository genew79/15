#pragma once
#include <SFML/Graphics.hpp>


class Assets
{
public:
	sf::Font font;
public:
	static Assets& Instance()
	{
		// согласно стандарту, этот код ленивый и потокобезопасный
		static Assets s;
		return s;
	}
	void Load();
private:
	Assets() {};
	~Assets() {};
	// необходимо также запретить копирование
	Assets(Assets const&) = delete; // реализация не нужна
	Assets& operator= (Assets const&) = delete;  // и тут
};
