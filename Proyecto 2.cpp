#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <fstream>


class Album {
public:
    Album(int numAlbums) {
        totalAlbums = numAlbums;
        totalPacks = totalAlbums * packsPerAlbum;
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
            packs.push_back({ pack, false }); // Agrega el sobre como no abierto
        }
    }

    void OpenPack(int packNumber) {
        if (packNumber < 1 || packNumber > totalPacks) {
            std::cout << "Numero de sobre no valido." << std::endl;
            return;
        }

        std::vector<int>& pack = packs[packNumber - 1].first;

        std::cout << "Contenido del sobre " << packNumber << ": ";
        for (int i = 0; i < stickersPerPack; ++i) {
            std::cout << pack[i] << " ";
            AddToAlbum(pack[i]);
        }
        std::cout << std::endl;

        packs[packNumber - 1].second = true; // Marca el sobre como abierto
    }

    void AddToAlbum(int sticker) {
        if (album.count(sticker) == 0) {
            album[sticker] = true;
        }
        else {
            duplicates[sticker]++;
        }
    }

    void ShowAlbum() const {
        std::cout << "Album:" << std::endl;
        for (int i = 1; i <= 25; ++i) {
            if (album.count(i) > 0) {
                std::cout << i << " ";
            }
            else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }

    void ShowDuplicates() const {
        std::cout << "Cromos repetidos:" << std::endl;
        for (const auto& entry : duplicates) {
            std::cout << "Cromo " << entry.first << ": " << entry.second << " repetidos." << std::endl;
        }
    }

    void ShowMissingStickers() const {
        std::cout << "Cromos faltantes:" << std::endl;
        for (int i = 1; i <= 25; ++i) {
            if (album.count(i) == 0) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
    }

    void ShowOpenedPacks() const {
        std::cout << "Sobres abiertos:" << std::endl;
        for (int i = 0; i < totalPacks; ++i) {
            if (packs[i].second) {
                std::cout << "Sobre " << i + 1 << " ";
            }
        }
        std::cout << std::endl;
    }

    void ShowRemainingPacks() const {
        std::cout << "Sobres disponibles:" << std::endl;
        for (int i = 0; i < totalPacks; ++i) {
            if (!packs[i].second) {
                std::cout << "Sobre " << i + 1 << " " << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void Finish() const {
        std::cout << "Album completado!" << std::endl;
        ShowDuplicates();
    }

    int getTotalPacks() const {
        return totalPacks;
    }

    bool isAlbumComplete() {
    for (int i = 1; i <= 25; ++i) {
        if (album.count(i) == 0) {
            return false; // If any sticker is missing, the album is not complete
        }
    }
    return true; // If all stickers are present, the album is complete
}

private:
    static const int stickersPerAlbum = 25;
    int totalPacks = totalAlbums * packsPerAlbum;
    static const int stickersPerPack = 5;
    static const int packsPerAlbum = 5;
    
    int totalAlbums;
    int totalStickers;
    std::vector<int> stickers;
    std::vector<std::pair<std::vector<int>, bool>> packs; // Cambio a par para incluir estado de apertura
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
        std::cout << "3. Mostrar Album.\n";
        std::cout << "4. Mostrar cromos repetidos.\n";
        std::cout << "5. Mostrar cromos faltantes.\n";
        std::cout << "6. Mostrar sobres abiertos.\n";
        std::cout << "7. Mostrar sobres disponibles.\n";
        std::cout << "8. Terminar.\n";
        std::cout << "9. Reiniciar.\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> option;

        
        switch (option) {
        case 1:
            album.ShowRemainingPacks();
            break;
        case 2:
            int packNumber;
            std::cout << "Ingrese el numero del sobre a abrir: ";
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
            album.ShowOpenedPacks();
            break;
        case 7:
            album.ShowRemainingPacks();
            break;
        case 8:
            album.Finish();
            break;
        case 9:
            std::cout << "Reiniciando datos..." << std::endl;
            album = Album(numAlbums);
            break;
        default:
            std::cout << "Opcion no valida." << std::endl;
            break;
        }
    if (album.isAlbumComplete()) {
        std::cout << "¡El álbum está completo!" << std::endl;
        album.ShowDuplicates();
        album.ShowRemainingPacks();
        break; // Termina el bucle, terminando así el programa
    }
    } while (option != 8);

    return 0;
}
