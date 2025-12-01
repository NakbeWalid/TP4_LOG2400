#pragma once
#include "commande.h"
#include <vector>
#include "IElement.h"

class CmdSupprimer : public Commande
{
public:
    CmdSupprimer(std::vector<IElement*>& container, IElement* elem);

    void executer() override;
    void annuler() override;

private:
    std::vector<IElement*>& container_;
    IElement* element_;
    int oldIndex_;
};
