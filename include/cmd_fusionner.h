#pragma once
#include "commande.h"
#include "IElement.h"
#include "nuage.h"
#include "manager.h"
#include "texture_decorator_concret.h"
#include <vector>

class CmdFusionner : public Commande
{
private:
    std::vector<IElement*>& elements_;
    std::vector<IElement*>& nuages_;
    Manager& manager_;
    std::vector<char>& texturesNuages_;
    
    std::vector<int> ids_;
    Nuage* nouveauNuage_;
    char texture_;
    int indexDansElements_;
    int indexDansNuages_;
    std::vector<TextureDecoratorConcret*> decorators_; 

public:
    CmdFusionner(std::vector<IElement*>& elements,
                 std::vector<IElement*>& nuages,
                 Manager& manager,
                 std::vector<char>& texturesNuages,
                 const std::vector<int>& ids);

    void executer() override;
    void annuler() override;
};

