#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H


typedef struct {
    int id;
    char name[50];
    // Ajoute d'autres champs nécessaires à la texture
} Texture;

// Prototypes pour la gestion des textures
void afficher_texture(const Texture* t);
void initialiser_texture(Texture* t, int id, char symbol);
#endif // TEXTURE_H

