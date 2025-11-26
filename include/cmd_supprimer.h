#pragma once
#include "commande.h"
#include "IElement.h"
#include <vector>

class CmdSupprimer : public Commande
{
private:
    std::vector<IElement *> &elements;
    IElement *cible;
    int indexRemoved; // position where the element was removed

public:
    CmdSupprimer(std::vector<IElement *> &elems, IElement *cible);

    void executer() override;
    void annuler() override;
};