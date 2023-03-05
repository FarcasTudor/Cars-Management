#include "Spalatorie.h"
using std::shuffle;

void Spalatorie::addMasinaToSpalatorie(const Masina& masina)
{
	this->listaSpalatorie.push_back(masina);
	notify();
}

void Spalatorie::AddRandomCars(vector<Masina> listaMasini, int numarDeMasiniDeAdaugat)
{
	shuffle(listaMasini.begin(), listaMasini.end(), std::default_random_engine(std::random_device{}()));

	while (listaSpalatorie.size() < numarDeMasiniDeAdaugat && listaMasini.size() > 0)
	{
		listaSpalatorie.push_back(listaMasini.back());
		listaMasini.pop_back();
	}
	notify();
}

const vector<Masina>& Spalatorie::getAllCarsFromListaSpalatorie() noexcept
{
	return this->listaSpalatorie;
}

void Spalatorie::emptySpalatorieRepo() noexcept
{
	this->listaSpalatorie.clear();
	notify();
}
