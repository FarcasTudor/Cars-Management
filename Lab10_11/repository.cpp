#include "repository.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <algorithm>
using std::ifstream;
using std::stringstream;
using std::ofstream;

bool MasinaRepo::exists(const Masina& masina) {
    try {
        find(masina.getNumarInmatriculare());
        return true;
    }
    catch (RepoException) {
        return false;
    }
}

bool MasinaRepo::exportFisier(const string filename, const string type)
{
    string nume_fisier = filename + '.' + type;
    std::ofstream fout(nume_fisier);
    if (type == "html" || type == "csv")
    {
        for (const Masina& masina : this->allMasini)
        {
            fout << "Numar de inmatriculare: " << masina.getNumarInmatriculare() << " | Producator: " << masina.getProducator() << " | Model: " << masina.getModel() << " | Tip: " << masina.getTip() << endl;
        }
        return true;
    }
    return false;
}


const Masina& MasinaRepo::find(const string numarDeInmatriculare)
{

    for (const Masina& masina : this->allMasini)
        if (masina.getNumarInmatriculare() == numarDeInmatriculare)
            return masina;
    throw RepoException("Masina cu numarul de inmatriculare " + numarDeInmatriculare + " nu exista in lista!\n");




    /*vector<Masina>::iterator find = std::find_if(this->allMasini.begin(), this->allMasini.end(), [=](const Masina& masina) {
        return masina.getNumarInmatriculare() == numarDeInmatriculare;
        });
    if (find != this->allMasini.end())
        return (*find);
    else
        throw RepoException("Masina cu numarul de inmatriculare " + numarDeInmatriculare + " nu exista in lista!\n");*/
}



void MasinaRepo::actualizare(const Masina& masina1)
{
    if (exists(masina1) == false)
        throw RepoException("Masina cu numarul de inmatriculare " + masina1.getNumarInmatriculare() + " nu exista in lista!\n");
    else
    {
        for (auto& masina : allMasini)
        {
            if (masina1.getNumarInmatriculare() == masina.getNumarInmatriculare())
            {
                masina = masina1;
                break;
            }
        }

    }
}


void MasinaRepo::stergeMasina(string numarDeInmatriculare)
{

    Masina masina1 = find(numarDeInmatriculare);
    int pozitie = -1;
    for (const Masina& masina : allMasini)
    {
        pozitie++;
        if (masina.getNumarInmatriculare() == numarDeInmatriculare)
        {
            allMasini.erase(allMasini.begin() + pozitie);
            break;
        }
    }

}

const vector<Masina>& MasinaRepo::getAllMasini()
{
    /*ector<Masina> masini;
    for (auto &masina : this->allMasini)
    {
        masini.push_back(masina);
    }
    return masini;*/
    return this->allMasini;
}

void MasinaRepo::store(const Masina& masina)
{
    if (exists(masina))
    {
        throw RepoException("Masina cu numarul de inmatriculare " + masina.getNumarInmatriculare() + " exista in lista!\n");
    }
    this->allMasini.push_back(masina);
}


void testAddRepo()
{
    MasinaRepo testRepo;
    Masina masina1{ "ms72tab" , "bmw", " seria5" , "sport" };
    testRepo.store(masina1);

    assert(testRepo.getAllMasini().size() == 1);

    Masina masina2{ "ms72tab", "audi", "rs8", "mini" };
    try {
        testRepo.store(masina2);

    }
    catch (RepoException& mesaj) {

        assert(mesaj.getErrorMessage() == "Masina cu numarul de inmatriculare ms72tab exista in lista!\n");
        assert(true);
    }

}
void testFindRepo()
{
    MasinaRepo testRepo;
    Masina masina1{ "ms72tab" , "bmw", "seria5" , "sport" };
    Masina masina2{ "ms73tab", "audi", "rs8", "mini" };
    Masina masina3{ "ms74tab", "porsche", "cayene", "suv" };
    testRepo.store(masina1);
    testRepo.store(masina2);
    assert(testRepo.exists(masina1));
    assert(!testRepo.exists(masina3));

    Masina masina_gasita = testRepo.find("ms72tab");
    assert(masina_gasita.getProducator() == "bmw");
    assert(masina_gasita.getModel() == "seria5");
    assert(masina_gasita.getTip() == "sport");

    try {
        testRepo.find("ms74tab");

    }
    catch (RepoException& errorMessage) {
        assert(errorMessage.getErrorMessage() == "Masina cu numarul de inmatriculare ms74tab nu exista in lista!\n");
        assert(true);
    }
}


