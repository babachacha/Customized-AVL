#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tp3.h"

// Cr�ation nouvel �l�ment
t_mot *creerMot(char *mot) {
    t_mot *nouveau = malloc(sizeof(t_mot));
    if(nouveau != NULL){
        nouveau->mot = strdup(mot);
        nouveau->nombre_occurences = 1;
        nouveau->suivant = NULL;
    }
    return nouveau;
}

/* ====== FIN creerMot ====== */

// Ajout mot dans une liste
t_mot *ajouterMot(t_mot *liste, char *mot) {
    if(mot == NULL)return liste;
    t_mot *precedent = NULL,*courant = liste;
    for(int i=0; i<strlen(mot);i++){mot[i] = tolower(mot[i]);}
    if(liste == NULL || strcmp(liste->mot,mot) > 0){
        t_mot *nouveau = creerMot(mot);
        nouveau->suivant = liste;
        return nouveau;
    }
    while(courant != NULL && strcmp(courant->mot,mot) < 0){
        precedent = courant;
        courant = courant->suivant;
    }

    if(courant == NULL || strcmp(courant->mot,mot) > 0){
        t_mot *nouveau = creerMot(mot);
        precedent->suivant = nouveau;
        nouveau->suivant = courant;
    }else{
        courant->nombre_occurences++;
    }
    return liste;
}
/* ====== FIN ajouterMot ====== */

// Retrait occurence mot d'une liste
t_mot *retirerMot(t_mot *liste, char *mot) {
    if(liste == NULL){
        printf("\n\n\tLA LISTE EST VIDE\n\n");
        return NULL;
    }

    t_mot *courant = liste;
    t_mot *precedent = NULL;
    if(strcmp(courant->mot,mot) == 0){
        courant->nombre_occurences--;
        if(courant->nombre_occurences == 0){
            t_mot *newHead = courant->suivant;
            free(courant->mot);
            free(courant);
            return newHead;
        }
    }

    precedent = liste;
    courant = liste->suivant;
    while(courant!=NULL){
        if(strcmp(courant->mot,mot) == 0){
            courant->nombre_occurences--;
            if(courant->nombre_occurences == 0){
                precedent->suivant = courant->suivant;
                free(courant);
            }
            break;
        }
        precedent = courant;
        courant = courant->suivant;
    }
    return liste;
}
// ====== FIN retirerMot ======


// Affichage mots d'un lexique
void afficherMots(t_mot *liste,int ID){
    t_mot *courant = liste;
    if(liste == NULL){
        printf("\n\n\tLA LISTE ID(%d) EST VIDE\n\n",ID);
        return;
    }
    char prefixe = '-';
    printf("\n\n==================\nID(%d)",ID);
    while(courant != NULL){
        if(courant->mot[0] == prefixe){
            printf("\n    --- %s [%d]",courant->mot,courant->nombre_occurences);
        }else{
            prefixe = courant->mot[0];
            printf("\n%c   --- %s [%d]",toupper(prefixe),courant->mot,courant->nombre_occurences);
        }
        courant = courant->suivant;
    }
    printf("\n==================\n\n");
}
/* ====== FIN afficherMots ====== */


// Fusion listes
t_mot *fusionner(t_mot *listeA, t_mot *listeB){
    if(listeB ==NULL){
        return listeA;
    }
    if(listeA == NULL){
        return listeB;
    }

    t_mot *ptrA = listeA;
    t_mot *ptrB = listeB;
    t_mot *temp = NULL;
    t_mot *precedentPtrA = NULL;
    while(ptrA != NULL && ptrB != NULL){
        if(strcmp(ptrA->mot,ptrB->mot) == 0){
            temp = ptrB;
            ptrB = ptrB->suivant;
            ptrA->nombre_occurences += temp->nombre_occurences;
            precedentPtrA = ptrA;
            ptrA = ptrA->suivant;
            free(temp);
        }
        else if(strcmp(ptrA->mot,ptrB->mot) > 0){
            temp = ptrB;
            ptrB = ptrB->suivant;
            if(precedentPtrA == NULL){
                listeA = temp;
                listeA->suivant = ptrA;
            }
            else{
                precedentPtrA->suivant = temp;
                temp->suivant = ptrA;
            }
            precedentPtrA = temp;
            continue;
        }
        else{
            precedentPtrA = ptrA;
            ptrA = ptrA->suivant;
        }
    }

    if(ptrA == NULL){
        precedentPtrA->suivant = ptrB;
    }
    return listeA;
}
/* ====== FIN fusionner ====== */


// Import fichier de mots dans une liste
t_mot *importerFichier(t_mot *liste){
    FILE *fp = NULL;
    char mot[30];
    char nomFichier[30];
    printf("\n\t<Entrez le chemin du fichier (avec double-slash comme s�parateur)>\n\t");
    scanf("%s",nomFichier); //lit avec les espaces
    viderBuffer();
    fp = fopen(nomFichier, "r");
    if(fp == NULL)
        printf("\n\n\tErreur dans le chemin du fichier\n\n");
    else{
        printf("\n\n\tFichier ouvert avec succ�s\n\n");
        while(!feof(fp)){ //tant que l'on est pas �� la fin du fichier
            fscanf(fp,"%s",mot);
            liste = ajouterMot(liste,mot);
        }
    }
    return liste;
}
/* ====== FIN importerFichier ====== */


// fonction utile pour vider le tampon clavier
void viderBuffer() {
    int c = '0';
    while (c!='\n' && c != EOF) { c = getchar(); }
}

int getlexique(){//Pour juger si le lexique a d�pass� la limite
    char str[20]="\0";
    gets(str);
    int sum = 0;
    for(int i=0;i<strlen(str);i++)
        sum = sum*10+(str[i]-'0');
    if(sum<0 || sum>(MAX_NUM_LEXIQUE-1)){
        printf("\n\t<Invalide ID!>\n>");
        return -1;
    }else
        return sum;
}
