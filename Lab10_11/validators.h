#pragma once
#include "entities.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

class ValidationException {
	vector<string> errorMessage;
public:
	ValidationException(vector<string> errorMessages) :errorMessage{ errorMessages } {};

	string getErrorMessages() {
		string mesajFinal = "";
		for (const string MesajEroare : errorMessage) {
			mesajFinal += MesajEroare + "\n";
		}
		return mesajFinal;
	}
};

class MasinaValidator {
public:
	void valideaza(const Masina& masina) {
		vector<string> errors;
		if (masina.getNumarInmatriculare().length() < 7 || masina.getNumarInmatriculare().length() > 8)
			errors.push_back("Numarul de inmatriculare trebuie sa aiba cel putin 7 si cel mult 8 caractere!");
		if (masina.getProducator().length() < 2)
			errors.push_back("Producatorul trebuie sa aiba cel putin 2 caractere!");
		if (masina.getModel().length() < 2)
			errors.push_back("Modelul trebuie sa aiba cel putin 2 caractere!");
		if (masina.getTip().length() < 2)
			errors.push_back("Tipul trebuie sa aiba cel putin 2 caractere!");

		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};