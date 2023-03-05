#include "entities.h"
#include <cassert>

string Masina::getNumarInmatriculare() const {
	return this->numarInmatriculare;
}
string Masina::getProducator() const {
	return this->producator;
}
string Masina::getModel() const {
	return this->model;
}
string Masina::getTip() const {
	return this->tip;
}

void Masina::setNumarInmatriculare(string numarInmatriculareNou) {
	this->numarInmatriculare = numarInmatriculareNou;
}
void Masina::setProducator(string producatorNou) {
	this->producator = producatorNou;
}
void Masina::setModel(string modelNou) {
	this->model = modelNou;
}
void Masina::setTip(string tipNou) {
	this->tip = tipNou;
}


bool comparareNumarInmatriculare(const Masina& masina1, const Masina& masina2)
{
	return masina1.getNumarInmatriculare() < masina2.getNumarInmatriculare();
}


bool comparareTip(const Masina& masina1, const Masina& masina2)
{
	return masina1.getTip() < masina2.getTip();
}

bool comparareProducatorModel(const Masina& masina1, const Masina& masina2)
{
	if (masina1.getProducator() == masina2.getProducator())
		return masina1.getModel() < masina2.getModel();
	else
		return masina1.getProducator() < masina2.getProducator();
}


void testGetSet() {
	Masina masina1{ "ms72tab", "renault","megane3","sport" };
	assert(masina1.getNumarInmatriculare() == "ms72tab");
	assert(masina1.getProducator() == "renault");
	assert(masina1.getModel() == "megane3");
	assert(masina1.getTip() == "sport");

	masina1.setNumarInmatriculare("ms73tab");
	masina1.setProducator("bmw");
	masina1.setModel("seria5");
	masina1.setTip("sport");

	assert(masina1.getNumarInmatriculare() == "ms73tab");
	assert(masina1.getProducator() == "bmw");
	assert(masina1.getModel() == "seria5");
	assert(masina1.getTip() == "sport");



}

void testeDomain() {
	testGetSet();
}

