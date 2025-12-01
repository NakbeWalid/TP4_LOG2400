#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "IElement.h"
#include "surface_strategy.h"
#include "affichage.h"

class PointMD;


class AffichageTemplate
{
protected:
    const std::vector<IElement*>* elements_;
    const std::vector<Ligne>* lignesC1_;
    const std::vector<Ligne>* lignesC2_;

public:
    AffichageTemplate() : elements_(nullptr), lignesC1_(nullptr), lignesC2_(nullptr) {}
    virtual ~AffichageTemplate() = default;

    void afficher(const std::vector<IElement*>& elements,
                  const std::vector<Ligne>* lignesC1 = nullptr,
                  const std::vector<Ligne>* lignesC2 = nullptr)
    {
        elements_ = &elements;
        lignesC1_ = lignesC1;
        lignesC2_ = lignesC2;
        
        initialiserGrille();     
        dessinerElements();        
        tracerLignes();           
        postTraitement();          
        reDessinerElements();      
        imprimer();                
    }

protected:
    virtual void initialiserGrille() = 0;
    virtual void dessinerElements() = 0;
    virtual void tracerLignes() = 0;
    virtual void reDessinerElements() = 0;
    virtual void imprimer() = 0;

    virtual void postTraitement() = 0;
};