void testActualizare()
{
    MasinaRepo testRepo;
    Masina masina1{ "ms72tab" , "bmw", "seria5" , "sport" };
    testRepo.store(masina1);
    assert(testRepo.exists(masina1));

    Masina masina_dupa_care_actualizam{ "ms72tab" , "MERCEDES", "C_class", "sedan" };
    testRepo.actualizare(masina_dupa_care_actualizam);

    assert(testRepo.find("ms72tab").getProducator() == "MERCEDES");
    assert(testRepo.find("ms72tab").getModel() == "C_class");
    assert(testRepo.find("ms72tab").getTip() == "sedan");

    try {
        Masina masina_dupa_care_actualizam2{ "inexistent" , "MERCEDES", "C_class", "sedan" };
        testRepo.actualizare(masina_dupa_care_actualizam2);
    }
    catch (RepoException& errorMessage) {
        assert(errorMessage.getErrorMessage() == "Masina cu numarul de inmatriculare inexistent nu exista in lista!\n");
        assert(true);
    }

}


void testSterge()
{
    MasinaRepo testRepo;
    Masina masina1{ "ms72tab" , "bmw", "seria5" , "sport" };
    testRepo.store(masina1);
    assert(testRepo.exists(masina1));
    assert(testRepo.getAllMasini().size() == 1);

    try {
        testRepo.stergeMasina("inexistent");
    }
    catch (RepoException& errorMessage) {
        assert(errorMessage.getErrorMessage() == "Masina cu numarul de inmatriculare inexistent nu exista in lista!\n");
        assert(true);
    }

    testRepo.stergeMasina("ms72tab");
    assert(testRepo.getAllMasini().size() == 0);

}



void testeRepo()
{
    testAddRepo();
    testFindRepo();
    testActualizare();
    testSterge();
}



void RepositoryLaborator::store(const Masina& masina)
{
    const int numar_random = rand() % 10;
    if (numar_random < probability)
        throw RepoException("Nu se poate executa functia. Mai incearca o data!");
    MasinaRepo::store(masina);
}

void RepositoryLaborator::stergeMasina(const string numarDeInmatriculare)
{
    const int numar_random = rand() % 10;
    if (numar_random < probability)
        throw RepoException("Nu se poate executa functia. Mai incearca o data!");
    MasinaRepo::stergeMasina(numarDeInmatriculare);
}

void RepositoryLaborator::actualizare(const Masina& masina)
{
    const int numar_random = rand() % 10;
    if (numar_random < probability)
        throw RepoException("Nu se poate executa functia. Mai incearca o data!");
    MasinaRepo::actualizare(masina);
}

const vector<Masina>& RepositoryLaborator::getAllMasini()
{
    const int numar_random = rand() % 10;
    if (numar_random < probability)
        throw RepoException("Nu se poate executa functia. Mai incearca o data!");
    return MasinaRepo::getAllMasini();
}

bool RepositoryLaborator::exists(const Masina& masina)
{
    const int random = (rand() % 10);
    if (random < probability)
        throw RepoException("Executia a intampinat o eroare. Incearca din nou!\n");
    return MasinaRepo::exists(masina);
}

const Masina& RepositoryLaborator::find(const string numarDeInmatriculare)
{
    const int numar_random = (rand() % 10);
    if (numar_random < probability)
        throw RepoException("Nu se poate executa functia. Mai incearca o data!");
    return MasinaRepo::find(numarDeInmatriculare);
}



void MasinaRepoFile::loadFromFile()
{
    ifstream fisier(this->filename);
    if (!fisier.is_open()) {
        throw RepoException("Cannot read from file " + filename + "!\n");
    }
    string line;
    while (getline(fisier, line))
    {
        string numarDeInmatriculare, producator, model, tip;
        size_t pozitieDelimitator = line.find_first_of(",");
        numarDeInmatriculare = line.substr(0, pozitieDelimitator);
        line = line.substr(pozitieDelimitator + 1, line.length());

        pozitieDelimitator = line.find_first_of(",");
        producator= line.substr(0, pozitieDelimitator);
        line = line.substr(pozitieDelimitator + 1, line.length());

        pozitieDelimitator = line.find_first_of(",");
        model = line.substr(0, pozitieDelimitator);
        line = line.substr(pozitieDelimitator + 1, line.length());

        pozitieDelimitator = line.find_first_of(",");
        tip = line.substr(0, pozitieDelimitator);
        line = line.substr(pozitieDelimitator + 1, line.length());
        Masina masinaDinFisier{ numarDeInmatriculare, producator, model, tip };
        MasinaRepo::store(masinaDinFisier);
    }
    fisier.close();
}

void MasinaRepoFile::writeToFile()
{
    ofstream masinaOutput(this->filename);
    if (!masinaOutput.is_open())
        throw RepoException("Cannot write to file " + filename + "!\n");
    for (auto& masina : getAllMasini())
        masinaOutput << masina.getNumarInmatriculare() << "," << masina.getProducator() << "," << masina.getModel() << "," << masina.getTip() << endl;
    masinaOutput.close();
}

void MasinaRepoFile::store(const Masina& masina)
{
    MasinaRepo::store(masina);
    writeToFile();
    
}

void MasinaRepoFile::stergeMasina(string numarDeInmatriculare)
{
    MasinaRepo::stergeMasina(numarDeInmatriculare);
    writeToFile();
}

void MasinaRepoFile::actualizare(const Masina& masina)
{
    MasinaRepo::actualizare(masina);
    writeToFile();
}
