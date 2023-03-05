#pragma once
#include "service.h"
#include <functional>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <ostream>
//#include <gsl/gsl_util>


using std::sort;

void MasinaStore::addMasina(string numarInmatriculare, string producator, string model, string tip)
{
	Masina masina1{ numarInmatriculare, producator, model, tip };
	validator.valideaza(masina1);
	repository.store(masina1);
	undoActiuni.push_back(std::make_unique<undoAdauga>(repository, masina1));
}

void MasinaStore::actualizareMasina(string numarInmatriculare, string producator_nou, string model_nou, string tip_nou)
{
	Masina masina1{ numarInmatriculare, producator_nou, model_nou, tip_nou };
	validator.valideaza(masina1);
	const Masina masina_de_modificat = repository.find(numarInmatriculare);
	undoActiuni.push_back(std::make_unique <undoActualizeaza>(repository, masina_de_modificat));
	repository.actualizare(masina1);

}

void MasinaStore::stergeMasina(string numarInmatriculare)
{
	const Masina masina = repository.find(numarInmatriculare);
	undoActiuni.push_back(std::make_unique<undoSterge>(repository, masina));
	repository.stergeMasina(numarInmatriculare);
}

vector<Masina> MasinaStore::sortByNumarInmatriculare()
{
	vector<Masina> lista_sortata = repository.getAllMasini();
	sort(lista_sortata.begin(), lista_sortata.end(), comparareNumarInmatriculare);
	return lista_sortata;
}

vector<Masina> MasinaStore::sortByTip()
{
	vector<Masina> lista_sortata = repository.getAllMasini();
	sort(lista_sortata.begin(), lista_sortata.end(), comparareTip);
	return lista_sortata;
}

vector<Masina> MasinaStore::sortByProducatorModel()
{
	return sortare_generala(comparareProducatorModel);
}

vector<Masina> MasinaStore::sortare_generala(bool(*functie_comparare_mai_mic)(const Masina&, const Masina&))
{
	vector<Masina> masini{ repository.getAllMasini() };
	/*for (size_t i = 0; i < masini.size(); i++)
	{
		for (size_t j = i + 1; j < masini.size(); j++)
		{
			if (!functie_comparare_mai_mic(masini[i], masini[j]))
			{
				Masina masina_auxiliara = masini[i];
				masini[i] = masini[j];
				masini[j] = masina_auxiliara;
			}
		}
	}*/
	sort(masini.begin(), masini.end(), functie_comparare_mai_mic);
	return masini;
}


vector<Masina> MasinaStore::filtrareProducator(string producator)
{
	vector<Masina> masini{ };
	vector<Masina> lista_masini{ repository.getAllMasini() };

	std::copy_if(lista_masini.begin(), lista_masini.end(), std::back_inserter(masini), [producator](const Masina& masina) {return masina.getProducator() == producator;  });
	return masini;
}

void MasinaStore::addMasinaToSpalatorie(string numarInmatriculare)
{
	const auto& masina = repository.find(numarInmatriculare);
	spalatorieCurenta.addMasinaToSpalatorie(masina);
}

size_t MasinaStore::addRandomMasiniToSpalatorie(int numarDeMasiniDeAdaugat)
{
	spalatorieCurenta.AddRandomCars(this->getAllMasini(), numarDeMasiniDeAdaugat);
	return spalatorieCurenta.getAllCarsFromListaSpalatorie().size();
}

const vector<Masina>& MasinaStore::getMasiniFromSpalatorie() noexcept
{
	return spalatorieCurenta.getAllCarsFromListaSpalatorie();
}

void MasinaStore::emptySpaltorie() noexcept
{
	spalatorieCurenta.emptySpalatorieRepo();
}

bool MasinaStore::exportFile(const string filename, const string type)
{
	return repository.exportFisier(filename, type);
}

const vector<Masina>& MasinaStore::getAllMasini()
{
	return this->repository.getAllMasini();
}

