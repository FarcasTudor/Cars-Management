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
#include <QMessageBox>
#include <string>
#include <set>
#include <vector>
#include <QDebug>
#include <QPainter>
#include <cstdlib>

#include "service.h"

using std::to_string;
using std::set;
using std::vector;

class SpalatorieGUI : public QWidget, public Observer {
private:
	MasinaStore& service;
	QHBoxLayout* mainLayout;
	QListWidget* listaMasini;

	QLabel* labelNumarDeInmatriculare;
	QLineEdit* editNumarDeInmatriculare;

	QPushButton* butonAdd;
	QPushButton* butonGenerate;
	QPushButton* butonEmpty;
	QPushButton* butonExport;
	QPushButton* butonClose;
	QPushButton* butonLabelWindow;
	QPushButton* butonTableWindow;
	QPushButton* butonDrawWindow;

	QLineEdit* editNoSlider;
	QLabel* labelSlider;
	QSlider* sliderGenerate;

	void initializareGUI();
	void connectSignalSlots();

	void reloadSpalatorie();
	void addMasinaLaSpalatorie();

	void update() override {
		reloadSpalatorie();
	}

public:
	SpalatorieGUI(MasinaStore& masinaStore) : service{ masinaStore } {
		initializareGUI();
		connectSignalSlots();
	}
};

class SpalatorieGUILabel : public QWidget, public Observer {
private:
	Spalatorie& spalatorie;
	QLabel* labelNoMasini;
	QLineEdit* editNoMasini;

	void initializareGUI() {
		QHBoxLayout* layout = new QHBoxLayout{};
		this->setLayout(layout);
		labelNoMasini = new QLabel{ "Numar de masini: " };
		editNoMasini = new QLineEdit{};
		layout->addWidget(labelNoMasini);
		layout->addWidget(editNoMasini);
		setAttribute(Qt::WA_DeleteOnClose);
		spalatorie.addObserver(this);
	};
	void update() override {
		this->editNoMasini->setText(QString::number(spalatorie.getAllCarsFromListaSpalatorie().size()));
	};
	~SpalatorieGUILabel() {
		spalatorie.removeObserver(this);
	}

public:
	SpalatorieGUILabel(Spalatorie& spalatorie) : spalatorie{ spalatorie } {
		initializareGUI();
	};
};

class SpalatorieGUITable :public QWidget, public Observer {
private:
	Spalatorie& spalatorie;
	QTableWidget* table;
	QPushButton* butonEmpty;
	void initGUI() {
		QHBoxLayout* layout = new QHBoxLayout{};
		this->setLayout(layout);
		table = new QTableWidget{};
		butonEmpty = new QPushButton{ "Goleste spalatoria" };
		layout->addWidget(table);
		layout->addWidget(butonEmpty);
		setAttribute(Qt::WA_DeleteOnClose);
		spalatorie.addObserver(this);
	};
	void reloadTableData(const vector<Masina>& masini) {
		this->table->setColumnCount(4);
		this->table->setRowCount(static_cast<int>(masini.size()));
		for (int i = 0; i < masini.size(); i++) {
			table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(masini[i].getNumarInmatriculare())));
			table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(masini[i].getProducator())));
			table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(masini[i].getModel())));
			table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(masini[i].getTip())));
		}

	};

	void connectSignalsSlots() {
		spalatorie.addObserver(this);

		QObject::connect(butonEmpty, &QPushButton::clicked, [&]() {
			spalatorie.emptySpalatorieRepo();;
			reloadTableData(spalatorie.getAllCarsFromListaSpalatorie());
			});
	}


public:
	SpalatorieGUITable(Spalatorie& spalatorie) :spalatorie{ spalatorie } {
		initGUI();
		connectSignalsSlots();
	};

	void update() override {
		this->reloadTableData(spalatorie.getAllCarsFromListaSpalatorie());
	}
	~SpalatorieGUITable() {
		spalatorie.removeObserver(this);
	}

};

class SpalatorieGUIDraw : public QWidget, public Observer {
	Spalatorie& spalatorie;
public:
	SpalatorieGUIDraw(Spalatorie& spalatorie) : spalatorie{ spalatorie } {
		spalatorie.addObserver(this);
	};

	void paintEvent(QPaintEvent*) override {
		QPainter painter{ this };
		int x = 0, y = 0;
		for (auto masina : spalatorie.getAllCarsFromListaSpalatorie()) {
			x = rand() % 400 + 1;
			y = rand() % 400 + 1;
			qDebug() << x << " " << y;
			painter.drawImage(x, y, QImage("yukiBUN.jpg"), 0, 0, 100, 100);

			x += 40;

		}
	}

	void update() override {
		this->repaint();
	}

	~SpalatorieGUIDraw() {
		spalatorie.removeObserver(this);
	}

	
};