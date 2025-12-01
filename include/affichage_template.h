#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "IElement.h"
#include "surface_strategy.h"
#include "affichage.h"

// Forward declaration
class PointMD;

// Classe de base pour le patron Template Method
// Definit le squelette de l'algorithme d'affichage
class AffichageTemplate
{
protected:
    const std::vector<IElement*>* elements_;
    const std::vector<Ligne>* lignesC1_;
    const std::vector<Ligne>* lignesC2_;

public:
    AffichageTemplate() : elements_(nullptr), lignesC1_(nullptr), lignesC2_(nullptr) {}
    virtual ~AffichageTemplate() = default;

    // ----------- TEMPLATE METHOD ------------
    // Methode template qui definit le squelette de l'algorithme
    void afficher(const std::vector<IElement*>& elements,
                  const std::vector<Ligne>* lignesC1 = nullptr,
                  const std::vector<Ligne>* lignesC2 = nullptr)
    {
        elements_ = &elements;
        lignesC1_ = lignesC1;
        lignesC2_ = lignesC2;
        
        initialiserGrille();      // Etape 1: Initialiser
        dessinerElements();        // Etape 2: Dessiner les elements
        tracerLignes();            // Etape 3: Tracer les lignes
        postTraitement();          // Etape 4: Post-traitement (variable)
        reDessinerElements();      // Etape 5: Re-dessiner par-dessus les lignes
        imprimer();                // Etape 6: Afficher
    }

protected:
    // Etapes FIXES du Template Method (methodes concretes)
    virtual void initialiserGrille() = 0;
    virtual void dessinerElements() = 0;
    virtual void tracerLignes() = 0;
    virtual void reDessinerElements() = 0;
    virtual void imprimer() = 0;

    // Etapes VARIABLES du Template Method (methodes virtuelles)
    virtual void postTraitement() = 0;
};

