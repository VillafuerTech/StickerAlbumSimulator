
# Sticker Album Simulator

This program simulates the process of collecting and organizing stickers into albums. It offers various functionalities such as generating stickers, opening packs, managing duplicates, and backing up the album’s state. The program is interactive and allows users to track their sticker collection in real-time.

---

## Features

1. **Album Generation**:
   - Create albums with a specified number of stickers and packs.
   - Randomly generate stickers and distribute them across packs.
   
2. **Pack Management**:
   - Open packs to reveal their contents.
   - Track opened and remaining packs.
   
3. **Album Tracking**:
   - Display stickers in the album.
   - Identify missing stickers.
   - Detect duplicate stickers.
   
4. **Backup and Restore**:
   - Save the current state of the album, duplicates, and packs to files.
   - Restore data from previous backups.
   
5. **Completion Check**:
   - Automatically detect when the album is complete.
   
6. **Interactive Menu**:
   - Perform operations such as opening packs, showing duplicates, viewing the album, and restarting the collection process.

---

## How to Use

### Prerequisites
- A C++ compiler (e.g., GCC).
- Basic knowledge of command-line usage.

### Compilation
To compile the program, run:
```bash
g++ -o StickerAlbumSimulator main.cpp
```

### Running the Program
Execute the compiled program:
```bash
./StickerAlbumSimulator
```

### Program Flow
1. If backup files (`backup.txt`, `album.txt`, `duplicates.txt`) are found, the program offers an option to load existing data.
2. If no backup is found or the user declines to load it, the program initializes a new album.
3. Users can interact with the program through a menu:
   - Open packs.
   - View album status.
   - Check duplicates and missing stickers.
   - Backup data and continue later.
4. The program ends when the album is complete or the user chooses to exit.

---

## Files Generated

- `album.txt`: Contains the stickers in the album.
- `duplicates.txt`: Lists duplicate stickers and their counts.
- `backup.txt`: Stores the program’s state for resumption.

---

## Program Menu Options

1. **Show Remaining Packs**: Displays unopened packs.
2. **Open Pack**: Opens a specified pack and adds its stickers to the album.
3. **Show Album**: Displays collected stickers in the album.
4. **Show Duplicates**: Lists stickers that are duplicates.
5. **Show Missing Stickers**: Lists stickers not yet collected.
6. **Show Opened Packs**: Displays packs that have been opened.
7. **Show Remaining Packs**: Re-lists unopened packs.
8. **Terminate**: Exits the program.
9. **Restart**: Resets the album and packs to the initial state.

---

## Example Interaction
```
Ingrese la cantidad de Albumes a producir: 1

Opciones:
1. Mostrar sobres disponibles.
2. Abrir sobre.
3. Mostrar Album.
4. Mostrar cromos repetidos.
5. Mostrar cromos faltantes.
6. Mostrar sobres abiertos.
7. Mostrar sobres disponibles.
8. Terminar.
9. Reiniciar.
Seleccione una opcion: 2
Ingrese el numero del sobre a abrir: 1
Contenido del sobre 1: 5 12 8 3 19
```

---

## Future Enhancements

- Add a graphical user interface (GUI) for better user experience.
- Enable online multiplayer features to trade stickers with other users.
- Support for custom album sizes and sticker designs.

---

## License

This project is licensed under the MIT License.

Enjoy completing your sticker albums! 🎉
