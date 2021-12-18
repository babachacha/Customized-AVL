#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED
#define MAX_LENGTH 100
#define MAXP 100
#include "tp3.h"

struct noeud {
    char* mot;
    int nombre_occurences;
    struct noeud* fils_droit;
    struct noeud* fils_gauche;
    struct noeud* next;
};

typedef struct noeud T_Noeud;
typedef struct noeud* T_Arbre;
typedef struct pile {
    int sommet ; // Indice de l�element au sommet de la pile
    T_Arbre tab[MAXP];
}pile;

pile creer_pile ();
int pile_vide (pile * p);
int pile_pleine (pile * p);
int empiler (pile * p, T_Arbre val);
T_Arbre depiler (pile * p);
void afficher_pile (pile p);

T_Arbre CreerNoeud(char* mot);
T_Arbre AjouterNoeud(T_Arbre t, char* mot);
T_Arbre Pere(T_Arbre t,char* mot);
T_Arbre Successeur(T_Arbre t);
T_Arbre Predecesseur(T_Arbre t);
T_Arbre RetirerMot(T_Arbre t, char* mot);
void Afficher(T_Arbre t);
void viderBuffer();

int max(int a,int b);
int Hauteur(T_Arbre t);
int CalNode(T_Arbre t);
void InOrder(T_Arbre t, t_mot* liste);
void PostOrderDelete(T_Arbre t);
int IsParfait(T_Arbre t);
int IsEquilibre(T_Arbre t);
t_mot* ArbreToLexique(T_Arbre t);
void DeleteListe(t_mot* liste);
t_mot *ajouterMot_TP4(t_mot *liste, T_Arbre t);
T_Arbre min_Node(T_Arbre t);
T_Arbre max_Node(T_Arbre t);
double Similarite(T_Arbre t1,T_Arbre t2);




#endif
