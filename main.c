#include"Ui.h"
#include<crtdbg.h>
#include<stdlib.h>

int main()
{
    MedicationRepo* repo = createRepo();

	OperationsStack* operationsStack = createStack();
	OperationsStack* operationsStack2 = createStack();

    Controller* ctrl = createController(repo, operationsStack, operationsStack2);

	addMedicationCTRL(ctrl, "Cardizem", 0.25, 10, 10.25);
	addMedicationCTRL(ctrl, "Zovirax", 0.15, 5, 15.55);
	//addMedicationCTRL(ctrl, "Lamictal", 0.35, 15, 2.00);
    addMedicationCTRL(ctrl, "Aspirin", 0.15, 100, 5.50);
    addMedicationCTRL(ctrl, "Imodium", 0.35, 54, 8.00);
    //addMedicationCTRL(ctrl, "Symbicort", 0.05, 29, 27.50);
    addMedicationCTRL(ctrl, "Augmentin", 0.27, 31, 9.99);
    addMedicationCTRL(ctrl, "Claritin", 0.72, 15, 10.25);

    addMedicationCTRL(ctrl, "Morphine", 0.35, 18, 1499.00);
    //addMedicationCTRL(ctrl, "Morphine", 0.55, 7, 2000.00);
    //addMedicationCTRL(ctrl, "Morphine", 0.45, 777, 1700.00);
    addMedicationCTRL(ctrl, "Morphine", 0.59, 77, 1577.00);

    Ui* ui = createUi(ctrl);

	startUi(ui);

	destroyUi(ui);

	_CrtDumpMemoryLeaks();

    return 0;
}
