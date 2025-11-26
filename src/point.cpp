#include "point.h"
#include <algorithm>

PointMD::PointMD(int id, int x, int y, char texture)
    : id_(id), x_(x), y_(y), texture_(texture)
{
}

int PointMD::getId() const { return id_; }
int PointMD::getX() const { return x_; }
int PointMD::getY() const { return y_; }
char PointMD::getTexture() const { return texture_; }

void PointMD::setPosition(int newX, int newY)
{
    x_ = newX;
    y_ = newY;
}

void PointMD::setTexture(char t)
{
    texture_ = t;
}

void PointMD::addTexture(char t)
{
    // éviter les doublons
    if (std::find(textures_.begin(), textures_.end(), t) == textures_.end())
        textures_.push_back(t);
    texture_ = t; // on garde la dernière comme "principale"
}

const std::vector<char>& PointMD::getTextures() const
{
    return textures_;
}

void PointMD::afficher() const
{
    std::cout << id_
              << ": (" << x_ << "," << y_ << ")  texture='";

    if (texture_ == ' ')
        std::cout << " ";
    else
        std::cout << texture_ << "'";

    std::cout << std::endl;
}

void PointMD::afficherDansGrille(std::vector<std::vector<char>>& grille,
                                 bool afficherID) const
{
    if (y_ < 0 || y_ >= (int)grille.size())
        return;
    if (x_ < 0 || x_ >= (int)grille[0].size())
        return;

    if (afficherID)
    {
        grille[y_][x_] = (id_ < 10 ? char('0' + id_) : '*');
    }
    else
    {
        grille[y_][x_] = (texture_ == ' ' ? '.' : texture_);
    }
}

std::vector<PointMD*> PointMD::getPoints() const
{
    return { const_cast<PointMD*>(this) };
}
