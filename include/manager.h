#pragma once
#include <vector>
#include "IElement.h"
#include "point.h"

// Le Manager gère les éléments (Points + Nuages) de manière centralisée.
class Manager
{
private:
    std::vector<IElement *> &elements; // référence vers la liste globale

public:
    Manager(std::vector<IElement *> &elems);

    // Récupère un élément (Point ou Nuage) contenant ce point ID
    IElement *getElement(int id);

    // Récupère UNIQUEMENT un Point par ID
    PointMD *getPoint(int id);

    // Accès direct aux éléments (utile pour CmdSupprimer / CmdFusionner)
    std::vector<IElement *> &getElements();
};