#pragma once
#include <vector>

class PointMD; // forward declaration

class IElement
{
public:
    virtual ~IElement() = default;

    // Pour Personne A (affichage / structure)
    virtual void afficher() const = 0;
    virtual void afficherDansGrille(std::vector<std::vector<char>> &grid, bool afficherID) const = 0;

    // Pour Personne B (fusion, stratégies)
    virtual std::vector<PointMD *> getPoints() const = 0;
};