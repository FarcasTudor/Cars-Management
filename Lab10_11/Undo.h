#pragma once
#include "entities.h"
#include "repository.h"
#include <vector>
#include <algorithm>


using std::vector;
class ActiuneUndo {

public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;

};

class undoAdauga : public ActiuneUndo
{
	Masina masinaAdaugata;
	MasinaRepo& repository;

public:
	undoAdauga(MasinaRepo& repository, const Masina& masina) : repository{ repository }, masinaAdaugata{ masina } {}
	void doUndo() override
	{
		repository.stergeMasina(masinaAdaugata.getNumarInmatriculare());
	}
};

class undoSterge : public ActiuneUndo
{
	Masina masinaStearsa;
	MasinaRepo& repository;

public:
	undoSterge(MasinaRepo& repository, const Masina& masina) : repository{ repository }, masinaStearsa{ masina } {}
	void doUndo() override
	{
		repository.store(masinaStearsa);
	}
};

class undoActualizeaza : public ActiuneUndo
{
	Masina masinaModificata;
	MasinaRepo& repository;

public:
	undoActualizeaza(MasinaRepo& repository, const Masina& masina) : repository{ repository }, masinaModificata{ masina }{}
	void doUndo() override
	{
		repository.actualizare(masinaModificata);
	}
};