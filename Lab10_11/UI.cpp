#pragma once
#include "UI.h"
#include <iostream>
using namespace std;

void ConsoleUI::uiAdd()
{
	string numarInmatriculare, producator, model, tip;
	cout << "Numarul de inmatriculare este: ";
	getline(cin >> ws, numarInmatriculare);

	cout << "Producatorul este: ";
	getline(cin >> ws, producator);

	cout << "Modelul este: ";
	getline(cin >> ws, model);

	cout << "Tipul este: ";
	getline(cin >> ws, tip);
	try {
		service.addMasina(numarInmatriculare, producator, model, tip);
		cout << "Masina adaugata cu succes!\n";
	}
	catch (RepoException& mesaj)
	{
		cout << mesaj.getErrorMessage();
	}
	catch (ValidationException& mesaj)
	{
		cout << "Masina invalida!" << endl;
		cout << mesaj.getErrorMessages();
	}

}


void ConsoleUI::printMasini()
{
	try {
		vector<Masina> allMasini = service.getAllMasini();
		if (allMasini.size() == 0)
			cout << "Nu exista masini!\n";
		else
		{
			for (const auto& masina : allMasini)
				cout << "Numar de inmatriculare: " << masina.getNumarInmatriculare() << " | Producator: " << masina.getProducator() << " | Model: " << masina.getModel() << " | Tip: " << masina.getTip() << endl;
		}
	}
	catch (RepoException& mesaj)
	{
		cout << mesaj.getErrorMessage();
	}


}

void ConsoleUI::uiActualizare()
{
	string numarInmatriculare, producator, model, tip;
	cout << "Numarul de inmatriculare dupa care actualizam masina este: ";
	getline(cin >> ws, numarInmatriculare);

	cout << "Producator nou este: ";
	getline(cin >> ws, producator);

	cout << "Model nou este: ";
	getline(cin >> ws, model);

	cout << "Tip nou este: ";
	getline(cin >> ws, tip);
	try {
		service.actualizareMasina(numarInmatriculare, producator, model, tip);
		cout << "Masina actualizata cu succes!\n";
	}
	catch (RepoException& mesaj)
	{
		cout << mesaj.getErrorMessage();
	}
	catch (ValidationException& mesaj)
	{
		cout << mesaj.getErrorMessages();
	}

}

void ConsoleUI::uiSterge()
{
	string numarInmatriculare;
	cout << "Numarul de inmatriculare dupa care stergem o masina din lista este: ";
	getline(cin >> ws, numarInmatriculare);
	try {
		service.stergeMasina(numarInmatriculare);
		cout << "Masina stearsa cu succes!\n";
	}
	catch (RepoException& mesaj)
	{
		cout << mesaj.getErrorMessage();
	}
	catch (ValidationException& mesaj)
	{
		cout << mesaj.getErrorMessages();
	}

}

void ConsoleUI::uiSort()
{
	cout << "Criteriul de sortare este (numarInmatriculare/tip/producator+model): ";
	string criteriu;
	cin >> criteriu;
	if (criteriu == "numarInmatriculare")
	{
		vector<Masina> masini = service.sortByNumarInmatriculare();
		if (masini.size() == 0)
			cout << "Nu exista masini in lista!" << endl;
		else
		{
			cout << "Lista de masini sortate dupa nr de inmatriculare:" << endl;
			for (const auto& masina : masini)
			{
				cout << "Numar de inmatriculare: " << masina.getNumarInmatriculare() << " | Producator: " << masina.getProducator() << " | Model: " << masina.getModel() << " | Tip: " << masina.getTip() << endl;
			}
		}
	}
	else
	{
		if (criteriu == "tip")
		{
			vector<Masina> masini = service.sortByTip();
			if (masini.size() == 0)
				cout << "Nu exista masini in lista!" << endl;
			else
			{
				cout << "Lista de masini sortate dupa tip:" << endl;
				for (const auto& masina : masini)
				{
					cout << "Numar de inmatriculare: " << masina.getNumarInmatriculare() << " | Producator: " << masina.getProducator() << " | Model: " << masina.getModel() << " | Tip: " << masina.getTip() << endl;
				}
			}
		}
		else
		{
			if (criteriu == "producator+model")
			{
				vector<Masina> masini = service.sortByProducatorModel();
				if (masini.size() == 0)
					cout << "Nu exista masini in lista!" << endl;
				else
				{
					cout << "Lista de masini sortate dupa producator+model:" << endl;
					for (const auto& masina : masini)
					{
						cout << "Numar de inmatriculare: " << masina.getNumarInmatriculare() << " | Producator: " << masina.getProducator() << " | Model: " << masina.getModel() << " | Tip: " << masina.getTip() << endl;
					}
				}
			}
			else
				cout << "Nu se poate sorta dupa criteriul dat!" << endl;
		}
	}

}

