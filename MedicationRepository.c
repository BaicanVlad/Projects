#include "MedicationRepository.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

MedicationRepo* createRepo()
{
    MedicationRepo* v = (MedicationRepo*)malloc(sizeof(MedicationRepo));
	v->medications = createDynamicArray(CAPACITY);

    return v;
}


void deleteRepo(MedicationRepo* v)
{
	if (v == NULL)
		return;

	// first free the memory allocated for the planets
	for (int i = 0; i < getLength(v->medications); i++)
	{
		Medication* m = get(v->medications, i);
		destroyMedication(m);
	}

	// then destroy the dynamic array
	destroy(v->medications);
	free(v);
}

int findPosOfMedication(MedicationRepo * v, char* name, double concentration)
{
	if (v == NULL)
		return -1;

	for (int i = 0; i < getLength(v->medications); i++)
	{
		Medication* m = get(v->medications, i);
		if (strcmp(m->name, name) == 0 && m->concentration == concentration)
			return i;
	}
	return -1;
}

Medication* find(MedicationRepo* v, char* name, double concentration)
{
    int i;
    for (i = 0; i < getLength(v->medications); i++)
    {
		Medication* m = getMedOnPos(v, i);
		if (strcmp(m->name, name) == 0 && m->concentration == concentration)
			return m;
    }
    return NULL;
}

int addMedication(MedicationRepo* v, Medication* m)
{
    // first search for a medication with the same name and concentration
    Medication* m2 = find(v, m->name, m->concentration);

    if (m2!= NULL)
    {

        m2->quantity += m->quantity;
        return 2;
    }

	// a copy of the medication which was passed will be stored, such that the memory for the medication can be deallocated where it was allocated (in Controller) 
	// and the Repository will handle its own memory
	Medication* copy = copyMedication(m);
	add(v->medications, copy);


	return 1;

}

void deleteMedication(MedicationRepo* v, int pos)
{
	delete(v->medications, pos);
}



int getRepoLength(MedicationRepo* v)
{
	return getLength(v->medications);
}

Medication* getMedOnPos(MedicationRepo* v, int pos)
{
	if (v == NULL)
		return NULL;

    if (pos < 0 || pos >= getLength(v->medications))
        return NULL;
	return get(v->medications, pos);
}

void setMedOnPos(MedicationRepo* v, Medication* elem , int pos)
{
	set(v->medications, elem, pos);
}

void sortByName(MedicationRepo* v)
{
    int i, j;
	int length = getRepoLength(v);
    Medication* a;
	Medication* b;

    for (i = (length - 1); i > 0; i--)
    {
        for (j = 1; j <= i; j++)
        {
			a = getMedOnPos(v, j);
			b = getMedOnPos(v, j-1);

            if (!cmpWords(a->name,b->name))
            {
				setMedOnPos(v, a, j - 1);
				setMedOnPos(v, b, j);
            }
        }
    }

}

void sortByPrice(MedicationRepo* v)
{
    int i, j;
    int length = getRepoLength(v);
    Medication *a,*b;

    for (i = (length-1); i > 0; i--)
    {
        for (j = 1; j <= i; j++)
        {
			a = getMedOnPos(v, j);
			b = getMedOnPos(v, j - 1);

            if (a->price > b->price)
            {
				setMedOnPos(v, a, j - 1);
				setMedOnPos(v, b, j);
            }
        }
    }
}
void sortByConcentration(MedicationRepo* v)
{
	int i, j;
	int length = getRepoLength(v);
	Medication *a, *b;

	for (i = (length - 1); i > 0; i--)
	{
		for (j = 1; j <= i; j++)
		{
			a = getMedOnPos(v, j);
			b = getMedOnPos(v, j - 1);
			
			if (a->concentration > b->concentration)
			{
				setMedOnPos(v, a, j - 1);
				setMedOnPos(v, b, j);
			}
		}
	}

}


int cmpWords(char* a, char* b)
{
    // compares two words in alphabetical means

    int i=0;
    while(a[i]==b[i])
        i++;
    return a[i]>b[i];
}
/*
// Tests
void initMedicationRepoForTests(MedicationRepo* v)
{
	Medication* m = createMedication("Med1",0.75,10,100.00);
	add(v, m);
}

void testAdd()
{
	MedicationRepo* v = createRepo();
	initMedicationRepoForTests(v);
	assert(getLength(v) == 1);

	Medication* m = createMedication("Med2",0.32,20,75.00);
	assert(addMedication(v, m) == 1);
	assert(getLength(v) == 2);

	// now try to add the same medication again -> add must return 0
	assert(addMedication(v, m) == 0);

	// destroy the test repository
	deleteRepo(v);
}

void testDelete()
{
    MedicationRepo* v = createRepo();
	initMedicationRepoForTests(v);

	assert(del(v, "Med1", 0.75) == 1);
	assert(getLength(v) == 0);

	assert(del(v, "Med1", 0.75) == 0);
}

void testGetMedOnPos()
{
    MedicationRepo* v = createRepo();
	initMedicationRepoForTests(v);

	assert(getMedOnPos(v,10) == NULL);

	assert(getMedOnPos(v,0) != NULL);
}

void testsMedicationRepo()
{
    testAdd();
    testDelete();
    testGetMedOnPos();
}
*/