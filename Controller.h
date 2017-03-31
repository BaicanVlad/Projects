#pragma once
#include "MedicationRepository.h"
#include "OperationsStack.h"

typedef struct
{
    MedicationRepo* repo;
	OperationsStack* undoStack;
	OperationsStack* redoStack;
} Controller;

//creates a controller
Controller* createController(MedicationRepo* r, OperationsStack*, OperationsStack*);

//delete a controller
//the memory is freed
void destroyController(Controller* c);

//calls the add function from the repository with the given information
int addMedicationCTRL(Controller* c, char* name, double concentration, int quantity, double price);

//calls the add function from the repository with the given information
int delMedication(Controller* c, char* name, double concentration);

int updateMedicationCTRL(Controller* c, char* name, double concentration, int quantity, double price);


//return the attached repository
MedicationRepo* getRepo(Controller* c);

MedicationRepo* findMedicationByString(Controller* c, char name[], char* type);
MedicationRepo* findMedicationByName(Controller* c, char name[]);
MedicationRepo* findMedicationByLowSupply(Controller* c, int quantity);

/// <summary>
/// Undoes the last performed operation.
/// </summary>
/// <param name="c">Pointer to the controller.</param>
/// <returns>1, if the undo operation could be done, 0 otherwise.</returns>
int undo(Controller*);

/// <summary>
/// Redoes the last performed operation.
/// </summary>
/// <param name="c">Pointer to the controller.</param>
/// <returns>1, if the redo operation could be done, 0 otherwise.</returns>
int redo(Controller*);
