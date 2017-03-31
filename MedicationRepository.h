#pragma once
#include "Medication.h"
#include "DynamicArray.h"

typedef struct
{
	DynamicArray* medications;
} MedicationRepo;

//Creates a MedicationRepo.
MedicationRepo* createRepo();

//delete a given medication repository
//the memory is freed
void deleteRepo(MedicationRepo* v);

//find a medication with a given name and concentration
Medication* find(MedicationRepo* v, char* name, double concentration);

//adds a medication to the repository
int addMedication(MedicationRepo* v, Medication* m);

//deletes a medication from the repository
void deleteMedication(MedicationRepo* v, int pos);

//return the number of medications
int getRepoLength(MedicationRepo* v);

//finds a specific medication by a given position
Medication* getMedOnPos(MedicationRepo* v, int pos);


//sorts all the medications in a repository by their name
void sortByName(MedicationRepo* v);

//compare two words alphabetically
int cmpWords(char* a, char* b);

void sortByPrice(MedicationRepo* v);


/*
void testsMedicationRepo();
*/