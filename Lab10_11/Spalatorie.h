#pragma once
#include "entities.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "Observer.h"

using std::vector;
class Spalatorie : public Observable {
private:
	vector<Masina> listaSpalatorie;

public:
	Spalatorie() = default;

	void addMasinaToSpalatorie(const Masina& masina);

	void AddRandomCars(vector<Masina> listaMasini, int numarDeMasiniDeAdaugat);

	const vector<Masina>& getAllCarsFromListaSpalatorie() noexcept;



	void emptySpalatorieRepo() noexcept;
};

class SpalatorieException {
	vector<string> errorMessage;
public:
	SpalatorieException(vector<string> errorMessages) :errorMessage{ errorMessages } {};

	string getErrorMessages() {
		string mesajFinal = "";
		for (const string MesajEroare : errorMessage) {
			mesajFinal += MesajEroare + "\n";
		}
		return mesajFinal;
	}
};