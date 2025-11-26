===========================================
 TP4 LOG2400 - MiniDesign
===========================================

Ce projet implémente le système MiniDesign dans le cadre du cours LOG2400.
Il inclut la gestion des Points, des Nuages, des Textures et des Surfaces,
ainsi qu’une interface console permettant de manipuler et afficher ces données.

Les fichiers se trouvent dans deux dossiers :
    /include  → fichiers .h
    /src      → fichiers .cpp

Le fichier MiniDesign.cpp contient le programme principal (main).

-------------------------------------------
1. PRÉREQUIS
-------------------------------------------

Sous Windows, assurez-vous d’avoir installé :
- MinGW (g++)
- mingw32-make (fourni avec MinGW)

Vérifiez que C:\MinGW\bin est bien dans votre variable PATH.
Pour tester :

    g++ --version
    mingw32-make --version

-------------------------------------------
2. COMPILATION
-------------------------------------------

La compilation se fait via l’outil suivant :

    mingw32-make

et NON via la commande « make », car celle-ci n’est pas disponible
nativement sous Windows PowerShell.

L’exécutable généré sera :

    MiniDesign.exe

-------------------------------------------
3. NETTOYAGE DES FICHIERS (make clean)
-------------------------------------------

Pour supprimer les fichiers intermédiaires et l’exécutable, utilisez :

    mingw32-make clean

⚠ Important :
- Sous Windows, la commande `rm` n’existe pas.
- Le Makefile utilise donc explicitement la commande Windows `del`.

Voici la règle clean utilisée :

    clean:
        del src\*.o
	    del MiniDesign.exe

-------------------------------------------
4. EXÉCUTION
-------------------------------------------

Pour lancer le programme :

    ./MiniDesign.exe "(5,0) (14,16) (23,0) (0,8) (0,0) (28,8)"

Ou laissez le programme vous demander une entrée :

    ./MiniDesign.exe

Et entrez :

    (5,0) (10,12) (23,3) ...

-------------------------------------------
5. UTILISATION DU MENU
-------------------------------------------

Une fois lancé, le programme offre plusieurs commandes :

    a  - Afficher les points et les nuages
    o1 - Afficher l'orthèse (textures)
    o2 - Afficher l'orthèse (IDs)
    f  - Fusionner des points dans un nuage
    d  - Déplacer un point
    s  - Supprimer un point
    c1 - Créer les surfaces (ordre des IDs)
    c2 - Créer les surfaces (distance minimale)
    q  - Quitter

-------------------------------------------
6. REMARQUES IMPORTANTES
-------------------------------------------

- Le projet compile uniquement via mingw32-make sous Windows.
- Aucun CMake n’est requis : seul le Makefile est utilisé.
- Les fichiers doivent être bien classés dans /src et /include.
- Si vous modifiez la structure, adaptez le Makefile en conséquence.

-------------------------------------------
7. CONTACT
-------------------------------------------

En cas de questions :
Yahia — étudiant génie info Polytechnique Montréal
