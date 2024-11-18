#ifndef RESERVE_H_INCLUDE
#define RESERVE_H_INCLUDE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
int ID_Parking;
char nom_parking[50];
char nom[50];
char prenom[50];
int numero;
int CIN;
int immatricule;
int arr_jour;
int arr_mois;
int arr_annee;
int arr_heure;
int dep_jour;
int dep_mois;
int dep_annee;
int dep_heure;
float prix;
} Reservation;



void afficher_places();

void selectionner_place(int row, int col);

void ajouterReservation(Reservation reservation);

void modifierReservation(int CIN, Reservation nouvelleReservation);

void supprimerReservation(int ID_Parking);




#endif


