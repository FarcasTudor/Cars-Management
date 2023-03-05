#pragma once
#include <QtWidgets/QApplication>
#include <QWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include "Service.h"
#include <QMessageBox>
#include <string>
#include <set>
#include <vector>
#include <QDebug>
#include <QPainter>
#include <cstdlib>
#include <QRadioButton>
#include <QHeaderView>
#include "SpalatorieGUI.h"

using std::set;
using std::vector;
using std::string;
using std::count_if;
using std::to_string;

class MasinaStoreGUI : public QWidget {
private:
	MasinaStore& service;
	SpalatorieGUI spalatorieWindow{ service };

	QLabel* labelNumarDeInmatriculare = new QLabel{ "Numar de inmatriculare: " };
	QLabel* labelProducator = new QLabel{ " Producator: " };
	QLabel* labelModel = new QLabel{ " Model: " };
	QLabel* labelTip = new QLabel{ " Tip: " };

	QLineEdit* editNumarDeInmatriculare;
	QLineEdit* editProducator;
	QLineEdit* editModel;
	QLineEdit* editTip;

	QPushButton* buttonAddMasina;
	QPushButton* buttonModificare;

	QLabel* labelStergere = new QLabel{ "Numar de inmatriculare: " };
	QLineEdit* editStergere;
	QPushButton* buttonStergere;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSortareNumarDeInmatriculare = new QRadioButton(QString::fromStdString("Numar de inmatriculare"));
	QRadioButton* radioSortareTip = new QRadioButton(QString::fromStdString("Tip"));
	QPushButton* buttonSortMasini;

	QLabel* labelFiltrareCriteriu = new QLabel{ "Dupa ce se va face filtrarea: " };
	QLineEdit* editFiltrareProducator;
	QLineEdit* editFiltrareTip;
	QPushButton* buttonFiltrareMasini;

	QPushButton* buttonUndo;
	
	QPushButton* buttonReloadData;

	QTableWidget* tableMasini;

	//cerinta lab 10
	QWidget* widgetListaMasini;
	QVBoxLayout* layoutListaMasini;
	QListWidget* listaMasini;

	QPushButton* butonSpalatorie;

	//cerinta lab 11
	QWidget* widgetDynamic;
	QVBoxLayout* layoutButonDynamic;
	set<string>getTip(const vector<Masina>& masini);
	void updateDynamicButon();

	void initializeGUIComponents();

	void connectSignalSlots();
	void reloadListaMasini(vector<Masina> masini);

public:
	MasinaStoreGUI(MasinaStore& MasinaService) : service{ MasinaService } {
		initializeGUIComponents();
		connectSignalSlots();
		reloadListaMasini(service.getAllMasini());
	}

	void guiAddMasina();
	void guiStergeMasina();
	void guiModificareMasina();
};