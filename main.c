#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include "tp3.h"

int main(){
    char choixMenu = '0';
    char mot[MAX_LENGTH];
    t_mot *listeA;
    T_Arbre lexique[MAX_LENGTH];
    for(int i=0;i<MAX_LENGTH;i++)
        lexique[i] = NULL;
    int arbre_nbr = 0;
    int id,id1,id2;
    char char_tem;
    do {
        printf("\n========================================");
        printf("\n  [1] Creer un nouvel arbre");
        printf("\n  [2] Afficher un arbre");
        printf("\n  [3] Ajouter un mot dans un arbre");
        printf("\n  [4] Retirer un mot d'un arbre");
        printf("\n  [5] Verifier si un arbre est parfait");
        printf("\n  [6] Verifier si un arbre est equilibre");
        printf("\n  [7] Transformer un arbre en un lexique en liste lineairement chainee et afficher le lexique");
        printf("\n  [8] Tester la similarite entre deux textes");
        printf("\n  [9] Quitter");
        printf("\n========================================");
        printf("\nVotre choix : ");
        choixMenu = getchar();
        viderBuffer();

        switch (choixMenu) {
            case '1' :
                printf("\n\n\t<Creer un nouvel arbre>\n\n");
                scanf("%s", mot);
                lexique[arbre_nbr] = CreerNoeud(mot);
                arbre_nbr++;
                printf("Le numero de l'arbre est %d\n",arbre_nbr);
                viderBuffer();
                break;
            case '2' :
                printf("\n\n\t<Afficher un arbre>\n\n");
                printf("Afficher quel arbre? Entrer son numero:\n");
                scanf("%d", &id);
                Afficher(lexique[id-1]);
                viderBuffer();
                break;
            case '3' :
                printf("\n\n\t<Ajouter un mot dans un arbre>\n\n");
                printf("Voulez-vous ajouter le mot dans l'arbre %d ? Y/N\n",arbre_nbr);
                char_tem=getchar();
                if (char_tem == 'N' || char_tem =='n'){
                    printf("Numero d'arbre:\n");
                    scanf("%d", &arbre_nbr);
                }
                printf("Mot:\n");
                scanf("%s", mot);
                lexique[arbre_nbr-1] = AjouterNoeud(lexique[arbre_nbr-1],mot);
                viderBuffer();
                break;
            case '4' :
                printf("\n\n\t<Retirer un mot d'un arbre>\n\n");
                printf("Voulez-vous retirer le mot de l'arbre %d ? Y/N\n",arbre_nbr);
                char_tem=getchar();
                if (char_tem == 'N' || char_tem =='n'){
                    printf("Numero d'arbre:\n");
                    scanf("%d", &arbre_nbr);
                }
                printf("Mot:\n");
                scanf("%s", mot);
                lexique[arbre_nbr-1] = RetirerMot(lexique[arbre_nbr-1],mot);
                viderBuffer();
                break;
            case '5' :
                // Vérifier si un arbre est parfait
                printf("\n\n\t<Test parfait>\n\n");
                printf("Quel arbre? Entrer son numero:\n");
                scanf("%d", &id);
                if(IsParfait(lexique[id-1])){
                    printf("\n\n est Parfait\n\n");
                }
                else{
                    printf("\n\n n'est pas Parfait\n\n");
                }
                viderBuffer();
                break;
            case '6' :
                // Vérifier si un arbre est équilibré
                printf("\n\n\t<Test equilibre>\n\n");
                printf("Quel arbre? Entrer son numero:\n");
                scanf("%d", &id);
                if(IsEquilibre(lexique[id-1])){
                    printf("\n\n est equilibre\n\n");
                }
                else{
                    printf("\n\n n'est pas equilibre\n\n");
                }
                viderBuffer();
                break;
            case '7' :
                // Transformer un arbre en un lexique en liste linéairement chaînée et afficher le lexique
                printf("\n\n\t<Test parfait>\n\n");
                printf("Quel arbre? Entrer son numero:\n");
                scanf("%d", &id);
                listeA = ArbreToLexique(lexique[id-1]);
                afficherMots(listeA,id);
                DeleteListe(listeA);
                break;
            case '8' :
                printf("\n\n\t<Similarite entre deux textes>\n\n");
                printf("Quel arbre? Entrer son numero:\n");
                scanf("%d", &id1);
                printf("Quel arbre? Entrer son numero:\n");
                scanf("%d", &id2);
                printf("\n L'indice de Jaccard: ");
                printf("%lf",Similarite(lexique[id1-1],lexique[id2-1]));
                viderBuffer();
                break;
        }
    } while (choixMenu != '9');
    printf("\n\n*** FIN DU PROGRAMME ***\n");
    for(int i = 0;i<MAX_LENGTH;i++){
        if(lexique[i]!=NULL){
            // 后序遍历
            PostOrderDelete(lexique[i]);
            printf("liste [%d] est vide!\n",i+1);
        }
    }
    return 0;
}
