#include "Controller.h"
#include <string.h>
#include <stdlib.h>

Controller* createController(MedicationRepo* r, OperationsStack* o, OperationsStack* o2)
{
	Controller* c = (Controller*)malloc(sizeof(Controller));
	c->repo = r;
	c->undoStack = o;
	c->redoStack = o2;

	return c;
}

void destroyController(Controller * c)
{
	// first destroy the repository inside
	deleteRepo(c->repo);

	// then the operation stack
	destroyStack(c->undoStack);

	// then free the memory
	free(c);
}

int addMedicationCTRL(Controller* c, char* name, double concentration, int quantity, double price)
{
	Medication* m = createMedication(name, concentration, quantity, price);

	int res = addMedication(c->repo, m);

	if (res == 1) // if the medication was successfully added - register the operation
	{
		Operation* o = createOperation(m, "add");
		push(c->undoStack, o);
		// once added, the operation can be destroyed (a copy of the operation was added)
		destroyOperation(o);

	}

	if (res == 2) 
	{
		Operation* o = createOperation(m, "addExisting");
		push(c->undoStack, o);

		destroyOperation(o);
	}

	// destroy the medication that was just created, as the repository stored a copy
	destroyMedication(m);
	

	return res;
}

int delMedication(Controller* c, char* name, double concentration)
{
	// find the position of the planet in the repository
	int pos = findPosOfMedication(c->repo, name, concentration);
	if (pos == -1)
		return -1;

	Medication* m = get(c->repo->medications, pos);

	Operation* o = createOperation(m, "remove");
	push(c->undoStack, o);
	// once added, the operation can be destroyed (a copy of the operation was added)
	destroyOperation(o);
	
	deleteMedication(c->repo, pos);

    return 0;
}

int updateMedicationCTRL(Controller* c, char* name, double concentration, int quantity, double price)
{
	Medication*m = find(c->repo, name, concentration);
	Medication*m2 = createMedication(name, concentration, quantity, price);

	if (m == NULL)
		return 0;
	else
	{

		Operation* o = createOperation(m, "update");
		push(c->undoStack, o);
		destroyOperation(o);

		deleteMedication(c->repo, findPosOfMedication(c->repo,name, concentration));
		add(c->repo->medications, m2);
	}
	return 1;
}

MedicationRepo* getRepo(Controller* c)
{
	return c->repo;
}

MedicationRepo* findMedicationByString(Controller* c, char name[], char* type)
{
    
    if (strcmp(name, "null") == 0)
	{
		if (strcmp(type, "name"))
			sortByName(c->repo);
		else
			sortByConcentration(c->repo);
		return c->repo;
	}

	MedicationRepo* res = createRepo();
    int i;

	for (i = 0; i < getRepoLength(c->repo); i++)
	{
		Medication* m= getMedOnPos(c->repo, i);
		if (strstr(m->name, name) != NULL)
		{
			Medication* newMed = createMedication(m->name,m->concentration,m->quantity,m->price);
			add(res->medications, newMed);
		}
	}
	
	if (strcmp(type, "name")==0)
		sortByName(res);
	else 
		sortByConcentration(res);
	
	return res;
}

MedicationRepo* findMedicationByName(Controller* c, char name[])
{
    MedicationRepo* res = createRepo();

    if (strcmp(name, "null") == 0)
	{
	    sortByName(c->repo);
		return c->repo;
	}
    int i;
	for (i = 0; i < getRepoLength(c->repo); i++)
	{
		Medication* m= getMedOnPos(c->repo, i);
		if (strcmp(m->name, name) == 0)
		{
			Medication* newMed = createMedication(m->name,m->concentration,m->quantity,m->price);
			addMedication(res, newMed);
		}
	}
    sortByPrice(res);



	return res;

}

MedicationRepo* findMedicationByLowSupply(Controller* c, int quantity)
{
	MedicationRepo* res = createRepo();

	int i;
	for (i = 0; i < getRepoLength(c->repo); i++)
	{
		Medication* m = getMedOnPos(c->repo, i);
		if (m->quantity < quantity)
		{
			Medication* newMed = createMedication(m->name, m->concentration, m->quantity, m->price);
			addMedication(res, newMed);
		}
	}
	return res;

}

int undo(Controller* c)
{
	if (isEmpty(c->undoStack))
	{
		return 0;
	}

	Operation* operation = pop(c->undoStack);

	if (strcmp(getOperationType(operation), "add") == 0)
	{
		Medication* m = getMedication(operation);
		
		deleteMedication(c->repo, getName(m), getConcentration(m));
	}
	else if (strcmp(getOperationType(operation), "addExisting") == 0)
	{
		Medication* m = getMedication(operation);
		
		Medication* m2 = find(c->repo, getName(m), getConcentration(m));

		m2->quantity -= m->quantity;

	}
	else if (strcmp(getOperationType(operation), "remove") == 0)
	{
		Medication* m = getMedication(operation);
		addMedication(c->repo, m);
	}
	else if (strcmp(getOperationType(operation), "update") == 0)
	{
		Medication* m = getMedication(operation);
		int pos = findPosOfMedication(c->repo, m->name, m->concentration);

		Medication* m2 = find(c->repo, m->name, m->concentration);
		Medication* copy = copyMedication(m2);
		operation->medication = copy;

		deleteMedication(c->repo,pos);
		addMedication(c->repo, m);


	}

	// the operation must be added on the redo stack
	push(c->redoStack, operation);

	// the operation must be destroyed
	destroyOperation(operation);


	return 1;

}
int redo(Controller* c)
{
	if (isEmpty(c->redoStack))
	{
		return 0;
	}

	Operation* operation = pop(c->redoStack);

	if (strcmp(getOperationType(operation), "add") == 0)
	{
		Medication* m = getMedication(operation);
		
		addMedication(c->repo, m);
	}
	else if (strcmp(getOperationType(operation), "addExisting") == 0)
	{
		Medication* m = getMedication(operation);
		

		Medication* m2 = find(c->repo, getName(m), getConcentration(m));

		m2->quantity += m->quantity;


	}
	else if (strcmp(getOperationType(operation), "remove") == 0)
	{
		Medication* m = getMedication(operation);
		deleteMedication(c->repo, getName(m), getConcentration(m));
	}

	else if (strcmp(getOperationType(operation), "update") == 0)
	{
		Medication* m = getMedication(operation);
		int pos = findPosOfMedication(c->repo, m->name, m->concentration);

		Medication* m2 = find(c->repo, m->name, m->concentration);
		Medication* copy = copyMedication(m2);
		operation->medication = copy;

		deleteMedication(c->repo, pos);
		addMedication(c->repo, m);
	}

	// the operation must be added on the redo stack
	push(c->undoStack, operation);

	// the operation must be destroyed
	destroyOperation(operation);

	return 1;

}