#pragma once
#include "service.h"

class ConsoleUI {
private:
	MasinaStore& service;
public:
	ConsoleUI(MasinaStore& service) noexcept :service{ service } {};
	ConsoleUI(const ConsoleUI& other) = delete;

	void uiAdd();
	void printMasini();
	void uiActualizare();
	void uiSterge();
	void uiSort();
	void uiFilter();
	//void addDefaultSongs();
	void uiAddSpalatorie();
	void uiAddRandomCarToSpalatorie();
	void uiEmptySpalatorie();
	void printMasiniSpalatorie();
	void exportMasini();
	void uiSpalatorie();
	void run();


};