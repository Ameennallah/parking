#include <stdio.h>
#include <stdlib.h>
#include "project.h"

#define ROWS 8
#define COLS 3



int main() {
int choix, ligne, colonne;
Reservation reservation;

do {
printf("\nMenu:\n");
printf("1. Afficher les places\n");
printf("2. Sélectionner une place\n");
printf("3. Ajouter une réservation\n");
printf("4. Modifier une réservation\n");
printf("5. Supprimer une réservation\n");
printf("6. Quitter\n");
printf("Choisissez une option: ");
scanf("%d", &choix);

switch (choix) {
    case 1:
        afficher_places();
        break;
    case 2:
        printf("Entrer la ligne et la colonne (1-8 pour ligne et 1-3 pour colonne) : ");
        scanf("%d %d", &ligne, &colonne);
        if (ligne >= 1 && ligne <= ROWS && colonne >= 1 && colonne <= COLS) {
            selectionner_place(ligne - 1, colonne - 1);
        }
        else {
            printf("Coordonnées invalides.\n");
        }
        break;
    case 3:
        printf("Entrez l'ID du parking: ");
        scanf("%d", &reservation.ID_Parking);
        printf("Entrez le nom du parking: ");
        scanf("%s", reservation.nom_parking);
        printf("Entrez votre nom: ");
        scanf("%s", reservation.nom);
        printf("Entrez votre prénom: ");
        scanf("%s", reservation.prenom);
        printf("Entrez votre numéro: ");
        scanf("%d", &reservation.numero);
        printf("Entrez votre CIN: ");
        scanf("%d", &reservation.CIN);
        printf("Entrez votre immatricule: ");
        scanf("%d", &reservation.immatricule);
        printf("Entrez la date d'arrivee (jour mois annee heure): ");
        scanf("%d %d %d %d", &reservation.arr_jour, &reservation.arr_mois,&reservation.arr_annee, &reservation.arr_heure);
        printf("Entrez la date de depart (jour mois annee heure): ");
        scanf("%d %d %d %d", &reservation.dep_jour, &reservation.dep_mois,&reservation.dep_annee, &reservation.dep_heure);

        ajouterReservation(reservation);
        break;

    case 4:
        printf("Entrez l'ID du parking à modifier: ");
        scanf("%d", &reservation.ID_Parking);
        printf("Entrez le nouveau nom du parking: ");
        scanf("%s", reservation.nom_parking);
        printf("Entrez votre nouveau nom: ");
        scanf("%s", reservation.nom);
        printf("Entrez votre nouveau prénom: ");
        scanf("%s", reservation.prenom);
        printf("Entrez votre nouveau numéro: ");
        scanf("%d", &reservation.numero);
        printf("Entrez votre nouveau CIN: ");
        scanf("%d", &reservation.CIN);
        printf("Entrez votre nouveau immatricule: ");
        scanf("%d", &reservation.immatricule);
        printf("Entrez la nouvelle date d'arrivée (jour mois annee heure): ");
       scanf("%d %d %d %d", &reservation.arr_jour, &reservation.arr_mois,&reservation.arr_annee ,&reservation.arr_heure);
        printf("Entrez la nouvelle date de départ (jour mois heure): ");
        scanf("%d %d %d %d", &reservation.dep_jour, &reservation.dep_mois,&reservation.dep_annee ,&reservation.dep_heure);

        modifierReservation(reservation.ID_Parking, reservation);
        break;

    case 5:
        printf("Entrez l'ID du parking à supprimer: ");
        scanf("%d", &reservation.ID_Parking);
        supprimerReservation(reservation.ID_Parking);
        break;
    case 6:
        printf("Au revoir!\n");
        break;

    default:
        printf("Choix invalide. Veuillez réessayer.\n");
        
}

} while (choix != 7);

return 0;
}

