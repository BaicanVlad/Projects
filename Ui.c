#include "Ui.h"
#include <stdio.h>
#include<stdlib.h>

Ui* createUi(Controller* c)
{
	Ui* ui = (Ui*)malloc(sizeof(Ui));
	ui->ctrl = c;

	return ui;
}

void destroyUi(Ui * ui)
{
	// first destroy the controller
	destroyController(ui->ctrl);
	// free the UI memory
	free(ui);
}

/*
	Prints the available menu for the problem
	Input: -
	Output: the menu is printed at the console
*/
void printMenu()
{
	printf("\nMenu:\n");
	printf("1  - Add a medication.\n");
	printf("2  - List all medications.\n");
	printf("3  - Delete a medication.\n");
	printf("4  - Update a medication.\n");
	printf("5  - Find all the available medications containing a given string.\n");
	printf("6  - For a given medication name, see all medications, sorted descending by price.\n");
	printf("7  - See the medications that are in short supply .\n");
	printf("8  - See all the available medications containing a given string.\n");
	printf("9  - Undo .\n");
	printf("10 - Redo .\n");
	printf("0  - to exit.\n\n");
}

/*
	Verifies if the given command is valid (is either 1, 2 or 0)
	Input: command - integer
	Output: 1 - if the command is valid
	0 - otherwise
*/
int validCommand(int command)
{
	if (command >= 0 && command <= 10)
		return 1;
	return 0;
}

/*
	Reads an integer number from the keyboard. Asks for number while read errors encountered.
	Input: the message to be displayed when asking the user for input.
	Returns the number.
*/
int readIntegerNumber(const char* message)
{
	char s[16];
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		scanf("%s", s);

		r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}

int addMedicationUi(Ui* ui)
{
	// read the planet's data
	char name[32];
	double concentration,price;
	int quantity;

	printf("Please input the name: ");
	scanf("%31s", name);

	printf("Please input the concentration: ");
	scanf("%lf", &concentration);

	quantity = readIntegerNumber("Please input the quantity: ");

	printf("Please input the price: ");
	scanf("%lf", &price);

	return addMedicationCTRL(ui->ctrl, name, concentration, quantity, price);
}

void listAllMedications(Ui* ui)
{
	MedicationRepo* repo = getRepo(ui->ctrl);
	int length = getRepoLength(repo);

	if (length == 0)
	{
		char* str = "There are no stored planets.";
		printf("%s \n", str);
	}
    int i;
	for (i = 0; i < length; i++)
	{

		char str[200];
		toString(getMedOnPos(repo, i), str);
		printf("%s\n", str);

	}
}
int deleteMedicationUi(Ui* ui)
{
    char name[32];
	double concentration;

	printf("Please input the name: ");
	scanf("%31s", name);

	printf("Please input the concentration: ");
	scanf("%lf", &concentration);

	return delMedication(ui->ctrl, name, concentration);
}

int updateMedicationUi(Ui* ui)
{
    char name[32];
	double concentration,price;
	int quantity;

	printf("Please input the name: ");
	scanf("%31s", name);

	printf("Please input the concentration: ");
	scanf("%lf", &concentration);

	quantity = readIntegerNumber("Please input the new quantity: ");

	printf("Please input the new price : ");
	scanf("%lf", &price);

	int res = updateMedicationCTRL(ui->ctrl ,name, concentration, quantity, price);

}

void listMedByGivenString(Ui*ui, char* type)
{
    char name[32];
    printf("Search for: ");
    scanf("%31s",name);

    MedicationRepo* res = findMedicationByString(ui->ctrl, name, type);

    int length = getRepoLength(res);
	if (length == 0)
	{
		printf("There are no medication containing the given string.");
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			char str[200];
			toString(getMedOnPos(res, i), str);
			printf("%s\n", str);
		}
	}

	// now we must destroy the repository that was created for this operation
	if (res != getRepo(ui->ctrl))
		deleteRepo(res);

}

void listMedByGivenName(Ui*ui)
{
    char name[32];
    printf("Search for: ");
    scanf("%31s",name);

    MedicationRepo* res = findMedicationByName(ui->ctrl, name);

    int length = getRepoLength(res);
	if (length == 0)
	{
		printf("There are no medication containing the given name.");
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			char str[200];
			toString(getMedOnPos(res, i), str);
			printf("%s\n", str);
		}
	}

	// now we must destroy the repository that was created for this operation
	if (res != getRepo(ui->ctrl))
		deleteRepo(res);

}

void listMedByShortSupply(Ui*ui)
{
	int quantity;
	printf("Search for: ");
	scanf("%d", &quantity);

	MedicationRepo* res = findMedicationByLowSupply(ui->ctrl, quantity);

	int length = getRepoLength(res);
	if (length == 0)
	{
		printf("There are no medication on low supply.");
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			char str[200];
			toString(getMedOnPos(res, i), str);
			printf("%s\n", str);
		}
	}

	// now we must destroy the repository that was created for this operation
	deleteRepo(res);

}

void startUi(Ui* ui)
{
	while (1)
	{
		printMenu();
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		if (command == 0)
			break;
		switch (command)
		{
		case 1:
		{
			int res = addMedicationUi(ui);
			if (res == 1)
			{
				freeStack(ui->ctrl->redoStack);
				printf("Medication successfully added.\n");
			}
			else if(res == 2)
            {
                printf("Medication already exists, so the quantity was updated.\n");
            }
            else
				printf("Error! Medication could not be added, as there is another medication with the same name and concentration!\n");
			break;
		}
		case 2:
		{
			listAllMedications(ui);
			break;
		}
		case 3:
        {
            int res = deleteMedicationUi(ui);

            if (res == -1)
                printf("The medication doesn't exist.");
			else
			{
				freeStack(ui->ctrl->redoStack);
				printf("Medication successfully deleted.");
			}
            break;
		}
		case 4:
        {
            int res = updateMedicationUi(ui);

            if (res == 0)
                printf("The medication doesn't exist.");
            else
                printf("Medication successfully updated.");
            break;
        }
		
        case 5:
        {
            listMedByGivenString(ui,"name");
            break;
        }
		
        case 6:
        {
            listMedByGivenName(ui);
            break;
        }
		case 7:
		{
			listMedByShortSupply(ui);
			break;
		}

		case 8:
		{
			listMedByGivenString(ui,"concentration");
			break;
		}

		case 9:
		{
			int res = undo(ui->ctrl);
			if (res == 1)
				printf("Undo was successful.\n");
			else
				printf("No more undos to be made.\n");
			break;
		}
		
		case 10:
		{
			int res = redo(ui->ctrl);
			if (res == 1)
				printf("Redo was successful.\n");
			else
				printf("No more redos to be made.\n");
			break;
		}
		
        }
	}
}

