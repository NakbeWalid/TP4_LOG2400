#include "cmd_fusionner.h"
#include "point.h"
#include "texture_decorator_concret.h"
#include <iostream>
#include <vector>

CmdFusionner::CmdFusionner(std::vector<IElement*>& elements,
                           std::vector<IElement*>& nuages,
                           Manager& manager,
                           std::vector<char>& texturesNuages,
                           const std::vector<int>& ids)
    : elements_(elements),
      nuages_(nuages),
      manager_(manager),
      texturesNuages_(texturesNuages),
      ids_(ids),
      nouveauNuage_(nullptr),
      texture_(' '),
      indexDansElements_(-1),
      indexDansNuages_(-1)
{
}

void CmdFusionner::executer()
{
    if (ids_.empty())
        return;

    texture_ = texturesNuages_[nuages_.size() % texturesNuages_.size()];
    nouveauNuage_ = new Nuage((int)elements_.size(), texture_);

    for (int pid : ids_)
    {
        IElement* elem = manager_.getElement(pid);

        if (!elem)
        {
            std::cout << "ID " << pid << " invalide !" << std::endl;
            continue;
        }

        if (auto pmd = dynamic_cast<PointMD*>(elem))
        {
            nouveauNuage_->ajouterElement(pmd);
            // Utiliser le Decorator pour appliquer la texture (patron Decorator)
            TextureDecoratorConcret* decorator = new TextureDecoratorConcret(pmd, texture_);
            decorators_.push_back(decorator);
        }
        else if (auto subNuage = dynamic_cast<Nuage*>(elem))
        {
            nouveauNuage_->ajouterElement(subNuage);
            // Utiliser le Decorator pour appliquer la texture aux points du sous-nuage (patron Decorator)
            auto pts = subNuage->getPoints();
            for (auto p : pts)
            {
                if (p)
                {
                    TextureDecoratorConcret* decorator = new TextureDecoratorConcret(p, texture_);
                    decorators_.push_back(decorator);
                }
            }
        }
    }

    // Les textures sont deja appliquees par les decorators
    // nouveauNuage_->appliquerTexture(texture_); // Plus necessaire avec le Decorator
    
    indexDansNuages_ = (int)nuages_.size();
    nuages_.push_back(nouveauNuage_);
    
    indexDansElements_ = (int)elements_.size();
    elements_.push_back(nouveauNuage_);

    std::cout << "Nuage " << nouveauNuage_->getId() << " cree avec texture '" << texture_ << "'.\n";
}

void CmdFusionner::annuler()
{
    if (!nouveauNuage_)
        return;

    // Retirer les textures avec les decorators
    for (auto decorator : decorators_)
    {
        if (decorator)
        {
            decorator->retirerTexture(texture_);
            delete decorator;
        }
    }
    decorators_.clear();

    // Retirer le nuage des vecteurs
    if (indexDansElements_ >= 0 && indexDansElements_ < (int)elements_.size())
    {
        elements_.erase(elements_.begin() + indexDansElements_);
    }

    if (indexDansNuages_ >= 0 && indexDansNuages_ < (int)nuages_.size())
    {
        nuages_.erase(nuages_.begin() + indexDansNuages_);
    }

    // Supprimer le nuage
    delete nouveauNuage_;
    nouveauNuage_ = nullptr;
}

