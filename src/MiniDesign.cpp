#include "affichage.h"
#include "point.h"
#include "nuage.h"
#include "surface.h"
#include "texture.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

    // POINTS ASCII pour affichage
    vector<Point> pointsAff = creerPoints(args);
    imprimerGrille(pointsAff);

    // POINTS DU MODELE (PointMD)
    vector<PointMD *> pointsMD;
    int idCounter = 0;
    for (auto &p : pointsAff)
        pointsMD.push_back(new PointMD(idCounter++, p.x, p.y));

    // LISTE DES NUAGE (vide au début)
    vector<Nuage *> nuages;
    std::vector<Ligne> lignesC1;
    std::vector<Ligne> lignesC2;

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
             << "c1 - Créer les surfaces selon l'ordre des IDs\n"
             << "c2 - Créer les surfaces selon la distance minimale\n"
             << "q  - Quitter\n> ";

        getline(cin, cmd);

        if (cmd == "q")
            break;

        if (cmd == "a")
        {
            cout << "\nListe des Points:\n";
            for (auto p : pointsMD)
            {
                if (p)
                    p->afficher();
            }

            for (auto n : nuages)
                n->afficher();

            continue;
        }

        else if (cmd == "f")
        {
            cout << "Entrez les IDs des points à fusionner (ex: 0 2 5) : ";
            string ligne;
            getline(cin, ligne);

            stringstream ss(ligne);
            vector<int> ids;
            int id;

            while (ss >> id)
                ids.push_back(id);

            if (ids.empty())
            {
                cout << "Aucun ID valide." << endl;
                continue;
            }

            // texture automatique
            char tex = (nuages.size() % 2 == 0 ? 'o' : '#');

            // création du nuage
            Nuage *n = new Nuage(nuages.size(), tex);

            for (int i : ids)
            {
                if (i >= 0 && i < pointsMD.size() && pointsMD[i])
                {
                    n->ajouterPoint(pointsMD[i]);
                    pointsMD[i]->addTexture(tex);
                }
            }

            nuages.push_back(n);

            continue;
        }

        else if (cmd == "c1")
        {
            lignesC1.clear();

            SurfaceC1 strat;

            for (auto n : nuages)
            {
                auto Ls = strat.construire(*n);
                lignesC1.insert(lignesC1.end(), Ls.begin(), Ls.end());
            }

            continue;
        }

        else if (cmd == "c2")
        {
            lignesC2.clear();

            SurfaceC2 strat;

            for (auto n : nuages)
            {
                auto Ls = strat.construire(*n);
                lignesC2.insert(lignesC2.end(), Ls.begin(), Ls.end());
            }

            continue;
        }

        else if (cmd == "o1")
        {
            vector<vector<string>> grille(HAUTEUR, vector<string>(LARGEUR, " "));

            // 1) Placer les textures DES POINTS
            for (auto p : pointsMD)
            {
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
                    string s = "";
                    for (char t : texs)
                        s.push_back(t); // ex "o", "#", "o#"
                    grille[y][x] = s;
                }
            }

            // 2) Tracer C1 et C2 → les traits "/"
            for (auto &L : lignesC1)
                tracerLigne(grille, L.a->getX(), L.a->getY(),
                            L.b->getX(), L.b->getY());

            for (auto &L : lignesC2)
                tracerLigne(grille, L.a->getX(), L.a->getY(),
                            L.b->getX(), L.b->getY());

            // 3) *** RÉAFFICHER LES TEXTURES PAR-DESSUS ***
            for (auto p : pointsMD)
            {
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
                    string s = "";
                    for (char t : texs)
                        s.push_back(t);
                    grille[y][x] = s;
                }
            }

            // 4) AFFICHAGE FINAL
            for (int y = HAUTEUR - 1; y >= 0; --y)
            {
                for (int x = 0; x < LARGEUR; ++x)
                    cout << grille[y][x];
                cout << "\n";
            }

            continue;
        }

        else if (cmd == "o2")
        {
            vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));

            // 1) Placer les IDs
            for (auto p : pointsMD)
            {
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
                tracerLigne(grille,
                            L.a->getX(), L.a->getY(),
                            L.b->getX(), L.b->getY());

            // 3) Tracer les lignes C2
            for (auto &L : lignesC2)
                tracerLigne(grille,
                            L.a->getX(), L.a->getY(),
                            L.b->getX(), L.b->getY());

            // 4) Réafficher les IDs par-dessus
            for (auto p : pointsMD)
            {
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

        else if (cmd == "d")
        {
            cout << "ID du point a deplacer : ";
            int id;
            cin >> id;
            cin.ignore();

            if (id < 0 || id >= pointsMD.size() || !pointsMD[id])
            {
                cout << "Point invalide." << endl;
                continue;
            }

            cout << "Nouvelle position X Y : ";
            int nx, ny;
            cin >> nx >> ny;
            cin.ignore();

            pointsMD[id]->setPosition(nx, ny);

            continue;
        }

        else if (cmd == "s")
        {
            cout << "ID du point a supprimer : ";
            int id;
            cin >> id;
            cin.ignore();

            if (id < 0 || id >= pointsMD.size() || !pointsMD[id])
            {
                cout << "Point invalide." << endl;
                continue;
            }

            // Retirer du MD
            PointMD *cible = pointsMD[id];

            // Retirer des nuages
            for (auto n : nuages)
                n->retirerPoint(id);

            pointsMD[id] = nullptr;

            continue;
        }
    }

    return 0;
}
