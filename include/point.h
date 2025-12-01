#pragma once
#include <iostream>
#include <vector>
#include "IElement.h"

class PointMD : public IElement
{
public:
    PointMD(int id, int x, int y, char texture = ' ');

    int getId() const;
    int getX() const;
    int getY() const;
    char getTexture() const;

    void setPosition(int newX, int newY);
    void setTexture(char t);

    void setId(int newId);


    // Pour gérer plusieurs textures (si le point est dans plusieurs nuages)
    void addTexture(char t);
    const std::vector<char>& getTextures() const;

    // IElement
    void afficher() const override;
    void afficherDansGrille(std::vector<std::vector<char>>& grille,
                            bool afficherID) const override;
    std::vector<PointMD*> getPoints() const override;

private:
    int id_;
    int x_;
    int y_;
    char texture_;                  // texture principale (dernière appliquée)
    std::vector<char> textures_;    // toutes les textures des nuages contenant ce point
};
