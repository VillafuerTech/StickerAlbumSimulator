#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;

random_device rd;
mt19937 g(rd());
class Album {
public:
   Album(int numAlbums) {
        totalAlbums = numAlbums;
        totalPacks = totalAlbums * 5; // Initialize totalPacks here
        totalStickers = numAlbums * stickersPerAlbum;
        GenerateStickers();
        GeneratePacks();
    }

    void GenerateStickers() {
    for (int i = 0; i < totalAlbums; ++i) {
        for (int j = 1; j <= stickersPerAlbum; ++j) {
            stickers.push_back(j);
        }
    }
    std::random_device rd;
    std::mt19937 g(time(0));
    std::shuffle(stickers.begin(), stickers.end(), g);
}
    
    void GeneratePacks() {
        for (int i = 0; i < totalPacks; ++i) {
            std::vector<int> pack;
            for (int j = 0; j < stickersPerPack; ++j) {
                pack.push_back(stickers[i * stickersPerPack + j]);
            }
            packs.push_back(pack);
        }
    }

    void OpenPack(int packNumber) {
        if (packNumber < 1 || packNumber > totalPacks) {
            std::cout << "Numero de sobre no valido." << std::endl;
            return;
        }

        std::vector<int> pack = packs[packNumber - 1];

        std::cout << "Contenido del sobre " << packNumber << ": ";
        for (int i = 0; i < stickersPerPack; ++i) {
            std::cout << pack[i] << " ";
            AddToAlbum(pack[i]);
        }
        std::cout << std::endl;
    }

    void AddToAlbum(int sticker) {
        if (album.count(sticker) == 0) {
            album[sticker] = true;
        }
        else {
            duplicates[sticker]++;
        }
    }

    void ShowAlbum() {
        std::cout << "Album:" << std::endl;
        for (int i = 1; i <= totalStickers; ++i) {
            if (album.count(i) > 0) {
                std::cout << i << " ";
            }
            else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }

    void ShowDuplicates() {
        std::cout << "Cromos repetidos:" << std::endl;
        for (const auto& entry : duplicates) {
            std::cout << "Cromo " << entry.first << ": " << entry.second << " repetidos." << std::endl;
        }
    }

    void ShowMissingStickers() {
        std::cout << "Cromos faltantes:" << std::endl;
        for (int i = 1; i <= totalStickers; ++i) {
            if (album.count(i) == 0) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
    }

    void Finish() {
        std::cout << "�lbum completado!" << std::endl;
        ShowDuplicates();
    }

    int getTotalPacks(){
        return totalPacks;
    }
private:
    static const int stickersPerAlbum = 25;
    int totalPacks = totalAlbums*5;
    static const int stickersPerPack = 5;

    int totalAlbums;
    int totalStickers;
    std::vector<int> stickers;
    std::vector<std::vector<int>> packs;
    std::map<int, bool> album;
    std::map<int, int> duplicates;
};

int main() {
    int numAlbums;
    std::cout << "Ingrese la cantidad de Albumes a producir: ";
    std::cin >> numAlbums;

    Album album(numAlbums);

    int option;
    do {
        std::cout << "\nOpciones:\n";
        std::cout << "1. Mostrar sobres disponibles.\n";
        std::cout << "2. Abrir sobre.\n";
        std::cout << "3. Mostrar �lbum.\n";
        std::cout << "4. Mostrar cromos repetidos.\n";
        std::cout << "5. Mostrar cromos faltantes.\n";
        std::cout << "6. Terminar.\n";
        std::cout << "7. Reiniciar.\n";
        std::cout << "Seleccione una opci�n: ";
        std::cin >> option;

        switch (option) {
        case 1:
            std::cout << "Sobres disponibles: " << album.getTotalPacks() << std::endl;
            break;
        case 2:
            int packNumber;
            std::cout << "Ingrese el n�mero del sobre a abrir: ";
            std::cin >> packNumber;
            album.OpenPack(packNumber);
            break;
        case 3:
            album.ShowAlbum();
            break;
        case 4:
            album.ShowDuplicates();
            break;
        case 5:
            album.ShowMissingStickers();
            break;
        case 6:
            album.Finish();
            break;
        case 7:
            std::cout << "Reiniciando datos..." << std::endl;
            album = Album(numAlbums);
            break;
        default:
            std::cout << "Opci�n no v�lida." << std::endl;
            break;
        }
    } while (option != 6);

    return 0;
}
