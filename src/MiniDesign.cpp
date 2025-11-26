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
            for (auto p : pointsMD)
                p->afficher();

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

            nuages.push_back(n);

            cout << "Nuage #" << n->getId() << " cree !" << endl;

            continue;
        }

        // Les autres commandes seront ajoutées ensuite
    }

    return 0;
}
