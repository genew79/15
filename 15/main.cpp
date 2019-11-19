#include "Assets.h"
#include "GameModel.h"
#include "GameRender.h"
#include "GameController.h"

int main()
{
	Assets::Instance().Load();					// Загружаем ресурсы
	GameModel game;								// Создаем модель игры
	GameRender render(&game);					// Создаем представление
	GameController controller(&game, &render);	// Создаем контроллер
	controller.Run();							// Запускаем игру
	return 0;
}
