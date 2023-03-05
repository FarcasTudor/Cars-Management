#pragma once
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

class Masina {
private:
	string numarInmatriculare;
	string producator;
	string model;
	string tip;

public:
	Masina() = delete;
	Masina(string numarInmatriculare, string producator, string model, string tip) : numarInmatriculare{ numarInmatriculare }, producator{ producator }, model{ model }, tip{ tip } {};

	string getNumarInmatriculare() const;
	string getProducator() const;
	string getModel() const;
	string getTip() const;

	void setNumarInmatriculare(string numarInmatriculareNou);
	void setProducator(string producatorNou);
	void setModel(string modelNou);
	void setTip(string tipNou);

};

bool comparareNumarInmatriculare(const Masina& masina1, const Masina& masina2);

bool comparareTip(const Masina& masina1, const Masina& masina2);

bool comparareProducatorModel(const Masina& masina1, const Masina& masina2);

void testeDomain();