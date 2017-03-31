#include "Medication.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Medication* createMedication(char* name, double concentration, int quantity, double price)
{
	Medication* m = (Medication*)malloc(sizeof(Medication));

	m->name = (char*)malloc(strlen(name) + 1);
	strcpy(m->name, name);

	m->concentration = concentration;

	m->quantity = quantity;

	m->price = price;

	return m;
}

Medication* copyMedication(Medication* m)
{
	if (m == NULL)
		return NULL;

	Medication* newMedication = createMedication(getName(m),getConcentration(m) ,getQuantity(m), getPrice(m));
	return newMedication;
}

void destroyMedication(Medication* m)
{
	// free the memory which was allocated for the component fields
	free(m->name);

	// free the memory which was allocated for the planet structure
	free(m);
}

char* getName(Medication* m)
{
	return m->name;
}

double getConcentration(Medication* m)
{
	return m->concentration;
}

int getQuantity(Medication* m)
{
	return m->quantity;
}

double getPrice(Medication* m)
{
	return m->price;
}

void toString(Medication* m, char str[])
{
	sprintf(str, "Name: %s \nConcentration: %.2f \nQuantity: %d \nPrice: %.2f \n", m->name, m->concentration, m->quantity, m->price);
}
