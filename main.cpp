#include "App.h"

void GenerateLevel(std::string name);
bool FileExist(std::string name);

int main()
{
	std::string name;

	std::cout << "Podaj nazwe poziomu: ";
	std::cin >> name;

	if(!FileExist("maps/" + name + ".map")) GenerateLevel(name);


	App app(800, 600, false, name);
	app.Run();
	return 0;
}

void GenerateLevel(std::string name)
{
	MapFile* map = new MapFile();

	std::cout << "Podany poziom nie istnieje" << std::endl;
	std::cout << "Podaj szerokosc nowego poziomu: ";
	std::cin >> map->w;
	std::cout << "Podaj wysokosc nowego poziomu: ";
	std::cin >> map->h;

	map->x = 16;
	map->y = 16;

	std::ofstream file(name = "maps/" + name + ".map", std::ios::binary); 
	file.write((char*)(map), sizeof(MapFile));
	file.close();

	delete map;
}

bool FileExist(std::string name)
{
        FILE* plik;
        plik = fopen(name.c_str(), "r");
        if ( plik )
        {
            fclose(plik);
            return true;
        }
        //fclose(plik);
        return false;
}