#pragma once


typedef struct
{
    char* name;
    double concentration;
    int quantity;
    double price;
} Medication;

Medication* createMedication(char* name, double concentration, int quantity, double price);
Medication* copyMedication(Medication* m);
void destroyMedication(Medication* m); // the memory is freed

char* getName(Medication* m);
double getConcentration(Medication* m);
int getQuantity(Medication* m);
double getPrice(Medication* m);

void toString(Medication* m, char str[]);
