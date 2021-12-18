#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "tp4.h"
#include "tp3.h"
pile creer_pile(){
    pile p;
    p.sommet = -1;
    return p;
}

int pile_vide(pile* p){
    return p->sommet == -1;
}
int pile_pleine(pile* p){
    return p->sommet == MAXP -1;
}
int empiler(pile *p, T_Arbre val){
    if(pile_pleine(p)){
        printf("Erreur pile pleine.\n");
        return 0;
    } else {
        p->sommet++;
        p->tab[p->sommet] = val;
        return 1;
    }
}
T_Arbre depiler(pile* p){
    if(pile_vide(p)){
        printf("Erreur pile vide.\n");
        return NULL;
    } else {
        p->sommet--;
        return p->tab[p->sommet+1];
    }
}
//afficher_pile()会将栈清空？
//不会清空，因为是值传递
void afficher_pile(pile p){
    //当栈不为空时。。。
    while(pile_vide(&p) == 0){
        printf("%s \n",depiler(&p)->mot);
    }
}






T_Noeud *CreerNoeud(char *mot) {
    T_Noeud *nouveau = malloc(sizeof(T_Noeud));
    if(nouveau != NULL){
        nouveau->mot = strdup(mot);
        nouveau->nombre_occurences = 1;
        nouveau->fils_droit = NULL;
        nouveau->fils_gauche = NULL;
        nouveau->next = NULL;
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
    return NULL;
}
T_Arbre Successeur(T_Arbre t){
    T_Arbre ptr;
    // 如果右节点非空，找右节点的左孩子
    if(t->fils_droit != NULL){
        ptr = t->fils_droit;
        while(ptr->fils_gauche != NULL)
            ptr = ptr->fils_gauche;
    }else{
        // 如果有节点为空，找
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
    {
        printf("\n\n---------Not existe!----------\n");
        return NULL;
    }
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
void Afficher(T_Arbre t){
    if(t){
        Afficher(t->fils_gauche);
        char initial = '=';
        if (t->mot[0] == initial + 32 || t->mot[0] == initial)
            printf("  ---%s [%d]\n",t->mot,t->nombre_occurences);
        else {
            initial = t->mot[0];
            printf("%c ---%s [%d]\n",toupper(initial),t->mot,t->nombre_occurences);
        }
        Afficher(t->fils_droit);
    }
}
void viderBuffer(){
    int c = '0';
    while (c!='\n' && c != EOF)
        c = getchar();
}
int max(int a,int b){
    return (a>b)?a:b;
}
int Hauteur(T_Arbre t){
    if(t == NULL){
        return 0;
    }
    else{
        int hl = Hauteur(t->fils_gauche);
        int hr = Hauteur(t->fils_droit);
        return max(hl,hr)+1;
    }
}
int CalNode(T_Arbre t){
    // 计算二叉树节点个数
    if(t == NULL){
        return 0;
    }
    else{
        return CalNode(t->fils_gauche) + CalNode(t->fils_droit) + 1;
    }
}
int IsParfait(T_Arbre t){
    // 深度为k，节点个数为2^k-1次方的树为满二叉树
    int h = Hauteur(t);
    int num = CalNode(t);
    if(pow(2,h)-1 == num){
        return 1;
    }
    else{
        return 0;
    }
}
int IsEquilibre(T_Arbre t){
    if(t == NULL){
        // 空树为平衡二叉树
        return 1;
    }
    else{
        int hl = Hauteur(t->fils_gauche);
        int hr = Hauteur(t->fils_droit);
        // 左右子树高度之差大于1，不平衡
        if(hl-hr>1 || hl-hr<-1){
            return 0;
        }
        // 左右子树都为平衡树，且高度差小于等于1，则该树为平衡树
        return IsEquilibre(t->fils_gauche) && IsEquilibre(t->fils_droit);
    }
}
void InOrder(T_Arbre t, t_mot* liste){
    if(t == NULL){
        return;
    }
    else{
        InOrder(t->fils_gauche,liste);
        ajouterMot(liste,t->mot);
        InOrder(t->fils_droit,liste);
    }
}
void afficherMotsT_Noeud(T_Arbre n){
    T_Arbre courant = n;
    if(n == NULL){
        printf("\n\n\tLA LISTE EST VIDE\n\n");
        return;
    }
    char prefixe = '-';
    printf("\n\n==================\n");
    while(courant != NULL){
        if(courant->mot[0] == prefixe){
            printf("\n    --- %s [%d]",courant->mot,courant->nombre_occurences);
        }else{
            prefixe = courant->mot[0];
            printf("\n%c   --- %s [%d]",toupper(prefixe),courant->mot,courant->nombre_occurences);
        }
        courant = courant->next;
    }
    printf("\n==================\n\n");
}
t_mot* ArbreToLexique(T_Arbre t){
    // 中序去递归，第一个节点确定为头结点，每次迭代保存当前节点
    t_mot *head = NULL;
    t_mot *cur = NULL;
    pile myPile = creer_pile();
    T_Arbre p = t;
    while(pile_vide(&myPile) == 0 || p!=NULL){
        while(p!=NULL){
            empiler(&myPile,p);
            p = p->fils_gauche;
        }
        if(pile_vide(&myPile) == 0){
            p = depiler(&myPile);
            // 如果p为第一个元素，表此时为空，那么更新head指针，将cur指针定位到head
            if(head == NULL){
                head = ajouterMot_TP4(cur,p);
                cur = head;
            }
            // 如果表非空，在完成插入后直接更新cur节点，每次插入都为O(1)
            else{
                cur = ajouterMot_TP4(cur,p);
            }
            p = p->fils_droit;
        }
    }
    return head;
}
double Similarite(T_Arbre t1,T_Arbre t2){
    t_mot *liste1 = ArbreToLexique(t1);
    t_mot *liste2 = ArbreToLexique(t2);
    double or = 0;
    double and = 0;
    while(liste1!=NULL && liste2!=NULL){
        if(strcmp(liste1->mot,liste2->mot) == 0){
            and++;
            or++;
            liste1 = liste1->suivant;
            liste2 = liste2->suivant;
        }
        else if(strcmp(liste1->mot,liste2->mot) > 0){
            // Liste1>list2
            or++;
            liste2 = liste2->suivant;
        }
        else{
            or++;
            liste1 = liste1->suivant;
        }
    }
    while(liste1!=NULL){
        or++;
        liste1 = liste1->suivant;
    }
    while(liste2!=NULL){
        or++;
        liste2 = liste2->suivant;
    }
    DeleteListe(liste1);
    DeleteListe(liste2);
    return and/or;
}
// 返回最小节点
T_Arbre min_Node(T_Arbre t){
    if(t!=NULL){
        while(t->fils_gauche!=NULL){
            t = t->fils_gauche;
        }
        return t;
    }
    else{
        printf("Input is NULL\n");
        return NULL;
    }
}
// 返回最大节点
T_Arbre max_Node(T_Arbre t){
    if(t!=NULL){
        while(t->fils_droit!=NULL){
            t = t->fils_droit;
        }
        return t;
    }
    else{
        printf("Input is NULL\n");
        return NULL;
    }
}
t_mot *ajouterMot_TP4(t_mot *liste, T_Arbre t) {
    if(t == NULL)return liste;

    // 不需要大小写转换，因为在插入树的时候，串已经被转换为小写了
    // for(int i=0; i<strlen(mot);i++){mot[i] = tolower(mot[i]);}
    t_mot *nouveau = creerMot(t->mot);
    nouveau->suivant = NULL;
    // 除了要复制串，nombre_occurences参数也需要复制
    nouveau->nombre_occurences = t->nombre_occurences;
    if(liste == NULL){
        // 如果没有表（liste == NULL），创建新节点作为表头返回
        return nouveau;
    }
    else{
        // 如果liste为表，那么在liste后面添加新节点完成复制，并返回新节点,以此实现O(1)常数级别复杂度的插入
        liste->suivant = nouveau;
        return nouveau;
    }
}
void PostOrderDelete(T_Arbre t){
    if(t!=NULL){
        return;
    }
    else{
        PostOrderDelete(t->fils_gauche);
        PostOrderDelete(t->fils_droit);
        free(t);
    }
}
void DeleteListe(t_mot* liste){
    t_mot *cur;
    while(liste!=NULL){
        cur = liste;
        liste = liste->suivant;
        free(cur);
    }
}
