#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED
#define MAX_LENGTH 100

struct noeud {
    char* mot;
    int nombre_occurences;
    struct noeud* fils_droit;
    struct noeud* fils_gauche;
};

typedef struct noeud T_Noeud;
typedef struct noeud* T_Arbre;

T_Arbre CreerNoeud(char* mot);

T_Arbre AjouterNoeud(T_Arbre t, char* mot);

T_Arbre Pere(T_Arbre t,char* mot);

T_Arbre Successeur(T_Arbre t);

T_Arbre Predecesseur(T_Arbre t);

T_Arbre RetirerMot(T_Arbre t, char* mot);

void Afficher(T_Arbre t);

void viderBuffer();


#endif