void ConsoleUI::uiFilter()
{
	cout << "Criteriul de filtrare (producator/tip): ";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "producator")
	{
		cout << "Producatorul pentru care se afiseaza masinile este: ";
		string producator;
		cin >> producator;
		vector<Masina> masini = service.filtrareProducator(producator);
		if (masini.size() == 0)
			cout << "Nu exista masini in lista!" << endl;
		else
		{
			cout << "Lista de masini produse de: " << producator << endl;
			for (const auto& masina : masini)
			{
				cout << "Numar de inmatriculare: " << masina.getNumarInmatriculare() << " | Producator: " << masina.getProducator() << " | Model: " << masina.getModel() << " | Tip: " << masina.getTip() << endl;
			}
		}
	}
	else
		if (criteriu == "tip")
		{
			cout << "Tipul pentru care se afiseaza masinile este: ";
			string tip;
			cin >> tip;
			vector<Masina> masini = service.filtrareTip(tip);
			if (masini.size() == 0)
				cout << "Nu exista masini in lista!" << endl;
			else
			{
				cout << "Lista de masini de tipul: " << tip << endl;
				for (const auto& masina : masini)
				{
					cout << "Numar de inmatriculare: " << masina.getNumarInmatriculare() << " | Producator: " << masina.getProducator() << " | Model: " << masina.getModel() << " | Tip: " << masina.getTip() << endl;
				}
			}
		}
}


void ConsoleUI::uiAddSpalatorie()
{
	string numarInmatriculare, producator, model, tip;
	cout << "Numarul de inmatriculare este: ";
	getline(cin >> ws, numarInmatriculare);


	try {
		service.addMasinaToSpalatorie(numarInmatriculare);
		cout << "\nMasina s-a adaugat cu succes  la spalatorie!\n\n";
	}
	catch (RepoException& errorMessage) {
		cout << errorMessage.getErrorMessage();
	}
	catch (ValidationException& errorMessage) {
		cout << "Masina nu este valida!" << endl;
		cout << errorMessage.getErrorMessages();
	}
}

void ConsoleUI::uiAddRandomCarToSpalatorie()
{
	int numarDeMasiniDeGenerat;
	cout << "Introduce cate masini sa se adauge la spalatorie: ";
	cin >> numarDeMasiniDeGenerat;

	try {
		const size_t numarDeMasiniGenerate = service.addRandomMasiniToSpalatorie(numarDeMasiniDeGenerat);
		cout << "\nS-au adaugat " << numarDeMasiniGenerate << " masini in catalogul spalatoriei.\n\n";
	}
	catch (RepoException& errorMessage) {
		cout << errorMessage.getErrorMessage();
	}
}

void ConsoleUI::uiEmptySpalatorie()
{
	service.emptySpaltorie();
	cout << "\nS-au sters toate masinile din catalogul spalatoriei.\n\n";
}

void ConsoleUI::printMasiniSpalatorie()
{
	vector<Masina> masini = service.getMasiniFromSpalatorie();
	if (masini.size() == 0)
		cout << "Nu exista masini!\n";
	else
	{
		for (const auto& masina : masini)
			cout << "Numar de inmatriculare: " << masina.getNumarInmatriculare() << " | Producator: " << masina.getProducator() << " | Model: " << masina.getModel() << " | Tip: " << masina.getTip() << endl;
	}
}

void ConsoleUI::exportMasini()
{
	string filename, type;
	cout << "Introduceti numele fisierului: ";
	cin >> filename;
	cout << "Introduceti extensia fisierului (html/csv): ";
	cin >> type;
	if (service.exportFile(filename, type))
		cout << "\nExport cu succes!\n";
	else
		cout << "\nExport failed!\n";
}




void ConsoleUI::uiSpalatorie() {
	int runningSpalatorie = 1;
	string comanda;
	while (runningSpalatorie == 1)
	{
		cout << "\nMENIU SPALATORIE" << endl;
		cout << "1.Adauga masina in program\n";
		cout << "2.Adauga masina random in program\n";
		cout << "3.Goleste programul\n";
		cout << "4.Afiseaza programul actual\n";
		cout << "5.Export in fisier\n";
		cout << "6.Inapoi la meniul principal\n";

		cout << "\nComanda este:";
		getline(cin >> ws, comanda);
		switch (comanda.at(0))
		{
		case '1':
			uiAddSpalatorie();
			break;
		case '2':
			uiAddRandomCarToSpalatorie();
			break;
		case '3':
			uiEmptySpalatorie();
			break;
		case '4':
			printMasiniSpalatorie();
			break;
		case '5':
			exportMasini();
			break;
		case '6':
			runningSpalatorie = 0;
			break;
		default:
			break;
		}
		cout << "Numar total de masini la spalatorie: " << service.getMasiniFromSpalatorie().size() << endl;
	}
}

void ConsoleUI::run() {

	int stop = 1;
	string comanda;
	while (stop == 1)
	{
		printf("\n1.Adaugare de masini\n");
		printf("2.Actualizare masina existenta\n");
		printf("3.Sterge masina existenta\n");
		printf("4.Filtrare masini dupa: producator, tip\n");
		printf("5.Sortare masini\n");
		printf("6.Afiseaza lista cu masini\n");
		printf("7.Meniu pentru spalatorie\n");
		printf("8.Undo\n");
		printf("9.Iesire aplicatie\n");

		cout << "\nComanda este:";
		getline(cin >> ws, comanda);


		switch (comanda.at(0))
		{
		case '1':
			uiAdd();
			break;
		case '2':
			uiActualizare();
			break;
		case '3':
			uiSterge();
			break;
		case '4':
			uiFilter();
			break;
		case '5':
			uiSort();
			break;
		case '6':
			printMasini();
			break;
		case '7':
			uiSpalatorie();
			break;
		case '8':
			if (service.undo() == -1)
				cout << "No more undo!\n";
			else
				printMasini();
			break;
		case '9':
			stop = 0;
			break;
		default:
			cout << "Comanda invalida!\n";
			break;

		}

	}
}


