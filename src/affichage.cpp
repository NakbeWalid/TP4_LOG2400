#include "affichage.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>



using namespace std;

void tracerLigne(vector<vector<string>> &grille,
                 int x0, int y0, int x1, int y1)
{
    int lignes = abs(y1 - y0);
    if (lignes == 0) {
        lignes = abs(x1 - x0);
        if (lignes == 0) {
            if (y0 >= 0 && y0 < HAUTEUR && x0 >= 0 && x0 < LARGEUR)
                grille[y0][x0] = "/";
            return;
        }
        for (int i = 0; i <= lignes; ++i) {
            int x = (x0 < x1) ? x0 + i : x0 - i;
            if (y1 >= 0 && y1 < HAUTEUR && x >= 0 && x < LARGEUR)
                grille[y1][x] = "/";
        }
    } else {
        for (int i = 0; i <= lignes; ++i) {
            double t = (double)i / lignes;
            int x = round(x0 + t * (x1 - x0));
            int y = round(y0 + t * (y1 - y0));
            if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                grille[y][x] = "/";
        }
    }
}


void tracerLigne(vector<vector<char>>& grille, int x0, int y0, int x1, int y1) {
    int lignes = abs(y1 - y0);
    if (lignes == 0) {
        lignes = abs(x1 - x0);
        if (lignes == 0) {
            if (y0 >= 0 && y0 < HAUTEUR && x0 >= 0 && x0 < LARGEUR)
                grille[y0][x0] = '/';
            return;
        }
        for (int i = 0; i <= lignes; ++i) {
            int x = (x0 < x1) ? x0 + i : x0 - i;
            if (y1 >= 0 && y1 < HAUTEUR && x >= 0 && x < LARGEUR)
                grille[y1][x] = '/';
        }
    } else {
        for (int i = 0; i <= lignes; ++i) {
            double t = (double)i / lignes;
            int x = round(x0 + t * (x1 - x0));
            int y = round(y0 + t * (y1 - y0));
            if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                grille[y][x] = '/';
        }
    }
}


void imprimerGrille(const vector<Point>& points) {
    vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));

    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x)
            cout << grille[y][x];
        cout << '\n';
    }
}



vector<Point> creerPoints(const string& ligne) {
    vector<Point> points;
    istringstream iss(ligne);
    string token;
    while (iss >> token) {
        if (token.size() >= 3 && token.front() == '(' && token.back() == ')') {
            token = token.substr(1, token.size() - 2);
            replace(token.begin(), token.end(), ',', ' ');
            istringstream pair(token);
            int x, y;
            if (pair >> x >> y) {
                points.push_back({x, y});
            }
        }
    }
    return points;
}


