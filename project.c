
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"
#define ROWS 8
#define COLS 3

int reservations[ROWS][COLS] = {0};

void afficher_places() {
    printf("Places disponibles :\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("Ligne %d Colonne %d: %s\n", i + 1, j + 1, reservations[i][j] ? "Réservée" : "Disponible");
        }
    }
}


void selectionner_place(int row, int col) {
    if (reservations[row][col] == 0) {
        reservations[row][col] = 1;
        printf("Place sélectionnée avec succès.\n");
    }
    else {
        printf("Cette place est déjà réservée.\n");
    }
}

void ajouterReservation(Reservation reservation) {
    FILE *file = fopen("reservations.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d, %s, %s, %s, %d, %d, %d, %d/%d/%d/%d, %d/%d/%d/%d , %f\n",
        reservation.ID_Parking,
        reservation.nom_parking,
        reservation.nom,
        reservation.prenom,
        reservation.numero,
        reservation.CIN,
        reservation.immatricule,
        reservation.arr_jour, reservation.arr_mois,reservation.arr_annee, reservation.arr_heure,
        reservation.dep_jour, reservation.dep_mois,reservation.dep_annee, reservation.dep_heure,
	reservation.prix);
        fclose(file);
    }
    else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}
void modifierReservation(int CIN, Reservation nouvelleReservation) {
    char filename[100];
    sprintf(filename, "reservations_%d.txt", CIN);

    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    Reservation reservation;
    int found = 0;

    if (file == NULL || tempFile == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    while (fscanf(file, "%d, %49[^,], %49[^,], %49[^,], %d, %d, %d, %d/%d/%d/%d, %d/%d/%d/%d, %f\n",
                  &reservation.ID_Parking,
                  reservation.nom_parking,
                  reservation.nom,
                  reservation.prenom,
                  &reservation.numero,
                  &reservation.CIN,
                  &reservation.immatricule,
                  &reservation.arr_jour, &reservation.arr_mois, &reservation.arr_annee, &reservation.arr_heure,
                  &reservation.dep_jour, &reservation.dep_mois, &reservation.dep_annee, &reservation.dep_heure,
			&reservation.prix) == EOF) {

        if (reservation.ID_Parking == nouvelleReservation.ID_Parking) {
            fprintf(tempFile, "%d, %s, %s, %s, %d, %d, %d, %d/%d/%d/%d, %d/%d/%d/%d ,%f\n",
                    nouvelleReservation.ID_Parking,
                    nouvelleReservation.nom_parking,
                    nouvelleReservation.nom,
                    nouvelleReservation.prenom,
                    nouvelleReservation.numero,
                    nouvelleReservation.CIN,
                    nouvelleReservation.immatricule,
                    nouvelleReservation.arr_jour, nouvelleReservation.arr_mois, nouvelleReservation.arr_annee, nouvelleReservation.arr_heure,
                    nouvelleReservation.dep_jour, nouvelleReservation.dep_mois, nouvelleReservation.dep_annee, nouvelleReservation.dep_heure,
			nouvelleReservation.prix);
            found = 1;
        } else {
            fprintf(tempFile, "%d, %s, %s, %s, %d, %d, %d, %d/%d/%d/%d, %d/%d/%d/%d , %f \n",
                    reservation.ID_Parking,
                    reservation.nom_parking,
                    reservation.nom,
                    reservation.prenom,
                    reservation.numero,
                    reservation.CIN,
                    reservation.immatricule,
                    reservation.arr_jour, reservation.arr_mois, reservation.arr_annee, reservation.arr_heure,
                    reservation.dep_jour, reservation.dep_mois, reservation.dep_annee, reservation.dep_heure,
			reservation.prix);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.txt", filename);

    if (found) {
        printf("Réservation modifiée avec succès pour CIN %d.\n", CIN);
    } else {
        printf("Réservation non trouvée pour CIN %d.\n", CIN);
    }
}

   


void supprimerReservation(int ID_Parking) {
    FILE *file = fopen("reservations.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    Reservation reservation;
    int found = 0;

    if (file == NULL || tempFile == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    return;
}

// Parcours du fichier pour copier les réservations sauf celle à supprimer
while (fscanf(file, "%d, %49[^,], %49[^,], %49[^,], %d, %d, %d, %d/%d/%d/%d, %d/%d/%d/%d , %f \n",
    &reservation.ID_Parking,
    reservation.nom_parking,
    reservation.nom,
    reservation.prenom,
    &reservation.numero,
    &reservation.CIN,
    &reservation.immatricule,
    &reservation.arr_jour, &reservation.arr_mois,&reservation.arr_annee, &reservation.arr_heure,
    &reservation.dep_jour, &reservation.dep_mois,&reservation.dep_annee, &reservation.dep_heure, 
	&reservation.prix) == EOF) {

// Vérification si l'ID correspond
if (reservation.ID_Parking == ID_Parking) {
    // On ignore cette réservation pour la "supprimer"
    found = 1;
}
else {
    // On copie la réservation non supprimée dans le fichier temporaire
    fprintf(tempFile, "%d, %s, %s, %s, %d, %d, %d, %d/%d/%d/%d, %d/%d/%d/%d, %f\n",
    reservation.ID_Parking,
    reservation.nom_parking,
    reservation.nom,
    reservation.prenom,
    reservation.numero,
    reservation.CIN,
    reservation.immatricule,
    reservation.arr_jour, reservation.arr_mois,reservation.arr_annee ,reservation.arr_heure,
    reservation.dep_jour, reservation.dep_mois,reservation.dep_annee, reservation.dep_heure,
	reservation.prix);
    }
}

fclose(file);
fclose(tempFile);

// Remplacement de l'ancien fichier par le fichier temporaire
remove("reservations.txt");
rename("temp.txt", "reservations.txt");

if (found) {
printf("Réservation supprimée avec succès.\n");
} else {
printf("Réservation non trouvée.\n");
}
}

