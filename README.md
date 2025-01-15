# MasterPiece.SDL Overview:

This project represents one of my initial forays into game development, crafted many years ago. Initially designed for Windows 98 using C++ and DirectX, it was subsequently adapted to utilize SDL. An intentional misspelling is present in the game's logo screen—retained to preserve the original's charm—I'm aware it should be "Masterpiece."

Gameplay Instructions:

Navigate the blocks using the arrow keys. To rearrange the blocks, press A or S. Your goal is to align at least three blocks in a horizontal, vertical, or diagonal sequence to clear a line. The challenge is to prevent the grid from becoming completely filled by lasting as long as possible.

Compile Instructions:

```bash
mkdir build && cd build
cmake ..
make -j4
```

TO run the  program copy exe andd resource directory to folder

```bash
mkdir MasterPiece
cp MasterPiece.SDL MasterPiece/
cp -rf ../img MasterPiece/img/
cd MasterPiece
./MasterPiece.SDL
```

![image](https://github.com/user-attachments/assets/c33f737f-91e1-41d3-8be7-fff46d421872)
![image](https://github.com/user-attachments/assets/01772032-880b-47b7-92e3-e21d803e2df2)
