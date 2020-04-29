#include "Engine/AssetManager.h"
#include <iostream>

typedef std::map<std::string, sf::Font*> FontMap;
typedef std::map<std::string, sf::Texture*> TextureMap;

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
    this->ClearFonts();
    this->ClearTextures();
}

sf::Font& AssetManager::getFont(std::string FilePath)
{
    FontMap::iterator FindIterator = fonts.find(FilePath);
    if(FindIterator == fonts.end()) {
        sf::Font* font = new sf::Font();
        if(font->loadFromFile(FilePath)) {
            fonts.insert(std::pair<std::string, sf::Font*>(FilePath, font));
        }
        else {
            delete font;
            std::cout << "ERROR::ASSETMANAGER::CAN'T LOAD FONT FROM " << FilePath << std::endl;
        }
        return *font;
    }
    else
        return *FindIterator->second;
}

sf::Texture& AssetManager::getTexture(std::string FilePath)
{
    TextureMap::iterator FindIterator = textures.find(FilePath);
    if(FindIterator == textures.end()) {
        sf::Texture* texture = new sf::Texture();
        if(texture->loadFromFile(FilePath)) {
            textures.insert(std::pair<std::string, sf::Texture*>(FilePath, texture));
        }
        else {
            delete texture;
            std::cout << "ERROR::ASSETMANAGER::CAN'T LOAD TEXTURE FROM " << FilePath << std::endl;
        }
        return *texture;
    }
    else
        return *FindIterator->second;
}

void AssetManager::ClearFonts()
{
    for(FontMap::iterator it = fonts.begin(); it != fonts.end(); it++)
        delete it->second;
    fonts.clear();
}


void AssetManager::ClearTextures()
{
    for(TextureMap::iterator it = textures.begin(); it != textures.end(); it++)
        delete it->second;
    textures.clear();
}
