#include "affichage.h"
#include "point.h"
#include "nuage.h"
#include "surface.h"
#include "texture.h"
#include "manager.h"
#include "cmd_deplacer.h"
#include "cmd_supprimer.h"
#include "invoker.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    string args;

    // Lecture des points
    if (argc > 1)
    {
        ostringstream oss;
        for (int i = 1; i < argc; ++i)
            oss << argv[i] << " ";
        args = oss.str();
    }
    else
    {
        cout << "Entrez les points au format (x,y) :\n> ";
        getline(cin, args);
    }

    vector<Point> pointsAff = creerPoints(args);
    imprimerGrille(pointsAff);

    // POINTS DU MODELE (PointMD) stockés comme IElement*
    vector<IElement *> elements; // uniquement les points au début
    int idCounter = 0;
    for (auto &p : pointsAff)
        elements.push_back(new PointMD(idCounter++, p.x, p.y, ' '));

    // LISTE DES NUAGE (IElement*)
    vector<IElement *> nuages;

    // Lignes générées par c1 et c2 (pour o1 / o2)
    vector<Ligne> lignesC1;
    vector<Ligne> lignesC2;

    vector<char> texturesNuages = {'o', '#'};

    Invoker invoker;
    Manager manager(elements);

    string cmd;

    while (true)
    {
        cout << "\nCommandes:\n"
             << "a  - Afficher les points et les nuages\n"
             << "o1 - Afficher l'orthèse avec les textures des points\n"
             << "o2 - Afficher l'orthèse avec les IDs des points\n"
             << "f  - Fusionner des points dans un nuage (et appliquer texture)\n"
             << "d  - Deplacer un point (ID)\n"
             << "s  - Supprimer un point (ID)\n"
             << "u - Annuler la dernière commande (undo)"
             << "r- Réappliquer la derniêre commande annulée (redo)"
             << "c1 - Créer les surfaces selon l'ordre des IDs\n"
             << "c2 - Créer les surfaces selon la distance minimale\n"
             << "q  - Quitter\n> ";
        getline(cin, cmd);

        if (cmd == "q")
            break;

        // UNDO
        else if (cmd == "u")
        {
            invoker.undo();
            continue;
        }
        // REDO
        else if (cmd == "r")
        {
            invoker.redo();
            continue;
        }
        // AFFICHER POINTS + NUAGES
        else if (cmd == "a")
        {
            cout << "\nListe:\n";

            // 1) Afficher les pointsg
            for (auto e : manager.getElements())
            {
                PointMD *p = dynamic_cast<PointMD *>(e);
                if (p)
                {
                    // afficher les textures du point
                    cout << p->getId() << ": ("
                         << p->getX() << "," << p->getY() << ")  textures: '";

                    const auto &texs = p->getTextures();
                    if (texs.empty())
                        cout << " ";
                    else
                        for (char t : texs)
                            cout << t;

                    cout << "'\n";
                }
            }

            // 2) Afficher les nuages
            for (auto elem : nuages)
            {
                Nuage *n = dynamic_cast<Nuage *>(elem);
                if (!n)
                    continue;

                cout << n->getId() << ": Nuage '" << n->getTexture()
                     << "' contient les éléments: ";

                for (auto e : n->getEnfants())
                {
                    PointMD *p = dynamic_cast<PointMD *>(e);
                    if (p)
                        cout << p->getId() << " ";
                    else
                    {
                        Nuage *sub = dynamic_cast<Nuage *>(e);
                        if (sub)
                            cout << sub->getId() << " ";
                    }
                }
                cout << "\n";
            }

            continue;
        }

        // DEPLACER (commande avec undo/redo)
        else if (cmd == "d")
        {
            cout << "ID du point a deplacer : ";
            string idStr;
            getline(cin, idStr);
            int id = stoi(idStr);

            PointMD *p = manager.getPoint(id);
            if (!p)
            {
                cout << "Erreur : point inexistant.\n";
                continue;
            }

            cout << "Nouvelle position (x y) : ";
            string xy;
            getline(cin, xy);
            stringstream ss(xy);
            int nx, ny;
            ss >> nx >> ny;

            Commande *c = new CmdDeplacer(p, nx, ny);
            invoker.executer(c);

            cout << "Point " << id << " deplace.\n";
            continue;
        }
        // SUPPRIMER (commande avec undo/redo)
        else if (cmd == "s")
        {
            cout << "ID du point a supprimer : ";
            string idStr;
            getline(cin, idStr);
            int id = stoi(idStr);

            // On cherche un element (point ou nuage) contenant ce point ID
            IElement *element = manager.getElement(id);

            if (!element)
            {
                cout << "Erreur : aucun element contenant le point " << id << ".\n";
                continue;
            }

            // Container primaire : les éléments gérés par le manager
            std::vector<IElement *> &mgrElems = manager.getElements();
            std::vector<IElement *> *container = nullptr;

            if (std::find(mgrElems.begin(), mgrElems.end(), element) != mgrElems.end())
                container = &mgrElems;
            else if (std::find(nuages.begin(), nuages.end(), element) != nuages.end())
                container = &nuages;

            if (!container)
            {
                cout << "Erreur interne : container de l'element introuvable.\n";
                continue;
            }

            Commande *c = new CmdSupprimer(*container, element);
            invoker.executer(c);

            cout << "Element contenant le point " << id << " supprime.\n";
            continue;
        }
        // FUSIONNER DES POINTS DANS UN NOUVEAU NUAGE
        else if (cmd == "f")
        {
            cout << "IDs de points/nuages à fusionner (ex: 0 2 5): ";
            string ligne;
            getline(cin, ligne);

            stringstream ss(ligne);
            vector<int> ids;
            int tmp;

            while (ss >> tmp)
                ids.push_back(tmp);

            if (ids.empty())
            {
                cout << "Aucun ID valide.\n";
                continue;
            }

            // Nouvelle texture automatique
            char tex = texturesNuages[nuages.size() % texturesNuages.size()];

            // Créer le nouveau nuage
            Nuage *nouveau = new Nuage((int)(elements.size()), tex);

            // Pour chaque ID donné
            for (int pid : ids)
            {
                IElement *elem = manager.getElement(pid);

                if (!elem)
                {
                    cout << "ID " << pid << " invalide !" << endl;
                    continue;
                }

                Nuage *subNuage = dynamic_cast<Nuage *>(elem);
                PointMD *pmd = dynamic_cast<PointMD *>(elem);

                if (pmd)
                {
                    // cas point simple
                    nouveau->ajouterElement(pmd);
                    pmd->addTexture(tex);
                }
                else if (subNuage)
                {
                    // cas NUAGE → on ajoute le NUAGE LUI-MÊME
                    nouveau->ajouterElement(subNuage);
                    subNuage->appliquerTexture(tex);
                }
            }

            // Appliquer texture au nuage (affichage)
            nouveau->appliquerTexture(tex);

            // L’ajouter dans la liste
            nuages.push_back(nouveau);
            elements.push_back(nouveau); // IMPORTANT : devient un IElement*

            continue;
        }

        // CREER LES SURFACES C1 (ordre des IDs)
        else if (cmd == "c1")
        {
            lignesC1.clear();
            SurfaceC1 strat;

            // IMPORTANT : s'assurer que les nuages sont dans l'ordre croissant de leur ID
            sort(nuages.begin(), nuages.end(),
                 [](IElement *a, IElement *b)
                 {
                     return dynamic_cast<Nuage *>(a)->getId() <
                            dynamic_cast<Nuage *>(b)->getId();
                 });

            for (auto elem : nuages)
            {
                Nuage *n = dynamic_cast<Nuage *>(elem);
                if (!n)
                    continue;

                // ⚠ NE PAS CONSTRUIRE UNE SURFACE POUR < 2 POINTS
                if (n->getPoints().size() < 2)
                    continue;

                auto Ls = strat.construire(*n);
                lignesC1.insert(lignesC1.end(), Ls.begin(), Ls.end());
            }

            cout << "Surfaces C1 mises à jour.\n";
            continue;
        }

        // CREER LES SURFACES C2 (distance minimale)
        else if (cmd == "c2")
        {
            lignesC2.clear();
            SurfaceC2 strat;

            sort(nuages.begin(), nuages.end(),
                 [](IElement *a, IElement *b)
                 {
                     return dynamic_cast<Nuage *>(a)->getId() <
                            dynamic_cast<Nuage *>(b)->getId();
                 });

            for (auto elem : nuages)
            {
                Nuage *n = dynamic_cast<Nuage *>(elem);
                if (!n)
                    continue;

                if (n->getPoints().size() < 2)
                    continue;

                auto Ls = strat.construire(*n);
                lignesC2.insert(lignesC2.end(), Ls.begin(), Ls.end());
            }

            cout << "Surfaces C2 mises à jour.\n";
            continue;
        }

        // ORTHESE TEXTURES
        else if (cmd == "o1")
        {
            // grille de string pour pouvoir afficher "o#", "o##", etc.
            vector<vector<string>> grille(HAUTEUR, vector<string>(LARGEUR, " "));

            // 1) Placer les textures des points
            for (auto e : manager.getElements())
            {
                PointMD *p = dynamic_cast<PointMD *>(e);
                if (!p)
                    continue;

                int x = p->getX();
                int y = p->getY();
                if (x < 0 || x >= LARGEUR || y < 0 || y >= HAUTEUR)
                    continue;

                const auto &texs = p->getTextures();
                if (texs.empty())
                {
                    grille[y][x] = ".";
                }
                else
                {
                    string s;
                    for (char t : texs)
                        s.push_back(t); // ex: "o", "#", "o#"
                    grille[y][x] = s;
                }
            }

            // 2) Tracer les lignes C1
            for (auto &L : lignesC1)
                if (L.a && L.b)
                    tracerLigne(grille,
                                L.a->getX(), L.a->getY(),
                                L.b->getX(), L.b->getY());

            // 3) Tracer les lignes C2
            for (auto &L : lignesC2)
                if (L.a && L.b)
                    tracerLigne(grille,
                                L.a->getX(), L.a->getY(),
                                L.b->getX(), L.b->getY());

            // 4) Ré-écrire les textures par-dessus les traits
            for (auto e : manager.getElements())
            {
                PointMD *p = dynamic_cast<PointMD *>(e);
                if (!p)
                    continue;

                int x = p->getX();
                int y = p->getY();
                if (x < 0 || x >= LARGEUR || y < 0 || y >= HAUTEUR)
                    continue;

                const auto &texs = p->getTextures();
                if (texs.empty())
                    grille[y][x] = ".";
                else
                {
                    string s;
                    for (char t : texs)
                        s.push_back(t);
                    grille[y][x] = s;
                }
            }

            // 5) Affichage
            for (int y = HAUTEUR - 1; y >= 0; --y)
            {
                for (int x = 0; x < LARGEUR; ++x)
                    cout << grille[y][x];
                cout << "\n";
            }

            continue;
        }
        // ORTHESE IDs
        else if (cmd == "o2")
        {
            vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));

            // 1) Placer les IDs
            for (auto e : manager.getElements())
            {
                PointMD *p = dynamic_cast<PointMD *>(e);
                if (!p)
                    continue;

                int x = p->getX();
                int y = p->getY();
                int id = p->getId();
                if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                    grille[y][x] = (id < 10 ? '0' + id : '*');
            }

            // 2) Tracer les lignes C1
            for (auto &L : lignesC1)
                if (L.a && L.b)
                    tracerLigne(grille,
                                L.a->getX(), L.a->getY(),
                                L.b->getX(), L.b->getY());

            // 3) Tracer les lignes C2
            for (auto &L : lignesC2)
                if (L.a && L.b)
                    tracerLigne(grille,
                                L.a->getX(), L.a->getY(),
                                L.b->getX(), L.b->getY());

            // 4) Ré-afficher les IDs par-dessus les traits
            for (auto e : manager.getElements())
            {
                PointMD *p = dynamic_cast<PointMD *>(e);
                if (!p)
                    continue;

                int x = p->getX();
                int y = p->getY();
                int id = p->getId();
                if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                    grille[y][x] = (id < 10 ? '0' + id : '*');
            }

            // 5) Affichage
            for (int y = HAUTEUR - 1; y >= 0; --y)
            {
                for (int x = 0; x < LARGEUR; ++x)
                    cout << grille[y][x];
                cout << "\n";
            }

            continue;
        }
        else
        {
            cout << "Commande inconnue.\n";
            continue;
        }
    }

    return 0;
}