int MasinaStore::undo()
{
	if (undoActiuni.empty())
		return -1;
	undoActiuni.back()->doUndo();
	undoActiuni.pop_back();
	return 0;
}


vector<Masina> MasinaStore::filtrareTip(string tip)
{
	vector<Masina> masini{ };
	vector<Masina> lista_masini{ repository.getAllMasini() };

	std::copy_if(lista_masini.begin(), lista_masini.end(), std::back_inserter(masini), [tip](const Masina& masina) {return masina.getTip() == tip;  });

	return masini;
}


void testAddService()
{
	MasinaRepo testRepository;
	MasinaValidator testValidator;
	MasinaStore testService{ testRepository, testValidator };

	testService.addMasina("ms72tab", "bmw", "seria5", "sport");
	testService.addMasina("ms73tab", "audi", "rs8", "suv");
	testService.addMasina("ms74tab", "porsche", "cayene", "sedan");

	assert(testService.getAllMasini().size() == 3);
	//1
	try {
		testService.addMasina("ms72tab", "bmw", "seria5", "sport");

	}
	catch (RepoException&) {
		assert(true);
	}
	//2
	try {
		testService.addMasina("", "bmw", "seria5", "sport");
		//assert(false);
	}
	catch (ValidationException& errorMessage) {
		assert(errorMessage.getErrorMessages() == "Numarul de inmatriculare trebuie sa aiba cel putin 7 si cel mult 8 caractere!\n");
		assert(true);
	}
	//3
	try {
		testService.addMasina("ms72tab", "", "seria5", "sport");

	}
	catch (ValidationException& errorMessage) {
		assert(errorMessage.getErrorMessages() == "Producatorul trebuie sa aiba cel putin 2 caractere!\n");
		assert(true);
	}
	//4
	try {
		testService.addMasina("ms72tab", "bmw", "", "sport");

	}
	catch (ValidationException& errorMessage) {
		assert(errorMessage.getErrorMessages() == "Modelul trebuie sa aiba cel putin 2 caractere!\n");
		assert(true);
	}
	//5
	try {
		testService.addMasina("ms72tab", "bmw", "seria5", "");

	}
	catch (ValidationException& errorMessage) {
		assert(errorMessage.getErrorMessages() == "Tipul trebuie sa aiba cel putin 2 caractere!\n");
		assert(true);
	}
}

void testFiltrareService()
{
	MasinaRepo testRepository;
	MasinaValidator testValidator;
	MasinaStore testService{ testRepository, testValidator };

	testService.addMasina("ms72tab", "bmw", "seria5", "sport");
	testService.addMasina("ms73tab", "audi", "rs8", "sport");
	testService.addMasina("ms74tab", "porsche", "cayene", "sedan");

	vector<Masina> masiniSport = testService.filtrareTip("sport");
	assert(masiniSport.size() == 2);

	vector<Masina> masiniSedan = testService.filtrareTip("sedan");
	assert(masiniSedan.size() == 1);

	vector<Masina> masiniBMW = testService.filtrareProducator("bmw");
	assert(masiniBMW.size() == 1);

}

void testSortService()
{
	MasinaRepo testRepository;
	MasinaValidator testValidator;
	MasinaStore testService{ testRepository, testValidator };

	testService.addMasina("ms73tab", "audi", "seria5", "sport");
	testService.addMasina("ms72tab", "audi", "rs8", "sport");
	testService.addMasina("ms74tab", "porsche", "cayene", "sedan");

	vector<Masina> sortedByNumarInmatriculare = testService.sortByNumarInmatriculare();
	assert(sortedByNumarInmatriculare.at(0).getNumarInmatriculare() == "ms72tab");
	assert(sortedByNumarInmatriculare.at(1).getNumarInmatriculare() == "ms73tab");
	assert(sortedByNumarInmatriculare.at(2).getNumarInmatriculare() == "ms74tab");

	vector<Masina> sortedByTip = testService.sortByTip();
	assert(sortedByTip.at(0).getNumarInmatriculare() == "ms74tab");
	assert(sortedByTip.at(1).getNumarInmatriculare() == "ms73tab");
	assert(sortedByTip.at(2).getNumarInmatriculare() == "ms72tab");

	vector<Masina> sortedbyProducatorModel = testService.sortByProducatorModel();
	//assert(gsl::at()sortedbyProducatorModel, 0) == "ms72tab");
	assert(sortedbyProducatorModel.at(0).getNumarInmatriculare() == "ms72tab");
	assert(sortedbyProducatorModel.at(1).getNumarInmatriculare() == "ms73tab");
	assert(sortedbyProducatorModel.at(2).getNumarInmatriculare() == "ms74tab");


}

