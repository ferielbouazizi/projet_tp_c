#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Depense {
    int code;
    char type[20];
    float montant;
    char description[51];
    int jour, mois, annee;
    struct Depense* suivant;
};

struct Revenu {
    int code;
    char source[20];
    float montant;
    char description[51];
    int jour, mois, annee;
    struct Revenu* suivant;
};

int confirmer_action();
struct Depense* ajouter_depense(struct Depense* tete, int code);
struct Depense* modifier_depense(struct Depense* tete, int code);
struct Depense* supprimer_depense(struct Depense* tete, int code);
struct Depense* vider_depenses(struct Depense* tete);
void afficher_depenses(struct Depense* tete);
float somme_depenses(struct Depense* tete, int mois, int annee);

struct Revenu* ajouter_revenu(struct Revenu* tete, int code);
struct Revenu* modifier_revenu(struct Revenu* tete, int code);
struct Revenu* supprimer_revenu(struct Revenu* tete, int code);
struct Revenu* vider_revenus(struct Revenu* tete);
void afficher_revenus(struct Revenu* tete);
float somme_revenus(struct Revenu* tete, int mois, int annee);

int main() {
    struct Depense* depenses = NULL;
    struct Revenu* revenus = NULL;
    int choix, code_dep = 1, code_rev = 1, code, mois, annee;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Ajouter depense\n2. Ajouter revenu\n3. Afficher depenses\n4. Afficher revenus\n");
        printf("5. Supprimer depense\n6. Supprimer revenu\n7. Modifier depense\n8. Vider depenses\n");
        printf("9. Modifier revenu\n10. Vider revenus\n11. Somme depenses/revenus (mois/annee)\n0. Quitter\nVotre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                depenses = ajouter_depense(depenses, code_dep++); break;
            case 2:
                revenus = ajouter_revenu(revenus, code_rev++); break;
            case 3:
                afficher_depenses(depenses); break;
            case 4:
                afficher_revenus(revenus); break;
            case 5:
                printf("Code a supprimer : "); scanf("%d", &code);
                depenses = supprimer_depense(depenses, code); break;
            case 6:
                printf("Code a supprimer : "); scanf("%d", &code);
                revenus = supprimer_revenu(revenus, code); break;
            case 7:
                printf("Code a modifier : "); scanf("%d", &code);
                depenses = modifier_depense(depenses, code); break;
            case 8:
                depenses = vider_depenses(depenses); break;
            case 9:
                printf("Code a modifier : "); scanf("%d", &code);
                revenus = modifier_revenu(revenus, code); break;
            case 10:
                revenus = vider_revenus(revenus); break;
            case 11:
                printf("Entrez mois (0 pour tout) et annee : ");
                scanf("%d %d", &mois, &annee);
                printf("Somme depenses : %.2f\n", somme_depenses(depenses, mois, annee));
                printf("Somme revenus  : %.2f\n", somme_revenus(revenus, mois, annee));
                printf("Balance        : %.2f\n", somme_revenus(revenus, mois, annee) - somme_depenses(depenses, mois, annee));
                break;
            case 0:
                printf("Fin du programme.\n"); break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;  
}

int confirmer_action() {
    char rep;
    printf("Confirmez-vous l'action ? (o/n) : ");
    while (getchar() != '\n'); 
    scanf("%c", &rep);
    return (rep == 'o' || rep == 'O');
}

struct Depense* ajouter_depense(struct Depense* tete, int code) {
    struct Depense* nouvelle = (struct Depense*)malloc(sizeof(struct Depense));
    if (!nouvelle) return tete;

    nouvelle->code = code;
    printf("Type (Transport, Alimentation, Divertissement, Autres) : ");
    scanf("%s", nouvelle->type);
    do {
        printf("Montant : ");
        scanf("%f", &nouvelle->montant);
    } while (nouvelle->montant < 0);

    printf("Description : ");
    getchar();
    fgets(nouvelle->description, 51, stdin);
    nouvelle->description[strcspn(nouvelle->description, "\n")] = '\0';
    printf("Date (jour mois annee) : ");
    scanf("%d %d %d", &nouvelle->jour, &nouvelle->mois, &nouvelle->annee);

    nouvelle->suivant = tete;
    return nouvelle;
}

struct Depense* modifier_depense(struct Depense* tete, int code) {
    struct Depense* courant = tete;
    while (courant) {
        if (courant->code == code) {
            printf("Modification de la depense %d\n", code);
            printf("Nouveau type : ");
            scanf("%s", courant->type);
            do {
                printf("Nouveau montant : ");
                scanf("%f", &courant->montant);
            } while (courant->montant < 0);
            printf("Nouvelle description : ");
            getchar();
            fgets(courant->description, 51, stdin);
            courant->description[strcspn(courant->description, "\n")] = '\0';
            printf("Nouvelle date : ");
            scanf("%d %d %d", &courant->jour, &courant->mois, &courant->annee);
            return tete;
        }
        courant = courant->suivant;
    }
    printf("Depense non trouvee.\n");
    return tete;
}

struct Depense* supprimer_depense(struct Depense* tete, int code) {
    struct Depense *actuel = tete, *precedent = NULL;
    while (actuel) {
        if (actuel->code == code) {
            if (precedent) precedent->suivant = actuel->suivant;
            else tete = actuel->suivant;
            free(actuel);
            printf("Depense supprimee.\n");
            return tete;
        }
        precedent = actuel;
        actuel = actuel->suivant;
    }
    printf("Depense non trouvee.\n");
    return tete;
}

struct Depense* vider_depenses(struct Depense* tete) {
    if (!confirmer_action()) return tete;
    struct Depense* tmp;
    while (tete) {
        tmp = tete;
        tete = tete->suivant;
        free(tmp);
    }
    printf("Toutes les depenses ont ete supprimees.\n");
    return NULL;
}

void afficher_depenses(struct Depense* tete) {
    if (tete == NULL) {
        printf("Aucune depense a afficher.\n");
        return;
    }
    while (tete) {
        printf("Code: %d | Type: %s | Montant: %.2f | Date: %02d/%02d/%d | Description: %s\n",
               tete->code, tete->type, tete->montant,
               tete->jour, tete->mois, tete->annee,
               tete->description);
        tete = tete->suivant;
    }
}

float somme_depenses(struct Depense* tete, int mois, int annee) {
    float somme = 0;
    while (tete) {
        if ((mois == 0 || tete->mois == mois) && (annee == 0 || tete->annee == annee))
            somme += tete->montant;
        tete = tete->suivant;
    }
    return somme;
}

struct Revenu* ajouter_revenu(struct Revenu* tete, int code) {
    struct Revenu* nouveau = (struct Revenu*)malloc(sizeof(struct Revenu));
    if (!nouveau) return tete;

    nouveau->code = code;
    printf("Source (Salaire, Pret, Autres) : ");
    scanf("%s", nouveau->source);
    do {
        printf("Montant : ");
        scanf("%f", &nouveau->montant);
    } while (nouveau->montant < 0);
    printf("Description : ");
    getchar();
    fgets(nouveau->description, 51, stdin);
    nouveau->description[strcspn(nouveau->description, "\n")] = '\0';
    printf("Date (jour mois annee) : ");
    scanf("%d %d %d", &nouveau->jour, &nouveau->mois, &nouveau->annee);

    nouveau->suivant = tete;
    return nouveau;
}

struct Revenu* modifier_revenu(struct Revenu* tete, int code) {
    struct Revenu* courant = tete;
    while (courant) {
        if (courant->code == code) {
            printf("Modification du revenu %d\n", code);
            printf("Nouvelle source : ");
            scanf("%s", courant->source);
            do {
                printf("Nouveau montant : ");
                scanf("%f", &courant->montant);
            } while (courant->montant < 0);
            printf("Nouvelle description : ");
            getchar();
            fgets(courant->description, 51, stdin);
            courant->description[strcspn(courant->description, "\n")] = '\0';
            printf("Nouvelle date : ");
            scanf("%d %d %d", &courant->jour, &courant->mois, &courant->annee);
            return tete;
        }
        courant = courant->suivant;
    }
    printf("Revenu non trouve.\n");
    return tete;
}

struct Revenu* supprimer_revenu(struct Revenu* tete, int code) {
    struct Revenu *actuel = tete, *precedent = NULL;
    while (actuel) {
        if (actuel->code == code) {
            if (precedent) precedent->suivant = actuel->suivant;
            else tete = actuel->suivant;
            free(actuel);
            printf("Revenu supprime.\n");
            return tete;
        }
        precedent = actuel;
        actuel = actuel->suivant;
    }
    printf("Revenu non trouve.\n");
    return tete;
}

struct Revenu* vider_revenus(struct Revenu* tete) {
    if (!confirmer_action()) return tete;
    struct Revenu* tmp;
    while (tete) {
        tmp = tete;
        tete = tete->suivant;
        free(tmp);
    }
    printf("Tous les revenus ont ete supprimes.\n");
    return NULL;
}

void afficher_revenus(struct Revenu* tete) {
    if (tete == NULL) {
        printf("Aucun revenu a afficher.\n");
        return;
    }
    while (tete) {
        printf("Code: %d | Source: %s | Montant: %.2f | Date: %02d/%02d/%d | Description: %s\n",
               tete->code, tete->source, tete->montant,
               tete->jour, tete->mois, tete->annee,
               tete->description);
        tete = tete->suivant;
    }
}

float somme_revenus(struct Revenu* tete, int mois, int annee) {
    float somme = 0;
    while (tete) {
        if ((mois == 0 || tete->mois == mois) && (annee == 0 || tete->annee == annee))
            somme += tete->montant;
        tete = tete->suivant;
    }
    return somme;
}
