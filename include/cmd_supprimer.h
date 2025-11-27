#pragma once
#include "commande.h"
#include <vector>
#include <cstddef> 
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
    size_t oldIndex_;   // <-- IMPORTANT pour undo
};