void testStergeService()
{
	MasinaRepo testRepository;
	MasinaValidator testValidator;
	MasinaStore testService{ testRepository, testValidator };

	testService.addMasina("ms73tab", "audi", "rs8", "sport");
	testService.addMasina("ms72tab", "audi", "seria5", "sport");
	testService.addMasina("ms74tab", "porsche", "cayene", "sedan");

	assert(testService.getAllMasini().size() == 3);

	testService.stergeMasina("ms72tab");
	assert(testService.getAllMasini().size() == 2);

}

void testActualizareService()
{
	MasinaRepo testRepository;
	MasinaValidator testValidator;
	MasinaStore testService{ testRepository, testValidator };

	testService.addMasina("ms73tab", "audi", "rs8", "sport");

	assert(testService.getAllMasini().size() == 1);

	testService.actualizareMasina("ms73tab", "mercedes", "C_class", "mini");
	assert(testRepository.find("ms73tab").getProducator() == "mercedes");
	assert(testRepository.find("ms73tab").getModel() == "C_class");
	assert(testRepository.find("ms73tab").getTip() == "mini");

}

void testSpalatorie()
{
	MasinaRepo testRepo;
	MasinaValidator testValidator;
	MasinaStore testService{ testRepo, testValidator };

	testService.addMasina("ms73tab", "audi", "rs8", "sport");
	testService.addMasina("ms72tab", "audi", "seria5", "sport");
	testService.addMasina("ms74tab", "porsche", "cayene", "sedan");

	assert(testService.getAllMasini().size() == 3);
	testService.addRandomMasiniToSpalatorie(2);
	assert(testService.getMasiniFromSpalatorie().size() == 2);
	testService.emptySpaltorie();
	assert(testService.getMasiniFromSpalatorie().size() == 0);

	testService.addRandomMasiniToSpalatorie(10);
	assert(testService.getMasiniFromSpalatorie().size() == 3);

	testService.emptySpaltorie();

	testService.addMasinaToSpalatorie("ms72tab");
	assert(testService.getMasiniFromSpalatorie().size() == 1);

	try {
		testService.addMasinaToSpalatorie("NuExista");
	}
	catch (RepoException&) {
		assert(true);
	}
	testService.addMasina("ms99tab", "aa", "aa", "aa");
	testService.addMasinaToSpalatorie("ms99tab");
	assert(testService.exportFile("fisierFacutPentruTest", "html") == true);
	assert(testService.exportFile("fisierFacutPentruTest", "extensieIncorecta") == false);
}

void testUndo()
{
	MasinaRepo testRepo;
	MasinaValidator testValidator;
	MasinaStore testService{ testRepo, testValidator };

	testService.addMasina("ms73tab", "audi", "rs8", "sport");
	testService.actualizareMasina("ms73tab", "bmw", "seria5", "sport");
	testService.stergeMasina("ms73tab");
	assert(testService.getAllMasini().size() == 0);
	testService.undo();
	assert(testService.getAllMasini().size() == 1);
	testService.undo();
	const Masina masina = testRepo.find("ms73tab");
	assert(masina.getTip() == "sport");
	testService.undo();
	assert(testService.getAllMasini().size() == 0);
	assert(testService.undo() == -1);

}

void testeService()
{
	testAddService();
	testFiltrareService();
	testSortService();
	testStergeService();
	testActualizareService();
	testSpalatorie();
	testUndo();
}
