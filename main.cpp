#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <fstream>

// Verifica si un archivo existe
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

class Album {
public:
    // Constructor
    Album(int numAlbums) {
        totalAlbums = numAlbums;
        totalPacks = totalAlbums * packsPerAlbum;
        totalStickers = totalAlbums * stickersPerAlbum;
        GenerateStickers();
        GeneratePacks();
    }

    // Guarda duplicados en archivo
    void BackupDuplicates() const {
        std::ofstream file("duplicates.txt");
        if (file.is_open()) {
            // Guarda los cromos repetidos
            for (const auto& pair : duplicates) {
                if (pair.second > 0) { 
                    file << pair.first << " " << pair.second << std::endl;
                }
            }
        } else {
            std::cerr << "Error al abrir el archivo de duplicados." << std::endl;
        }
    }

    // Guarda el contenido del álbum
    void BackupAlbum() const {
        std::ofstream file("album.txt");
        if (file.is_open()) {
            // Guarda los cromos en el álbum
            for (int i = 1; i <= stickersPerAlbum; ++i) {
                if (album.count(i) > 0) {
                    file << i << " ";
                }
            }
            file << std::endl;
        } else {
            std::cerr << "Error al abrir el archivo del álbum." << std::endl;
        }
    }

    // Guarda todos los datos
    void BackupData() const {
        std::ofstream file("backup.txt");
        if (file.is_open()) {
            // Guarda el estado del álbum
            file << totalAlbums << " " << totalPacks << " " << totalStickers << std::endl;

            // Guarda los stickers
            for (int sticker : stickers) {
                file << sticker << " ";
            }
            file << std::endl;

            // Guarda el estado de los packs
            for (const auto& pack : packs) {
                file << pack.second << " ";
            }
            file << std::endl;
        } else {
            std::cerr << "Error al abrir el archivo de respaldo." << std::endl;
        }
    }

    // Carga todos los datos desde archivos
    void LoadData() {
        // 1) Carga el archivo de respaldo general
        std::ifstream file("backup.txt");
        if (file.is_open()) {
            // Carga el estado del álbum
            file >> totalAlbums >> totalPacks >> totalStickers;

            // Carga los stickers
            stickers.resize(totalStickers);
            for (int &sticker : stickers) {
                file >> sticker;
            }

            // Carga el estado de los packs
            packs.resize(totalPacks);
            for (auto &pack : packs) {
                file >> pack.second;
            }
        } else {
            std::cerr << "No se encontró un archivo de respaldo. Iniciando con datos predeterminados." << std::endl;
        }

        // 2) Carga el álbum
        std::ifstream albumFile("album.txt");
        if (albumFile.is_open()) {
            int sticker;
            while (albumFile >> sticker) {
                album[sticker] = true;
            }
        } else {
            std::cerr << "Error al abrir el archivo del álbum." << std::endl;
        }

        // 3) Carga duplicados
        std::ifstream duplicatesFile("duplicates.txt");
        if (duplicatesFile.is_open()) {
            int sticker, count;
            while (duplicatesFile >> sticker >> count) {
                duplicates[sticker] = count; // Asignamos correctamente a 'duplicates'
            }
        } else {
            std::cerr << "Error al abrir el archivo de duplicados." << std::endl;
        }
    }

    // Genera todos los stickers y los mezcla
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

    // Genera los packs con los stickers mezclados
    void GeneratePacks() {
        for (int i = 0; i < totalPacks; ++i) {
            std::vector<int> pack;
            for (int j = 0; j < stickersPerPack; ++j) {
                pack.push_back(stickers[i * stickersPerPack + j]);
            }
            packs.push_back({ pack, false }); // Cada sobre se inicia como "no abierto"
        }
    }

    // Abre un sobre y agrega su contenido al álbum
    void OpenPack(int packNumber) {
        if (packNumber < 1 || packNumber > totalPacks) {
            std::cout << "Numero de sobre no valido." << std::endl;
            return;
        }

        std::vector<int> &pack = packs[packNumber - 1].first;

        std::cout << "Contenido del sobre " << packNumber << ": ";
        for (int i = 0; i < stickersPerPack; ++i) {
            std::cout << pack[i] << " ";
            AddToAlbum(pack[i]);
        }
        std::cout << std::endl;

        packs[packNumber - 1].second = true; // Marca el sobre como abierto
    }

