#include "point.h"
#include <iostream>

PointMD::PointMD(int id, int x, int y, char texture)
    : id_(id), x_(x), y_(y), texture_(texture) {}

int PointMD::getId() const { return id_; }
int PointMD::getX() const { return x_; }
int PointMD::getY() const { return y_; }
char PointMD::getTexture() const { return texture_; }

void PointMD::addTexture(char t) {
    textures_.push_back(t);
}

const std::vector<char>& PointMD::getTextures() const {
    return textures_;
}

void PointMD::setPosition(int newX, int newY) {
    x_ = newX;
    y_ = newY;
}

void PointMD::afficher() const {
    std::cout << id_
              << ": (" << x_ << "," << y_ << ")  textures: '";

    if (textures_.empty())
        std::cout << " '";
    else
        for (char t : textures_) std::cout << t;

    std::cout << "'" << std::endl;
}
