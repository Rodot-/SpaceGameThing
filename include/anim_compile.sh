g++ -c animTesting.cpp gameAssets.cpp AnimationBase.cpp PlayerShip.cpp assetManager.cpp Forces.cpp integrators.cpp TheHeavens.cpp Registries.cpp Collision.cpp HitBox.cpp  
g++ animTesting.o PlayerShip.o gameAssets.o AnimationBase.o assetManager.o Forces.o integrators.o TheHeavens.o Registries.o Collision.o HitBox.o -o testAnim -lsfml-graphics -lsfml-window -lsfml-system -fopenmp 
#./runGame
