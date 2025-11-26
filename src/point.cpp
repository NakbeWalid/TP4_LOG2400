#include "point.h"
#include <iostream>

PointMD::PointMD(int id, int x, int y, char texture)
    : id_(id), x_(x), y_(y), texture_(texture) {}

int PointMD::getId() const { return id_; }
int PointMD::getX() const { return x_; }
int PointMD::getY() const { return y_; }
char PointMD::getTexture() const { return texture_; }

void PointMD::setPosition(int newX, int newY) {
    x_ = newX;
    y_ = newY;
}

void PointMD::setTexture(char t) {
    texture_ = t;
}

void PointMD::afficher() const {
    std::cout << "PointMD #" << id_
              << " (" << x_ << "," << y_
              << ") texture=" << texture_ << std::endl;
}
