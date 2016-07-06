g++ -c testing.cpp gameAssets.cpp assetManager.cpp TheHeavens.cpp Forces.cpp integrators.cpp
g++ testing.o gameAssets.o assetManager.o TheHeavens.o Forces.o integrators.o -o testGame -lsfml-graphics -lsfml-window -lsfml-system -fopenmp
#./runGame
