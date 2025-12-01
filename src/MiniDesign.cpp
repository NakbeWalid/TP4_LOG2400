#include "affichage.h"
#include "affichage_template.h"
#include "affichage_texture.h"
#include "affichage_id.h"
#include "point.h"
#include "nuage.h"
#include "surface_strategy.h"
#include "surface_c1.h"
#include "surface_c2.h"
#include "texture_decorator.h"
#include "manager.h"
#include "cmd_deplacer.h"
#include "cmd_supprimer.h"
#include "cmd_fusionner.h"
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
             << "o1 - Afficher l'orthese avec les textures des points\n"
             << "o2 - Afficher l'orthese avec les IDs des points\n"
             << "f  - Fusionner des points dans un nuage (et appliquer texture)\n"
             << "d  - Deplacer un point (ID)\n"
             << "s  - Supprimer un point (ID)\n"
             << "u - Annuler la dernière commande (undo)\n"
             << "r- Reappliquer la derniêre commande annulee (redo)\n"
             << "c1 - Creer les surfaces selon l'ordre des IDs\n"
             << "c2 - Creer les surfaces selon la distance minimale\n"
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

            // Séparer points et nuages
            vector<PointMD *> points;
            vector<Nuage *> clouds;

            for (auto e : manager.getElements())
            {
                if (auto p = dynamic_cast<PointMD *>(e))
                    points.push_back(p);
                else if (auto n = dynamic_cast<Nuage *>(e))
                    clouds.push_back(n);
            }

            // Trier par ID
            sort(points.begin(), points.end(),
                 [](PointMD *a, PointMD *b)
                 { return a->getId() < b->getId(); });

            sort(clouds.begin(), clouds.end(),
                 [](Nuage *a, Nuage *b)
                 { return a->getId() < b->getId(); });

            // --- 1) Affichage des points ---
            for (auto p : points)
            {
                // Utiliser la methode afficher() qui peut etre surchargee par le Decorator
                // Le Decorator delegue a l'element, donc on peut utiliser directement l'element
                // Les textures sont deja appliquees par les decorators dans CmdFusionner
                p->afficher();
            }

            // --- 2) Affichage des nuages ---
            for (auto n : clouds)
            {
                cout << n->getId() << ": Nuage '" << n->getTexture()
                     << "' contient les elements: ";

                for (auto child : n->getEnfants())
                {
                    if (auto p = dynamic_cast<PointMD *>(child))
                        cout << p->getId() << " ";
                    else if (auto sub = dynamic_cast<Nuage *>(child))
                        cout << sub->getId() << " ";
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



            Commande *c = new CmdSupprimer(*container, element);
            invoker.executer(c);

            cout << "Element contenant le point " << id << " supprime.\n";
            continue;
        }
        // FUSIONNER DES POINTS/NUAGE DANS UN NOUVEAU NUAGE (Command Pattern)
        else if (cmd == "f")
        {
            cout << "IDs de points/nuages a fusionner (ex: 0 2 5): ";
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

            CmdFusionner* c = new CmdFusionner(elements, nuages, manager, texturesNuages, ids);
            invoker.executer(c);
            continue;
        }

        // CREER LES SURFACES C1 (ordre des IDs)
        else if (cmd == "c1")
        {
            lignesC1.clear();
            lignesC2.clear(); 
            SurfaceC1 strat;

            if (nuages.empty())
            {
                cout << "Aucun nuage disponible. Utilisez 'f' pour creer des nuages.\n";
                continue;
            }

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
                // ICI FAUT CHANGER LE CODE JE PENSE PARCE QUE ON VA SUPPOSER QUE UN NUAGE CONTIENT AU MOINS 2 points
                auto pts = n->getPoints();
                // ⚠ NE PAS CONSTRUIRE UNE SURFACE POUR < 2 POINTS
                if (pts.size() < 2)
                {
                    cout << "Nuage " << n->getId() << " a seulement " << pts.size() << " point(s), ignore.\n";
                    continue;
                }

                auto Ls = strat.construire(*n);
                lignesC1.insert(lignesC1.end(), Ls.begin(), Ls.end());
            }

            cout << "Surfaces C1 mises a jour. (" << lignesC1.size() << " lignes creees)\n";
            continue;
        }

        // CREER LES SURFACES C2 (distance minimale)
        else if (cmd == "c2")
        {
            lignesC1.clear();
            lignesC2.clear();
            SurfaceC2 strat;

            if (nuages.empty())
            {
                cout << "Aucun nuage disponible. Utilisez 'f' pour creer des nuages.\n";
                continue;
            }

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

                auto pts = n->getPoints();
                if (pts.size() < 2)
                {
                    cout << "Nuage " << n->getId() << " a seulement " << pts.size() << " point(s), ignore.\n";
                    continue;
                }

                auto Ls = strat.construire(*n);
                lignesC2.insert(lignesC2.end(), Ls.begin(), Ls.end());
            }

            cout << "Surfaces C2 mises a jour. (" << lignesC2.size() << " lignes creees)\n";
            continue;
        }

        // ORTHESE TEXTURES (Template Method)
        else if (cmd == "o1")
        {
            AffichageTexture affichage;
            affichage.afficher(manager.getElements(), 
                              lignesC1.empty() ? nullptr : &lignesC1,
                              lignesC2.empty() ? nullptr : &lignesC2);
            continue;
        }
        
        // ORTHESE IDs (Template Method)
        else if (cmd == "o2")
        {
            AffichageID affichage;
            affichage.afficher(manager.getElements(),
                              lignesC1.empty() ? nullptr : &lignesC1,
                              lignesC2.empty() ? nullptr : &lignesC2);
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