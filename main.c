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

int confirmer_action() {
    char reponse;
    printf("Etes-vous sûr de vouloir continuer ? (o/n) : ");
    scanf(" %c", &reponse);
    return (reponse == 'o' || reponse == 'O');
}

int saisie_valide_jour() {
    int jour;
    do {
        printf("Entrez le jour de la depense (1-31) : ");
        scanf("%d", &jour);
        if (jour < 1 || jour > 31) {
            printf("Jour invalide. Veuillez entrer un jour entre 1 et 31.\n");
        }
    } while (jour < 1 || jour > 31);
    return jour;
}

int saisie_valide_mois() {
    int mois;
    do {
        printf("Entrez le mois de la depense (1-12) : ");
        scanf("%d", &mois);
        if (mois < 1 || mois > 12) {
            printf("Mois invalide. Veuillez entrer un mois entre 1 et 12.\n");
        }
    } while (mois < 1 || mois > 12);
    return mois;
}

struct Depense* ajouter_depense(struct Depense* tete, int code) {
    struct Depense* nouvelle = (struct Depense*)malloc(sizeof(struct Depense));
    int type_choice;

    printf("Choisissez le type de depense :\n");
    printf("1. Transport\n");
    printf("2. Alimentation\n");
    printf("3. Divertissement\n");
    printf("4. Autres\n");
    printf("Votre choix : ");
    scanf("%d", &type_choice);

    switch (type_choice) {
        case 1: strcpy(nouvelle->type, "Transport"); break;
        case 2: strcpy(nouvelle->type, "Alimentation"); break;
        case 3: strcpy(nouvelle->type, "Divertissement"); break;
        case 4: strcpy(nouvelle->type, "Autres"); break;
        default: strcpy(nouvelle->type, "Inconnu"); break;
    }

    printf("Entrez le montant de la depense : ");
    scanf("%f", &nouvelle->montant);
    printf("Entrez la description de la depense : ");
    scanf(" %[^\n]", nouvelle->description);

    nouvelle->jour = saisie_valide_jour();
    nouvelle->mois = saisie_valide_mois();

    printf("Entrez l'annee de la depense : ");
    scanf("%d", &nouvelle->annee);

    nouvelle->code = code;
    nouvelle->suivant = tete;
    return nouvelle;
}

struct Revenu* ajouter_revenu(struct Revenu* tete, int code) {
    struct Revenu* nouveau = (struct Revenu*)malloc(sizeof(struct Revenu));
    int source_choice;

    printf("Choisissez la source du revenu :\n");
    printf("1. Salaire\n");
    printf("2. Pret\n");
    printf("3. Autres\n");
    printf("Votre choix : ");
    scanf("%d", &source_choice);

    switch (source_choice) {
        case 1: strcpy(nouveau->source, "Salaire"); break;
        case 2: strcpy(nouveau->source, "Pret"); break;
        case 3: strcpy(nouveau->source, "Autres"); break;
        default: strcpy(nouveau->source, "Inconnu"); break;
    }

    printf("Entrez le montant du revenu : ");
    scanf("%f", &nouveau->montant);
    printf("Entrez la description du revenu : ");
    scanf(" %[^\n]", nouveau->description);

    nouveau->jour = saisie_valide_jour();
    nouveau->mois = saisie_valide_mois();

    printf("Entrez l'annee du revenu : ");
    scanf("%d", &nouveau->annee);

    nouveau->code = code;
    nouveau->suivant = tete;
    return nouveau;
}

void afficher_depenses(struct Depense* tete) {
    struct Depense* courant = tete;
    if (!courant) {
        printf("Aucune depense enregistrée.\n");
        return;
    }
    while (courant != NULL) {
        printf("Code: %d | Type: %s | Montant: %.2f | Description: %s | Date: %d/%d/%d\n",
               courant->code, courant->type, courant->montant, courant->description,
               courant->jour, courant->mois, courant->annee);
        courant = courant->suivant;
    }
}

void afficher_revenus(struct Revenu* tete) {
    struct Revenu* courant = tete;
    if (!courant) {
        printf("Aucun revenu enregistré.\n");
        return;
    }
    while (courant != NULL) {
        printf("Code: %d | Source: %s | Montant: %.2f | Description: %s | Date: %d/%d/%d\n",
               courant->code, courant->source, courant->montant, courant->description,
               courant->jour, courant->mois, courant->annee);
        courant = courant->suivant;
    }
}

struct Depense* supprimer_depense(struct Depense* tete, int code) {
    struct Depense* courant = tete;
    struct Depense* precedent = NULL;

    while (courant != NULL && courant->code != code) {
        precedent = courant;
        courant = courant->suivant;
    }
    if (courant == NULL) {
        printf("Depense non trouvée.\n");
        return tete;
    }
    if (precedent == NULL) {
        tete = courant->suivant;
    } else {
        precedent->suivant = courant->suivant;
    }
    free(courant);
    printf("Depense supprimée.\n");
    return tete;
}

struct Revenu* supprimer_revenu(struct Revenu* tete, int code) {
    struct Revenu* courant = tete;
    struct Revenu* precedent = NULL;

