
#include "Accounting/Registries.h"

//TextureRegistry::TextureRegistry(void) {}

//TextureRegistry::~TextureRegistry(void) {}

sf::Texture& TextureRegistry::operator[](std::string name) { return TextureRegistry::_textures[name]; }

bool TextureRegistry::Contains(std::string name) {

	std::map<std::string, sf::Texture>::const_iterator item = TextureRegistry::_textures.find(name);
	if (item == TextureRegistry::_textures.end() )
		return false;
	return true;
}

sf::Texture& TextureRegistry::Get(std::string name) { //could also make this a bool and take a texture reference to change

	if (TextureRegistry::Contains(name)) {
		printf("Found the Texture: %s\n",name.c_str());
	}
	else{
		 TextureRegistry::Load(name);
		printf("New Texture: %s\n", name.c_str());
	}
	return TextureRegistry::_textures[name];
}

void TextureRegistry::Load(std::string name) {

		sf::Texture t;
		if (t.loadFromFile(name) )
			TextureRegistry::_textures[name] = t;
		else {
			printf("ERROR: Texture Not Found!\n");
			printf("       Could Not Find \"%s\"\n", name.c_str());
			exit(1);
		}
}

std::map<std::string, sf::Texture> TextureRegistry::_textures;

