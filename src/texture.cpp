#include "texture.h"
#include <stdio.h>
#include <string.h>

void initialiser_texture(Texture* t, int id, char symbol) {
    t->id = id;
    t->name[0] = symbol;
    t->name[1] = '\0'; // Nom limité au symbole pour l’instant
}

void afficher_texture(const Texture* t) {
    printf("Texture: ID=%d, Symbol=%s\n", t->id, t->name);
}