    // Agrega un sticker al álbum o lo cuenta como duplicado
    void AddToAlbum(int sticker) {
        if (album.count(sticker) == 0) {
            album[sticker] = true;
        } else {
            duplicates[sticker]++;
        }
    }

    // Muestra el estado del álbum
    void ShowAlbum() const {
        std::cout << "Album:" << std::endl;
        for (int i = 1; i <= stickersPerAlbum; ++i) {
            if (album.count(i) > 0) {
                std::cout << i << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }

    // Muestra los duplicados
    void ShowDuplicates() const {
        std::cout << "Cromos repetidos:" << std::endl;
        for (const auto& entry : duplicates) {
            std::cout << "Cromo " << entry.first << ": " 
                      << entry.second << " repetidos." << std::endl;
        }
    }

    // Muestra los stickers que faltan
    void ShowMissingStickers() const {
        std::cout << "Cromos faltantes:" << std::endl;
        for (int i = 1; i <= stickersPerAlbum; ++i) {
            if (album.count(i) == 0) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
    }

    // Muestra los sobres que se han abierto
    void ShowOpenedPacks() const {
        std::cout << "Sobres abiertos:" << std::endl;
        for (int i = 0; i < totalPacks; ++i) {
            if (packs[i].second) {
                std::cout << "Sobre " << i + 1 << " ";
            }
        }
        std::cout << std::endl;
    }

    // Muestra los sobres que todavía no se han abierto
    void ShowRemainingPacks() const {
        std::cout << "Sobres disponibles:" << std::endl;
        for (int i = 0; i < totalPacks; ++i) {
            if (!packs[i].second) {
                std::cout << "Sobre " << i + 1 << std::endl;
            }
        }
        std::cout << std::endl;
    }

    // Muestra mensaje final
    void Finish() const {
        std::cout << "Programa terminado!" << std::endl;
        ShowDuplicates();
    }

    // Devuelve la cantidad total de sobres generados
    int getTotalPacks() const {
        return totalPacks;
    }

    // Verifica si el álbum está completo
    bool isAlbumComplete() {
        for (int i = 1; i <= stickersPerAlbum; ++i) {
            if (album.count(i) == 0) {
                return false; 
            }
        }
        return true;
    }

private:
    // Constantes
    static const int stickersPerAlbum = 25;
    static const int stickersPerPack  = 5;
    static const int packsPerAlbum    = 5;

    // Atributos
    int totalAlbums;
    int totalPacks;      // Se elimina la inicialización directa (antes: = totalAlbums * packsPerAlbum)
    int totalStickers;
    
    // Estructuras de datos
    std::vector<int> stickers;
    // Para cada sobre, guardamos {vector de stickers, bool de si está abierto}
    std::vector<std::pair<std::vector<int>, bool>> packs;
    
    // 'album' indica si el cromo está en el álbum (true) o no
    std::map<int, bool> album;
    // 'duplicates' guarda cuántas copias extra de cada cromo tenemos
    std::map<int, int> duplicates;
};

int main() {

    int numAlbums;
    Album album(1);

    // Si hay respaldo, preguntar si se desea cargar
    if(fileExists("backup.txt") && fileExists("album.txt") && fileExists("duplicates.txt")) {
        char option;
        do {
            std::cout << "Se ha encontrado un archivo de respaldo. ¿Desea cargarlo? (s/n): ";
            std::cin >> option;
        } while (option != 's' && option != 'n');

        if (option == 's') {
            album.LoadData();
        } else {
            // Elimina archivos de respaldo
            remove("backup.txt");
            remove("album.txt");
            remove("duplicates.txt");

            std::cout << "Ingrese la cantidad de Albumes a producir: ";
            std::cin >> numAlbums;

            album = Album(numAlbums); 
        }
    } 
    else {
        std::cout << "Ingrese la cantidad de Albumes a producir: ";
        std::cin >> numAlbums;

        album = Album(numAlbums);
    }

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
            case 2: {
                int packNumber;
                std::cout << "Ingrese el numero del sobre a abrir: ";
                std::cin >> packNumber;
                album.OpenPack(packNumber);
                break;
            }
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

        // Verifica si el álbum está completo
        if (album.isAlbumComplete()) {
            std::cout << "¡El álbum está completo!" << std::endl;
            album.ShowDuplicates();
            album.ShowRemainingPacks();
            break; // Termina el bucle principal
        }

        // Respalda datos en cada iteración
        album.BackupData();
        album.BackupAlbum();
        album.BackupDuplicates();

    } while (option != 8);

    return 0;
}