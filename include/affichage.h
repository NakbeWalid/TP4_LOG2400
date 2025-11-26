#pragma once
#include <vector>
#include <string>
using std::string;
using std::vector;

const int LARGEUR = 30;
const int HAUTEUR = 20;

struct Point {
    int x, y;
};

std::vector<Point> creerPoints(const std::string& ligne);
void tracerLigne(std::vector<std::vector<char>>& grille, int x0, int y0, int x1, int y1);
void imprimerGrille(const std::vector<Point>& points);
void tracerLigne(vector<vector<string>> &grille,
                 int x1, int y1, int x2, int y2);
