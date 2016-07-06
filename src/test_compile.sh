g++ -c testing.cpp gameAssets.cpp
g++ testing.o gameAssets.o -o testGame -lsfml-graphics -lsfml-window -lsfml-system -fopenmp
#./runGame
