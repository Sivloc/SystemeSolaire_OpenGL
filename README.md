# Système Solaire en OpenGL

## Introduction
Projet de découverte d'Open_GL

## Fonctionnalités
- Visualisation du système solaire en 3D.
- Déplacement avec les touches ZQSD.
- Déplacer la vue avec la souris.
- Changement de vue sur les planètes avec les touches de 1 à 8.
- Retour à la vue de base avec la touche 0.
- Accélération ou ralentissement des planètes avec les touches flèche gauche et flèche droite.

## Prérequis
- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)

## Configuration
Avant de compiler le projet, assurez-vous de configurer le chemin (path) correct à la ligne 22 du fichier main.cpp. Remplacez le chemin actuel par le chemin absolu vers votre dossier contenant les ressources nécessaires.

```cpp
// Changer le chemin vers le dossier des ressources
string path = "/chemin/vers/votre/dossier/SystemeSolaire_OpenGL";
```
Changez également le chemin des 4 fichiers .obj utilisés, lignes 111 à 114 : 
```cpp
const char *sphere = "/chemin/vers/votre/dossier/SystemeSolaire_OpenGL/obj/planete.obj";
const char *cube = "/chemin/vers/votre/dossier/SystemeSolaire_OpenGL/obj/cube.obj";
const char *orbite = "/chemin/vers/votre/dossier/SystemeSolaire_OpenGL/obj/orbite_50.obj";
const char *anneau = "/chemin/vers/votre/dossier/SystemeSolaire_OpenGL/obj/anneau.obj";
```
Changez aussi ce paramètre si vous souhaitez afficher les orbites des planètes, ligne 24 : 
```cpp
// Changer le false en true pour afficher les orbites
bool displayOrbites = false;
```
