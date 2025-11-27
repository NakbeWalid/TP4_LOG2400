#pragma once
#include <vector>
#include "IElement.h"
#include "point.h"
#include "nuage.h"

// Le Manager gère les éléments (Points + Nuages) de manière centralisée.
class Manager
{
private:
    std::vector<IElement *> &elements_; // référence vers la liste globale

public:
    Manager(std::vector<IElement *> &elems);

    // Récupère un élément (Point ou Nuage) contenant ce point ID
    IElement *getElement(int id) const;

    // Récupère UNIQUEMENT un Point par ID
    PointMD *getPoint(int id) const;

    Nuage* getNuage(int id) const;

    // Accès direct aux éléments (utile pour CmdSupprimer / CmdFusionner)
    std::vector<IElement *> &getElements();
};