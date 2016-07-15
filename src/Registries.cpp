
#include "Accounting/Registries.h"
#include <fstream>

//The Main Game registry class

sf::Texture& GameRegistry::GetTexture(std::string name) {

	return GameRegistry::_textureRegistry.Get(name);
}

Animation& GameRegistry::GetAnimation(std::string name) {

	return GameRegistry::_animationRegistry.Get(name);
}

TextureRegistry GameRegistry::_textureRegistry;

AnimationRegistry GameRegistry::_animationRegistry;


//Registry template classes
template <class T>
Registry<T>::Registry(void) {}

template <class T>
T& Registry<T>::Get(std::string name) {

	if (Contains(name)){}
	else 
		Load(name);
	return _contents[name];
}

template <class T>
bool Registry<T>::Contains(std::string name) const {
	
	typename std::map<std::string, T>::const_iterator item = _contents.find(name);
	if (item == _contents.end())
		return false;
	return true;
}



void TextureRegistry::Load(std::string name) {

		sf::Texture t;
		if (t.loadFromFile(name) )
			_contents[name] = t;
		else {
			printf("ERROR: Texture Not Found!\n");
			printf("       Could Not Find \"%s\"\n", name.c_str());
			exit(1);
		}
}

struct AnimParams {

	std::string TileSheet;
	int FPS, height, width, count, method_attr;
	std::string method; //row, column
};

void AnimationRegistry::Load(std::string name) {
	//Lets do a little test using my format
	AnimParams params;
	std::ifstream animConfig(name.c_str());
	std::string line;
	std::string param;
	std::string value;
	bool onValue = false;
	while (std::getline(animConfig, line)) {
		char p[16];
		char v[16];
		//sscanf(line.c_str(), "%s:", p);
		sscanf(line.c_str(), "%[^: ]", p);
		param = p;
		
		if (param == "FPS"){
			sscanf(line.c_str(), "%*s %d", &params.FPS); 
			printf("The %s is %i\n", p, params.FPS);
		}
		else if (param == "FileName") { 
			sscanf(line.c_str(), "%*s \"%[^\" ]\"", v);
			params.TileSheet = v;
			printf("The %s is %s\n", p, params.TileSheet.c_str());
		}
		else if (param == "height") {
			sscanf(line.c_str(), "%*s %d", &params.height); 
			printf("The %s is %i\n", p, params.height);
		}
		else if (param == "width") {
			sscanf(line.c_str(), "%*s %d", &params.width); 
			printf("The %s is %i\n", p, params.width);
		}
		else if (param == "count") {
			sscanf(line.c_str(), "%*s %d", &params.count); 
			printf("The %s is %i\n", p, params.count);
		}
		else if (param == "method") {
			sscanf(line.c_str(), "%*s (%[^( ,],%d", v, &params.method_attr);
			params.method = v;
			printf("The %s is %s\n", p, v);
			printf("With %i\n", params.method_attr);
		}
		line = "";
	}
	Animation newAnim = RollingTileSheet(params.width, params.height, params.method_attr, params.count);
	newAnim.SetTexture(GameRegistry::GetTexture("../"+params.TileSheet));
	newAnim.SetBaseFrameTime(1.0/params.FPS);	
	_contents[name] = newAnim;

} //animation script parser, adds an animation object











