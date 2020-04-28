#pragma once
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "SFML/Graphics.hpp"

class AssetManager
{
    public:
        AssetManager();
        virtual ~AssetManager();

        sf::Font& getFont(std::string FilePath);

        sf::Texture& getTexture(std::string FilePath);

        void Clear();

    private:
        std::map<std::string, sf::Font*> fonts;

        std::map<std::string, sf::Texture*> textures;

        void ClearFonts();

        void ClearTextures();
};

#endif // ASSETMANAGER_H
