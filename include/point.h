#pragma once
#include <iostream>

class PointMD {
public:
    PointMD(int id, int x, int y, char texture = 'o');

    int getId() const;
    int getX() const;
    int getY() const;
    char getTexture() const;

    void setPosition(int newX, int newY);
    void setTexture(char t);

    void afficher() const;

private:
    int id_;
    int x_;
    int y_;
    char texture_;
};
