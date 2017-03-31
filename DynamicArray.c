#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
	// make sure that the space was allocated
	if (da == NULL)
		return NULL;

	da->capacity = capacity;
	da->length = 0;

	// allocate space for the elements
	da->elems = (TElement*)malloc(capacity * sizeof(TElement));
	if (da->elems == NULL)
		return NULL;

	return da;
}

void destroy(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	// free the space allocated for the elements
	free(arr->elems);
	arr->elems = NULL;

	// free the space allocated for the dynamic array
	free(arr);
	arr = NULL;
}

// Resizes the array, allocating more space.
void resize(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	arr->capacity *= 2;
	arr->elems = (TElement*)realloc(arr->elems, arr->capacity * sizeof(TElement));
}

void add(DynamicArray* arr, TElement t)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;

	// resize the array, if necessary
	if (arr->length == arr->capacity)
		resize(arr);
	arr->elems[arr->length++] = t;
}

void delete(DynamicArray* arr, int pos)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;

	for (int i = pos; i < arr->length - 1; i++)
		arr->elems[i] = arr->elems[i + 1];

	arr->length--;
}

int getLength(DynamicArray* arr)
{
	if (arr == NULL)
		return -1;

	return arr->length;
}

TElement get(DynamicArray* arr, int pos)
{
	return arr->elems[pos];
}

void set(DynamicArray * arr,TElement elem ,int pos)
{
	arr->elems[pos] = elem;
}

// ------------------------------------------------------------------------------------------------------------
// Tests
/*
void testsDynamicArray()
{
	DynamicArray* da = createDynamicArray(2);
	if (da == NULL)
		assert(0);

	assert(da->capacity == 2);
	assert(da->length == 0);

	Medication* m1 = createMedication("Med1", 0.50, 100, 100.00);
	add(da, m1);
	assert(da->length == 1);

	Medication* m2 = createMedication("Med2", 0.50, 100, 100.00);
	add(da, m2);
	assert(da->length == 2);

	// capacity must double
	Medication* m3 = createMedication("Med3", 0.50, 100, 100.00);
	add(da, m3);
	assert(da->length == 3);
	assert(da->capacity == 4);

	// delete planet on position 0
	delete(da, 0);
	Medication* m = get(da, 0);
	assert(strcmp(getName(m), "Med2") == 0);
	assert(da->length == 2);

	// destroy the dynamic array
	destroy(da);

	// destroy the planets
	destroyPlanet(m1);
	destroyPlanet(m2);
	destroyPlanet(m3);
}
*/