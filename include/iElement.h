#pragma once
#include <vector>

class PointMD;

class IElement
{
public:
    virtual ~IElement() = default;

    virtual void afficher() const = 0;
    virtual void afficherDansGrille(std::vector<std::vector<char>> &grid, bool afficherID) const = 0;

    virtual std::vector<PointMD *> getPoints() const = 0;
};