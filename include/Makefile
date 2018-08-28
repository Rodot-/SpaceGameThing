CC=g++
SOURCES=gameAssets.cpp assetManager.cpp Registries.cpp HitBox.cpp AnimationBase.cpp Forces.cpp Worlds.cpp WorldGeometry.cpp integrators.cpp Collision.cpp QuadTree.cpp TheHeavens.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system


gameAssets.o: gameAssets.cpp World/gameAssets.h
	$(CC) -c gameAssets.cpp

assetManager.o: assetManager.cpp World/assetManager.h
	$(CC) -c assetManager.cpp

Registries.o: Registries.cpp Accounting/Registries.h
	$(CC) -c Registries.cpp

HitBox.o: HitBox.cpp World/HitBox.h
	$(CC) -c HitBox.cpp

AnimationBase.o: AnimationBase.cpp Anim/AnimationBase.h
	$(CC) -c AnimationBase.cpp

Forces.o: Forces.cpp World/Forces.h
	$(CC) -c Forces.cpp

Worlds.p: Worlds.cpp World/Worlds.h
	$(CC) -c Worlds.cpp

WorldGeometry.o: WorldGeometry.cpp World/WorldGeometry.h
	$(CC) -c WorldGeometry.cpp

Collision.o: Collision.cpp Math/Collision.h
	$(CC) -c Collision.cpp

QuadTree.o: QuadTree.cpp Math/QuadTree.h
	$(CC) -c QuadTree.cpp

integrators.o: integrators.cpp Math/integrators.h
	$(CC) -c integrators.cpp

TheHeavens.o: TheHeavens.cpp World/TheHeavens.h
	$(CC) -c TheHeavens.cpp

all: $(SOURCES) 
	$(CC) -c $(SOURCES)

tree: $(OBJECTS)
	$(CC) treeTest.o $(OBJECTS) -o testTree $(LDFLAGS)

treeTest.o: treeTest.cpp
	$(CC) -c treeTest.cpp

anim: $(OBJECTS)
	$(CC) animTesting.o $(OBJECTS) -o testAnim $(LDFLAGS)

animTesting.o: animTesting.cpp
	$(CC) -c animTesting.cpp

