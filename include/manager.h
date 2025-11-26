#pragma once
#include "nuage.h"
#include "texture.h"

#ifndef MANAGER_H
#define MANAGER_H

// Gestion centralisée de tous les nuages, textures…
typedef struct {
    Nuage* nuages;
    int nb_nuages;
    Texture* textures;
    int nb_textures;
} Manager;

// Prototypes pour ajouter, supprimer, etc.

#endif // MANAGER_H

