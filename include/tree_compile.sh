g++ -c treeTest.cpp gameAssets.cpp AnimationBase.cpp assetManager.cpp Forces.cpp integrators.cpp TheHeavens.cpp Registries.cpp WorldGeometry.cpp QuadTree.cpp Worlds.cpp Collision.cpp HitBox.cpp
g++ treeTest.o gameAssets.o AnimationBase.o assetManager.o Forces.o integrators.o TheHeavens.o Registries.o WorldGeometry.o QuadTree.o Worlds.o Collision.o HitBox.o -o testTree -lsfml-graphics -lsfml-window -lsfml-system -fopenmp
#./runGame