    while (courant != NULL && courant->code != code) {
        precedent = courant;
        courant = courant->suivant;
    }
    if (courant == NULL) {
        printf("Revenu non trouvé.\n");
        return tete;
    }
    if (precedent == NULL) {
        tete = courant->suivant;
    } else {
        precedent->suivant = courant->suivant;
    }
    free(courant);
    printf("Revenu supprimé.\n");
    return tete;
}

struct Depense* vider_depenses(struct Depense* tete) {
    struct Depense* courant = tete;
    while (courant != NULL) {
        struct Depense* temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    return NULL;
}

struct Revenu* vider_revenus(struct Revenu* tete) {
    struct Revenu* courant = tete;
    while (courant != NULL) {
        struct Revenu* temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    return NULL;
}

float somme_depenses(struct Depense* tete, int mois, int annee) {
    struct Depense* courant = tete;
    float somme = 0;
    while (courant != NULL) {
        if ((mois == 0 || courant->mois == mois) && (annee == 0 || courant->annee == annee)) {
            somme += courant->montant;
        }
        courant = courant->suivant;
    }
    return somme;
}

float somme_revenus(struct Revenu* tete, int mois, int annee) {
    struct Revenu* courant = tete;
    float somme = 0;
    while (courant != NULL) {
        if ((mois == 0 || courant->mois == mois) && (annee == 0 || courant->annee == annee)) {
            somme += courant->montant;
        }
        courant = courant->suivant;
    }
    return somme;
}

void stats_depenses(struct Depense* tete) {
    struct Depense* courant = tete;
    float total = 0;
    int count = 0;
    while (courant != NULL) {
        total += courant->montant;
        count++;
        courant = courant->suivant;
    }
    if (count > 0) {
        printf("Total des depenses: %.2f\n", total);
        courant = tete;
        while (courant != NULL) {
            printf("%s : %.2f (%.2f%%)\n", courant->type, courant->montant, (courant->montant / total) * 100);
            courant = courant->suivant;
        }
    } else {
        printf("Aucune depense.\n");
    }
}

void stats_revenus(struct Revenu* tete) {
    struct Revenu* courant = tete;
    float total = 0;
    int count = 0;
    while (courant != NULL) {
        total += courant->montant;
        count++;
        courant = courant->suivant;
    }
    if (count > 0) {
        printf("Total des revenus: %.2f\n", total);
        courant = tete;
        while (courant != NULL) {
            printf("%s : %.2f (%.2f%%)\n", courant->source, courant->montant, (courant->montant / total) * 100);
            courant = courant->suivant;
        }
    } else {
        printf("Aucun revenu.\n");
    }
}

int main() {
    struct Depense* depenses = NULL;
    struct Revenu* revenus = NULL;
    int choix, sous_choix, code_dep = 1, code_rev = 1, code, mois, annee;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Ajouter (1. Depense  2. Revenu)\n");
        printf("2. Afficher (1. Depenses  2. Revenus)\n");
        printf("3. Supprimer (1. Depense  2. Revenu)\n");
        printf("4. Modifier (1. Depense  2. Revenu)\n");
        printf("5. Initialiser (1. Depenses  2. Revenus)\n");
        printf("6. Somme depenses/revenus (mois/annee)\n");
        printf("7. Statistiques (1. Depenses  2. Revenus)\n");
        printf("0. Quitter\nVotre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Ajouter (1. Depense  2. Revenu) : ");
                scanf("%d", &sous_choix);
                if (sous_choix == 1) depenses = ajouter_depense(depenses, code_dep++);
                else if (sous_choix == 2) revenus = ajouter_revenu(revenus, code_rev++);
                break;
            case 2:
                printf("Afficher (1. Depenses  2. Revenus) : ");
                scanf("%d", &sous_choix);
                if (sous_choix == 1) afficher_depenses(depenses);
                else if (sous_choix == 2) afficher_revenus(revenus);
                break;
            case 3:
                printf("Supprimer (1. Depense  2. Revenu) : ");
                scanf("%d", &sous_choix);
                printf("Code a supprimer : ");
                scanf("%d", &code);
                if (sous_choix == 1) depenses = supprimer_depense(depenses, code);
                else if (sous_choix == 2) revenus = supprimer_revenu(revenus, code);
                break;
            case 4:
                printf("Modifier (1. Depense  2. Revenu) : ");
                scanf("%d", &sous_choix);
                printf("Code a modifier : ");
                scanf("%d", &code);
                // Modification functions need to be implemented
                break;
            case 5:
                printf("Initialiser (1. Depenses  2. Revenus) : ");
                scanf("%d", &sous_choix);
                if (sous_choix == 1) depenses = vider_depenses(depenses);
                else if (sous_choix == 2) revenus = vider_revenus(revenus);
                break;
            case 6:
                printf("Somme depenses/revenus pour mois (0 pour tous): ");
                scanf("%d", &mois);
                printf("Entrez l'annee: ");
                scanf("%d", &annee);
                printf("Total des depenses: %.2f\n", somme_depenses(depenses, mois, annee));
                printf("Total des revenus: %.2f\n", somme_revenus(revenus, mois, annee));
                break;
            case 7:
                printf("Statistiques (1. Depenses  2. Revenus) : ");
                scanf("%d", &sous_choix);
                if (sous_choix == 1) stats_depenses(depenses);
                else if (sous_choix == 2) stats_revenus(revenus);
                break;
            case 0:
                printf("Quitter le programme.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}
