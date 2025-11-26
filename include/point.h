#pragma once
#include <vector>

class PointMD {
public:
    PointMD(int id, int x, int y, char texture = ' ');

    int getId() const;
    int getX() const;
    int getY() const;

    // Dernière texture (option legacy)
    char getTexture() const;

    // Textures cumulées pour multi-nuages
    void addTexture(char t);
    const std::vector<char>& getTextures() const;

    void setPosition(int newX, int newY);

    void afficher() const;

private:
    int id_;
    int x_;
    int y_;
    char texture_;                // ancienne texture unique
    std::vector<char> textures_;   // textures multiples
};
