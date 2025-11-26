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

        // Lecture des points d'entrée
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

        // // ========= TESTS (pour tester les fct avant de le faire avec les cmd du exe ) ========= 
        // cout << "=== TEST PointMD ===" << endl;
        // PointMD p1(0, 5, 3, 'o');
        // PointMD p2(1, 10, 8, '#');
        // p1.afficher(); p2.afficher();
        // p1.setPosition(7,4); p1.setTexture('$'); p1.afficher();
        // cout << "=== FIN TEST PointMD ===" << endl;

        // cout << "\n=== TEST NUAGE ===" << endl;
        // PointMD* pA = new PointMD(0, 5, 5, 'o');
        // PointMD* pB = new PointMD(1, 10, 7, '#');
        // Nuage n1(100, 'o');
        // n1.ajouterPoint(pA); n1.ajouterPoint(pB);
        // n1.afficher();
        // n1.appliquerTexture('$');
        // n1.afficher();
        // cout << "=== FIN TEST NUAGE ===" << endl;

        // cout << "\n=== TEST STRATEGY ===" << endl;
        // Nuage n2(200, 'o');
        // PointMD* sA = new PointMD(10, 2, 2);
        // PointMD* sB = new PointMD(20, 8, 5);
        // PointMD* sC = new PointMD(30, 15, 3);
        // n2.ajouterPoint(sA); n2.ajouterPoint(sB); n2.ajouterPoint(sC);
        // SurfaceC1 c1; SurfaceC2 c2;
        // auto c1l = c1.construire(n2);
        // auto c2l = c2.construire(n2);
        // cout << "C1 lignes : " << c1l.size() << endl;
        // cout << "C2 lignes : " << c2l.size() << endl;
        // cout << "=== FIN TEST STRATEGY ===" << endl;
        // // =============================================================

        // POINTS ASCII
        vector<Point> pointsAff = creerPoints(args);
        imprimerGrille(pointsAff);

        // POINTS DU MODELE
        vector<PointMD*> pointsMD;
        int idCounter = 0;
        for (auto &p : pointsAff)
            pointsMD.push_back(new PointMD(idCounter++, p.x, p.y, ' '));

        // STOCKAGE DES NUAGE POUR COMMANDE 'a'
        vector<Nuage*> nuages;

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

            else if (cmd == "a")
            {
                cout << "\nListe des Points :\n";
                for (auto p : pointsMD)
                {
                    cout << p->getId() << ": (" 
                        << p->getX() << "," 
                        << p->getY() << ")  texture='" 
                        << p->getTexture() << "'" 
                        << endl;
                }

                cout << "\nListe des Nuages \n";
                for (auto n : nuages)
                    n->afficher();

                continue;
            }
        }

        return 0;
    }
