#pragma once
#include <iostream>
#include <vector>
#include "entities.h"

using std::vector;

class MasinaRepo {
	//protected: 
private:
	vector<Masina> allMasini;
public:

	virtual ~MasinaRepo() = default;

	MasinaRepo() = default;

	MasinaRepo(const MasinaRepo& other) = delete;
	/*
	Adauga o masina in lista
	@param masina: masina care se adauga (Masina)
	@return -
	post: masina va fi adaugata in lista

	@throws: RepoException daca o masina cu acelasi numar de inmatriculare
			 exista deja
	*/
	virtual void store(const Masina& masina);
	/*
	Actualizeaza o masina din lista
	@param masina: masina dupa care o actualizam
	@return -
	post: masina va fi modificata in lista

	@throws: RepoException daca o masina cu acelasi numar de inmatriculare
			  nu exista
	*/
	virtual void actualizare(const Masina& masina1);

	/*

	*/
	virtual void stergeMasina(string numarDeInmatriculare);
	/*
	Returneaza o lista cu toate masinile
	@return: lista cu masini
	*/
	virtual const vector<Masina>& getAllMasini();
	bool exportFisier(const string filename, const string type);
	/*
	Cauta o masina cu numar de inmatriculare dat

	@param numarDeInmatriculare: numare de inmatriculare dupa care se cauta
	@returns: entitatea Masina cu numar de inamtriculre dat (daca aceasta exista)
	@throws: RepoException daca nu exista masina cu numarul de inmatriculare dat*/
	virtual const Masina& find(const string numarDeInmatriculare);

	/*
	Verifica daca o masina data exista in lista

	@param masina: masina care se cauta in lista
	@return: true daca masina exista, false altfel
	*/
	virtual bool exists(const Masina& masina);



};

class RepositoryLaborator : public MasinaRepo
{
private:
	const double probability = 1;
	//vector<Masina> masini;
public:
	RepositoryLaborator() noexcept : MasinaRepo() {};

	void store(const Masina& masina) override;

	void stergeMasina(const string numarDeInmatriculare) override;

	const Masina& find(const string numarDeInmatriculare) override;

	void actualizare(const Masina& masina) override;

	const vector<Masina>& getAllMasini() override;

	bool exists(const Masina& masina) override;

};
void testeRepo();


/*
Clasa de exceptii specifice Repo
*/
class RepoException {
private:
	string errorMessage;
public:
	RepoException(string mesaj) :errorMessage{ mesaj } {};
	string getErrorMessage() {
		return this->errorMessage;
	}
};

class MasinaRepoFile : public MasinaRepo {
private:
	string filename;
	void loadFromFile();
	void writeToFile();
public:
	MasinaRepoFile() = delete;
	MasinaRepoFile(string filename) : MasinaRepo(), filename{ filename }{ loadFromFile(); };
	//MasinaRepoFile(const MasinaRepoFile& repository) = delete;
	//~MasinaRepoFile() = default;

	void store(const Masina& masina) override;
	void stergeMasina(string numarDeInmatriculare) override;
	void actualizare(const Masina& masina) override;

};
































