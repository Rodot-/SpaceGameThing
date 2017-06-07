g++ -c worldTesting.cpp gameAssets.cpp AnimationBase.cpp PlayerShip.cpp assetManager.cpp Forces.cpp integrators.cpp QuadTree.cpp Registries.cpp Worlds.cpp WorldGeometry.cpp Collision.cpp HitBox.cpp
g++ worldTesting.o PlayerShip.o gameAssets.o AnimationBase.o assetManager.o Forces.o integrators.o TheHeavens.o Registries.o QuadTree.o Worlds.o WorldGeometry.o Collision.o HitBox.o -o testWorld -lsfml-graphics -lsfml-window -lsfml-system -fopenmp
#./runGame
