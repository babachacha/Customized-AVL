#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tp4.h"

T_Noeud *CreerNoeud(char *mot) {
    T_Noeud *nouveau = malloc(sizeof(T_Noeud));
    if(nouveau != NULL){
        nouveau->mot = strdup(mot);
        nouveau->nombre_occurences = 1;
        nouveau->fils_droit = NULL;
        nouveau->fils_gauche = NULL;
    }
    return nouveau;
}
T_Arbre AjouterNoeud(T_Arbre t,char* mot){
    for (int i=0; i<strlen(mot); i++)
        mot[i] = tolower(mot[i]);
    T_Arbre noeud = CreerNoeud(mot);
    if(t == NULL){
        t = noeud;
        return t;
    }
    T_Arbre pere = NULL;
    T_Arbre fils = t;
    while (fils){
        pere = fils;
        if (strcmp(noeud->mot, fils->mot)<0)
            fils = fils->fils_gauche;
        else if(strcmp(noeud->mot, fils->mot)>0)
            fils = fils->fils_droit;
        else{
            fils->nombre_occurences++;
            return t;
        }
    }
    if(strcmp(noeud->mot, pere->mot)<0)
        pere->fils_gauche = noeud;
    else
        pere->fils_droit = noeud;
    return t;
}

T_Arbre Pere(T_Arbre t,char* mot){
    if (t == NULL || (strcmp(t->mot,mot) == 0))
        return NULL;
    if (strcmp(mot,t->mot) < 0){
        if (t->fils_gauche == NULL)
            return NULL;
        if (strcmp(t->fils_gauche->mot,mot) == 0)
            return t;
        return Pere(t->fils_gauche,mot);
    }
    if (strcmp(mot,t->mot) > 0){
        if (t->fils_droit == NULL)
            return NULL;
        if (strcmp(t->fils_droit->mot,mot) == 0)
            return t;
        return Pere(t->fils_droit,mot);
    }
}

T_Arbre Successeur(T_Arbre t){
    T_Arbre ptr;
    if(t->fils_droit != NULL){
        ptr = t->fils_droit;
    while(ptr->fils_gauche != NULL)
        ptr = ptr->fils_gauche;
    }else{
        ptr = Pere(t,t->mot);
        while((ptr != NULL) && (t == ptr->fils_droit)){
            t=ptr;
            ptr=Pere(t,t->mot);
        }
    }return ptr;
}

T_Arbre Predecesseur(T_Arbre t){
    T_Arbre ptr;
    if(t->fils_gauche != NULL){
        ptr = t->fils_gauche;
    while(ptr->fils_droit != NULL)
        ptr = ptr->fils_droit;
    }else{
        ptr = Pere(t,t->mot);
        while((ptr != NULL) && (t == ptr->fils_gauche)){
            t=ptr;
            ptr=Pere(t,t->mot);
        }
    }return ptr;
}

T_Arbre RetirerMot(T_Arbre t, char* mot){
    if (t == NULL)
        return NULL;
    else if (strcmp(mot, t->mot) < 0)
        t->fils_gauche = RetirerMot(t->fils_gauche, mot);
    else if (strcmp(mot, t->mot) > 0)
        t->fils_droit = RetirerMot(t->fils_droit, mot);
    else if (t->nombre_occurences > 1){
        t->nombre_occurences--;
        return t;
    }else{
        if(t->fils_gauche == NULL)
            return t->fils_droit;
        else if(t->fils_droit == NULL)
            return t->fils_gauche;
        else{
            T_Arbre s = Successeur(t);
            t->mot = s->mot;
            t->fils_droit = RetirerMot(t->fils_droit,s->mot);
            free(s);
        }
    }
    return t;
}

void forder(T_Arbre t,T_Arbre* arr,int len){
    if(t){
        arr[len++]=t;
        forder(t->fils_gauche,arr,len);
        forder(t->fils_droit,arr,len);
    }
}

void Afficher(T_Arbre t){
	if (t==NULL)
        printf("Arbre est vide!\n");
    else{
        //trier
        T_Arbre arr[MAX_LENGTH];
        for(int i=0;i<MAX_LENGTH;i++)
            arr[i]=NULL;
        forder(t,arr,0);
        int nbr=0;
        while (arr[nbr])
            nbr++;
        T_Arbre tem;
        for(int i = 0; i<nbr; ++i){
            for(int j=0; j<nbr-1-i;j++){
                if (strcmp(arr[j]->mot, arr[j+1]->mot)>0){
                    tem = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = tem;
                }
            }
        }//Bubble Sort, changer apres
        //afficher
        char initial = '=';
        int k=0;
        while (arr[k]){
            if (arr[k]->mot[0] == initial + 32 || arr[k]->mot[0] == initial)
                printf("  ---%s [%d]\n", arr[k]->mot, arr[k]->nombre_occurences);
            else {
                initial = arr[k]->mot[0];
                printf("%c ---%s [%d]\n", toupper(initial) , arr[k]->mot, arr[k]->nombre_occurences);
            k++;
            }
        }
    }
}
void viderBuffer(){
    int c = '0';
    while (c!='\n' && c != EOF)
            c = getchar();
}
