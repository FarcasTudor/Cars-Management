#pragma once
#include "repository.h"
#include "validators.h"
#include <functional>
#include "Spalatorie.h"
#include "Undo.h"
//#include "Observer.h"

using std::function;

class MasinaStore {
private:
	MasinaRepo& repository;
	MasinaValidator& validator;

	vector<std::unique_ptr<ActiuneUndo>> undoActiuni;
	Spalatorie spalatorieCurenta;
public:
	/*
	Adauga o masina cu numarul de inmatriuclare numarInmatriculare, producatorul producator, modelul model, tipul tip
	*@param numarInmatriculare: numarul de inmatricularei a masinii care se adauga (string)
	*@param producator: producatorul masinii care se adauga (string)
	*@param model: modelul masinii care se adauga (string)
	*@param tip: tipul masinii care se adauga (string)
	*
	* @throws:
	*	RepoException daca mai exista masina cu numarul de inmatriculare datdat
	*	ValidationException daca masina nu este valida
	*/
	void addMasina(string numarInmatriculare, string producator, string model, string tip);

	void actualizareMasina(string numarInmatriculare, string producator, string model, string tip);

	void stergeMasina(string numarInmatriculare);

	vector<Masina> sortByNumarInmatriculare(); 

		vector<Masina> sortByTip();

	vector<Masina> sortByProducatorModel();

	vector<Masina> sortare_generala(bool(*functie_comparare_mai_mic)(const Masina&, const Masina&));

	vector<Masina> filtrareProducator(string producator);

	vector<Masina> filtrareTip(string tip);

	MasinaStore(MasinaRepo& masinaRepository, MasinaValidator& validatorMasina) noexcept : repository{ masinaRepository }, validator{ validatorMasina }  {};

	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Service
	//(in aplicatie avem 1 singur Service)
	MasinaStore(const MasinaStore& other) = delete;

	void addMasinaToSpalatorie(string numarInmatriculare);
	size_t addRandomMasiniToSpalatorie(int numarDeMasiniDeAdaugat);
	const vector<Masina>& getMasiniFromSpalatorie() noexcept;
	void emptySpaltorie() noexcept;
	bool exportFile(const string filename, const string type);
	/*
	Returneaza un vector cu toate masinile disponibile

	@return: lista cu toate masinile disponibile
	*/
	const vector<Masina>& getAllMasini();

	int undo();

	Spalatorie& getSpalatorie() {
		return this->spalatorieCurenta;
	}
};

void testeService();