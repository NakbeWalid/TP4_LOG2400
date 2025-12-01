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


    void addTexture(char t);
    const std::vector<char>& getTextures() const;

    void afficher() const override;
    void afficherDansGrille(std::vector<std::vector<char>>& grille,
                            bool afficherID) const override;
    std::vector<PointMD*> getPoints() const override;

private:
    int id_;
    int x_;
    int y_;
    char texture_;
    std::vector<char> textures_;
};
