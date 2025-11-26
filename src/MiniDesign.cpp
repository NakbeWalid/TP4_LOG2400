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
        pointsMD.push_back(new PointMD(idCounter++, p.x, p.y, ' ')); // texture vide

    // LISTE DES NUAGE (vide au début)
    vector<Nuage *> nuages;

    string cmd;

    while (true)
    {
        cout << "\nCommandes:\n"
             << "a  - Afficher les points et les nuages\n"
             << "o1 - Afficher l'orthèse (textures)\n"
             << "o2 - Afficher l'orthèse (IDs)\n"
             << "f  - Fusionner des points dans un nuage\n"
             << "d  - Deplacer un point\n"
             << "s  - Supprimer un point\n"
             << "c1 - Surfaces (ordre des IDs)\n"
             << "c2 - Surfaces (distance minimale)\n"
             << "q  - Quitter\n> ";

        getline(cin, cmd);

        if (cmd == "q")
            break;

        if (cmd == "a")
        {
            cout << "\nListe des Points:\n";
            for (auto p : pointsMD){
                if (!p) continue;
                p->afficher();
            }

            for (auto n : nuages)
            {
                cout << "Nuage '" << n->getTexture()
                     << "' contient les points: ";

                const auto &pts = n->getPoints();
                for (size_t i = 0; i < pts.size(); ++i)
                {
                    cout << pts[i]->getId();
                    if (i < pts.size() - 1)
                        cout << ", ";
                }
                cout << "\n";
            }
            continue;
        }
        else if (cmd == "f")
        {
            cout << "Entrez les IDs des points a fusionner (ex: 0 2 5) : ";
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

            cout << "Texture du nuage : ";
            char t;
            cin >> t;
            cin.ignore(); // vider le buffer

            // Créer un nouveau Nuage
            Nuage *n = new Nuage(nuages.size(), t);

            // Ajouter les points dans le nuage
            for (int i : ids)
            {
                if (i >= 0 && i < pointsMD.size())
                    n->ajouterPoint(pointsMD[i]);
                else
                    cout << "ID " << i << " invalide !" << endl;
            }

            n->appliquerTexture(t);
            nuages.push_back(n);

            continue;
        }

        else if (cmd == "c1")
        {
            if (nuages.empty())
            {
                cout << "Aucun nuage n'existe encore." << endl;
                continue;
            }

            cout << "ID du nuage : ";
            int nid;
            cin >> nid;
            cin.ignore();

            if (nid < 0 || nid >= nuages.size())
            {
                cout << "Nuage invalide." << endl;
                continue;
            }

            Nuage *n = nuages[nid];
            SurfaceC1 strat;

            auto lignes = strat.construire(*n);

            // Prépare une grille vide
            vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));

            // Trace les lignes ASCII
            for (auto &L : lignes)
            {
                tracerLigne(grille,
                            L.a->getX(), L.a->getY(),
                            L.b->getX(), L.b->getY());
            }

            // Affiche la grille
            for (int y = HAUTEUR - 1; y >= 0; --y)
            {
                for (int x = 0; x < LARGEUR; ++x)
                    cout << grille[y][x];
                cout << '\n';
            }

            continue;
        }
        else if (cmd == "c2")
        {
            if (nuages.empty())
            {
                cout << "Aucun nuage n'existe encore." << endl;
                continue;
            }

            cout << "ID du nuage : ";
            int nid;
            cin >> nid;
            cin.ignore();

            if (nid < 0 || nid >= nuages.size())
            {
                cout << "Nuage invalide." << endl;
                continue;
            }

            Nuage *n = nuages[nid];
            SurfaceC2 strat;

            auto lignes = strat.construire(*n);

            vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));

            for (auto &L : lignes)
            {
                tracerLigne(grille,
                            L.a->getX(), L.a->getY(),
                            L.b->getX(), L.b->getY());
            }

            for (int y = HAUTEUR - 1; y >= 0; --y)
            {
                for (int x = 0; x < LARGEUR; ++x)
                    cout << grille[y][x];
                cout << '\n';
            }

            continue;
        }
        else if (cmd == "o1")
        {
            vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));

            for (auto p : pointsMD)
            {   
                if (!p) continue;
                int x = p->getX();
                int y = p->getY();

                if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR){
                    char t = p->getTexture();
                    grille[y][x] = (t == ' ' ? '.' : t);
                }
            }

            // Affichage
            for (int y = HAUTEUR - 1; y >= 0; --y)
            {
                for (int x = 0; x < LARGEUR; ++x)
                    cout << grille[y][x];
                cout << '\n';
            }

            continue;
        }
        else if (cmd == "o2")
        {
            vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));

            for (auto p : pointsMD)
            {   
                if (!p) continue;
                int x = p->getX();
                int y = p->getY();
                int id = p->getId();

                if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                    grille[y][x] = (id < 10 ? ('0' + id) : '*');
            }

            for (int y = HAUTEUR - 1; y >= 0; --y)
            {
                for (int x = 0; x < LARGEUR; ++x)
                    cout << grille[y][x];
                cout << '\n';
            }

            continue;
        }

        else if (cmd == "d")
        {
            cout << "ID du point a deplacer : ";
            int id;
            cin >> id;
            cin.ignore();

            if (id < 0 || id >= pointsMD.size())
            {
                cout << "Point invalide." << endl;
                continue;
            }

            cout << "Nouvelle position X Y : ";
            int nx, ny;
            cin >> nx >> ny;
            cin.ignore();

            pointsMD[id]->setPosition(nx, ny);

            cout << "Point " << id << " deplace." << endl;
            continue;
        }
        else if (cmd == "s")
        {
            cout << "ID du point a supprimer : ";
            int id;
            cin >> id;
            cin.ignore();

            if (id < 0 || id >= pointsMD.size())
            {
                cout << "Point invalide." << endl;
                continue;
            }

            PointMD *cible = pointsMD[id];

            // 1. Retirer des nuages
            for (auto n : nuages)
                n->retirerPoint(id);

            // 2. Supprimer du vector pointsMD (on laisse un nullptr à la place)
            pointsMD[id] = nullptr;

            cout << "Point " << id << " supprime." << endl;
            continue;
        }

        // Les autres commandes seront ajoutées ensuite
    }

    return 0;
}
