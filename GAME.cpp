#include "Game.h"
using namespace std;


bool CheckMapExtension(string mapFileName)
{
	//									reverse
	size_t extensionIndex = mapFileName.rfind(".txt");
	if (extensionIndex != -1 && mapFileName.length() - 4 == extensionIndex && mapFileName.length() > 4)
		return true;
	else
		return false;
}

//2. Проверяем есть ли такой файл(open)
bool IsFileExist(string mapFileName)
{
	ifstream mapFile;
	mapFile.open(mapFileName);
	if (mapFile.is_open())
	{
		mapFile.close();
		return true;
	}
	else
	{
		return false;
	}
	// Открываем файл (на чтение из файла) ?
	// Если он открылся, то закрываем его и возвращаем правду
	// Если нет, то мы возвращаем ложь
}

void GetMap(Map& map, string mapFileName)
{
	ifstream mapFile;
	map.h = 0;
	map.w = 0;
	mapFile.open(mapFileName);
	string temp;
	while (!mapFile.eof()) // Так нужно пройтись N раз
	{
		getline(mapFile, temp);
		map.w = temp.length();
		map.h++;
	}
	string* tempMap = new string[map.h];
	mapFile.close();
	mapFile.open(mapFileName);
	int i = 0;
	while (!mapFile.eof())
	{
		getline(mapFile, temp);
		tempMap[i] = temp;
		i++;
	}
	mapFile.close();
	map.map = tempMap;
}



Coord FindPlayer(Map &map)
{
	Coord playerPosition{ 0, 0 };
	for (int i = 0; i < map.h; i++)
	{
		int playerX = map.map[i].find('P');
		if (playerX != -1)
		{
			playerPosition.x = playerX;
			playerPosition.y = i;
			return playerPosition;
		}
	}
	return playerPosition;
}



/// Начинаем писать игровой цикл
/// conio
/// _kbhit //  _getch
/// 


bool CheckNextPosition(Coord nextPosition, Map map)
{
	return (map.map[nextPosition.y][nextPosition.x] != '#');
}

void HandleTransLation(Coord nextPosition, Map& map)
{	
	switch (map.map[nextPosition.y][nextPosition.x])
	{
	case 'K':
		swap(map.map[map.player.position.y][map.player.position.x], map.map[nextPosition.y][nextPosition.x]);
		map.map[map.player.position.y][map.player.position.x] = ' ';
		map.player.position = nextPosition;
		map.player.currentNumberOfKeys++;
		break;
	default:
		swap(map.map[map.player.position.y][map.player.position.x], map.map[nextPosition.y][nextPosition.x]);
		map.player.position = nextPosition;
		break;
	}
	
	
	
	map.DrawMap();
}
void StartGame(string mapFileName)
{
	bool isActive = true;
	Map map;
	map.maxNumberOfKeys = 1;            //YOU HAVE TO CHANGE IT 
	map.player.currentNumberOfKeys = 0;
	CLS;
	GetMap(map, mapFileName);
	// CheckMap()
	// Если у нас какие-то проблемы (Проверить что персонаж 1, проверить что выход 1,
	// проверить что все закрыто стенками, проверить что ключей как минимум больше 0)
	// Если что-то не так из этого списка -> выводите сообщение об ошибке (что конкретно) 
	// и используете функцию exit(1) для завершения работы приложения
	
	map.player.position = FindPlayer(map);
	
	CursorHide(FALSE, 20);
	map.DrawMap();   // по запросу 
	// нужно проинициалиолвать игрока
	//Нужно найти координаты игрока на карте
	//и заполнить нашу стурктуру 
	while (isActive)
	{
		if (_kbhit())   // is button pressed  on?
		{
			int key = _getch();
			switch (key)
			{
			case _KEY::ESC:
				isActive = false;
				break;
			case _KEY::RIGHT:
			case 'd':
			case 'D':
			case 'в':
			case 'В':
				
				if (CheckNextPosition(Coord{ map.player.position.x+1, map.player.position.y }, map))
				{
					HandleTransLation(Coord{ map.player.position.x+1, map.player.position.y }, map);
					
				}
				break;
			case _KEY::LEFT:
			case 'a':
			case 'A':
			case 'ф':
			case 'Ф':
				if (CheckNextPosition(Coord{ map.player.position.x - 1, map.player.position.y }, map))
				{
					HandleTransLation(Coord{ map.player.position.x - 1, map.player.position.y }, map);
				}
				
				break;

			case _KEY::UP:
			case 'w':
			case 'W':
			case 'ц':
			case 'Ц':
				if (CheckNextPosition(Coord{ map.player.position.x, map.player.position.y-1 }, map))
				{
					HandleTransLation(Coord{ map.player.position.x, map.player.position.y-1 }, map);
				}

				break;
			case _KEY::DOWN:
			case 's':
			case 'S':
			case 'ы':
			case 'Ы':
				if (CheckNextPosition(Coord{ map.player.position.x, map.player.position.y+1 }, map))
				{
					HandleTransLation(Coord{ map.player.position.x, map.player.position.y+1 }, map);
				}

				break;
			default: break;
			}
		}

	}
}

// TODO: 2. Проверяем файл на существование
// Написали каркас нашей игры
int main()
{
	setlocale(LC_ALL, "RUS");
	string mapFileName;
	cout << "Введите имя файла с картой в формате .txt: ";
	cin >> mapFileName;
	if (!CheckMapExtension(mapFileName) || !IsFileExist(mapFileName))
	{
		cout << "Файл не подходит или его не существует. Введите файл формата .txt и убедитесь, что он существует.";
		return 1;
	}
	else
	{
		StartGame(mapFileName);
	}
}
