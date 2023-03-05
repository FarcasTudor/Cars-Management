#include "MasinaStoreGUI.h"


void MasinaStoreGUI::initializeGUIComponents()
{
	//impartim fereastra in 2: in stanga, butoane+labels+qlineedits
	//iar in dreapta: tabelul cu masini

	//"stanga" si "dreapta" pentru ca este QHBoxLayout
	//se adauga componente incepand din stanga, pe orizontala
	//aici: "left" component, then "right" component
	//care la randul lor contin alte componente
	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* layoutLeft = new QVBoxLayout;
	left->setLayout(layoutLeft);

	//componente pentru functionalitatea de adaugare a unei masini
	//folosim un QFormLayout pentru detaliile de adaugare a unei masini
	QWidget* form = new QWidget;
	QFormLayout* layoutForm = new QFormLayout;
	form->setLayout(layoutForm);

	editNumarDeInmatriculare = new QLineEdit;
	editProducator = new QLineEdit;
	editModel = new QLineEdit;
	editTip = new QLineEdit;

	layoutForm->addRow(labelNumarDeInmatriculare, editNumarDeInmatriculare);
	layoutForm->addRow(labelProducator, editProducator);
	layoutForm->addRow(labelModel, editModel);
	layoutForm->addRow(labelTip, editTip);

	buttonAddMasina = new QPushButton("Adauga masina");
	layoutForm->addWidget(buttonAddMasina);

	buttonModificare = new QPushButton("Modifica o masina");
	layoutForm->addWidget(buttonModificare);

	//adaugam toate componentele legate de adaugare masina
	//in layout-ul care corespunde partii din stanga a ferestrei
	layoutLeft->addWidget(form);

	QWidget* formStergere = new QWidget;
	QFormLayout* layoutFormStergere = new QFormLayout;
	formStergere->setLayout(layoutFormStergere);

	editStergere = new QLineEdit();
	buttonStergere = new QPushButton("Sterge masina");
	layoutFormStergere->addRow(labelStergere, editStergere);
	layoutFormStergere->addWidget(buttonStergere);
	layoutLeft->addWidget(formStergere);

	//Radio Buttons: ne ajuta cand trebuie sa selectam doar o 
	//optiune din mai multe (doar un RadioButton poate fi selectat
	//la un moment dat)


	//vs. CheckBox (see documentation)
	//also see documentation on QGroupBox, QRadioButton pentru detalii

	//cream un GroupBox pentru radiobuttons care corespund 
	//criteriilor de sortare pe care le avem (dupanumarInmatriculare/tip) 
	//+ butonul de sortare
	QVBoxLayout* layoutRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(layoutRadioBox);
	layoutRadioBox->addWidget(radioSortareNumarDeInmatriculare);
	layoutRadioBox->addWidget(radioSortareTip);

	buttonSortMasini = new QPushButton("Sorteaza masini");
	layoutRadioBox->addWidget(buttonSortMasini);

	//adaugam acest grup in partea stanga, 
	//dupa componentele pentru adaugare in layout-ul vertical
	layoutLeft->addWidget(groupBox);

	//cream un form pentru filtrarea dupa producator
	QWidget* formFilter = new QWidget;
	QFormLayout* layoutFormFilter = new QFormLayout;
	formFilter->setLayout(layoutFormFilter);

	editFiltrareProducator = new QLineEdit();
	layoutFormFilter->addRow(labelFiltrareCriteriu, editFiltrareProducator);
	buttonFiltrareMasini = new QPushButton("Filtreaza masinile dupa producator");
	layoutFormFilter->addWidget(buttonFiltrareMasini);

	layoutLeft->addWidget(formFilter);
	buttonUndo = new QPushButton("Undo");
	buttonUndo->setStyleSheet("background-color: blue");
	layoutLeft->addWidget(buttonUndo);

	//Buton folosit pentru a reincarca datele
	//afisam toate melodiile in tabel, in ordinea initiala din fisier
	buttonReloadData = new QPushButton("Reload data");
	buttonReloadData->setStyleSheet("background-color: yellow");
	layoutLeft->addWidget(buttonReloadData);

	//componenta right - contine doar tabelul cu masini
	QWidget* right = new QWidget;
	QVBoxLayout* layoutRight = new QVBoxLayout;
	right->setLayout(layoutRight);

	int numberLines = 100;
	int numberColums = 4;
	this->tableMasini = new QTableWidget{ numberLines, numberColums };

	//setam header-ul tabelului
	QStringList tabelHeaderList;
	tabelHeaderList << "Numar de Inmatriculare" << "Producator" << "Model" << "Tip";
	this->tableMasini->setHorizontalHeaderLabels(tabelHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->tableMasini->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//spalatorie
	butonSpalatorie = new QPushButton{ "Deschide spalatorie" };
	butonSpalatorie->setStyleSheet("background-color: red");
	layoutLeft->addWidget(butonSpalatorie);

	layoutRight->addWidget(tableMasini);

	//CERINTA LABORATOR 10
	widgetListaMasini = new QWidget{};
	this->listaMasini = new QListWidget{};
	this->layoutListaMasini = new QVBoxLayout{};

	this->listaMasini->setFixedHeight(320);
	this->listaMasini->setSelectionMode(QAbstractItemView::SingleSelection);

	widgetListaMasini->setLayout(layoutListaMasini);
	layoutRight->addWidget(listaMasini);

	//buton dinamic pentru tipurile de masini
	widgetDynamic = new QWidget{};
	layoutButonDynamic = new QVBoxLayout{};
	widgetDynamic->setLayout(layoutButonDynamic);
	updateDynamicButon();

	mainLayout->addWidget(left);
	mainLayout->addWidget(right);
	mainLayout->addWidget(widgetDynamic);

}

void MasinaStoreGUI::connectSignalSlots()
{
	QObject::connect(buttonAddMasina, &QPushButton::clicked, this, &MasinaStoreGUI::guiAddMasina);
	QObject::connect(buttonStergere, &QPushButton::clicked, this, &MasinaStoreGUI::guiStergeMasina);
	QObject::connect(buttonModificare, &QPushButton::clicked, this, &MasinaStoreGUI::guiModificareMasina);
	QObject::connect(buttonSortMasini, &QPushButton::clicked, [&]() {
		if (this->radioSortareNumarDeInmatriculare->isChecked())
			this->reloadListaMasini(service.sortByNumarInmatriculare());
		else if (this->radioSortareTip->isChecked())
			this->reloadListaMasini(service.sortByTip());

		});
	QObject::connect(buttonFiltrareMasini, &QPushButton::clicked, [&]() {
		string filter = this->editFiltrareProducator->text().toStdString();
		this->reloadListaMasini(service.filtrareProducator(filter));
		});
	QObject::connect(buttonReloadData, &QPushButton::clicked, [&]() {
		this->reloadListaMasini(service.getAllMasini());
		});
	QObject::connect(buttonUndo, &QPushButton::clicked, [&]() {
		service.undo();
		this->reloadListaMasini(service.getAllMasini());
		});
	QObject::connect(butonSpalatorie, &QPushButton::clicked, [&]() {
		spalatorieWindow.show();
		});
	QObject::connect(listaMasini, &QListWidget::itemSelectionChanged, [&]() {
		auto masini = listaMasini->selectedItems();
		for (auto masina : masini) {
			qDebug() << masina->text();
			masina->setBackground(Qt::green);
		}

		});
}

void MasinaStoreGUI::reloadListaMasini(vector<Masina> masini)
{
	this->tableMasini->clearContents();
	this->tableMasini->setRowCount(masini.size());

	int lineNumber = 0;
	for (auto& masina : masini)
	{
		this->tableMasini->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(masina.getNumarInmatriculare())));
		this->tableMasini->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(masina.getProducator())));
		this->tableMasini->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(masina.getModel())));
		this->tableMasini->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(masina.getTip())));
		lineNumber++;
	}
	//lista de la cerinta de lab 10
	this->listaMasini->clear();
	const vector<Masina> allMasini = service.getAllMasini();
	for (auto& masina : allMasini)
	{
		QString currentItem = QString::fromStdString(masina.getNumarInmatriculare() + "\t" + masina.getProducator() + "\t" + masina.getModel() + "\n" + masina.getTip());
		this->listaMasini->addItem(currentItem);
	}
	updateDynamicButon();
}

void MasinaStoreGUI::guiAddMasina()
{
	try {
		//preluare detalii din QLineEdit-uri
		string numarDeInmatriculare = editNumarDeInmatriculare->text().toStdString();
		string producator = editProducator->text().toStdString();
		string model = editModel->text().toStdString();
		string tip = editTip->text().toStdString();

		//golim QLineEdit-urile dupa apasarea butonului
		editNumarDeInmatriculare->clear();
		editProducator->clear();
		editModel->clear();
		editTip->clear();

		this->service.addMasina(numarDeInmatriculare, producator, model, tip);
		this->reloadListaMasini(this->service.getAllMasini());

		//afisam un mesaj pentru a anunta utilizatorul ca masina s-a adaugat cu succes
		QMessageBox::information(this, "Info", QString::fromStdString("Masina adaugata cu succes."));

	}
	catch (RepoException& mesajEroare) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(mesajEroare.getErrorMessage()));
	}
}

void MasinaStoreGUI::guiStergeMasina()
{
	string numarDeInmatriculare = editStergere->text().toStdString();

	//golim QLineEdit-urile dupa apasarea butonului
	editStergere->clear();

	this->service.stergeMasina(numarDeInmatriculare);
	this->reloadListaMasini(this->service.getAllMasini());

	//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
	QMessageBox::information(this, "Info", QString::fromStdString("Masina stearsa cu succes."));

}

void MasinaStoreGUI::guiModificareMasina()
{
	try {
		//preluare detalii din QLineEdit-uri
		string numarDeInmatriculare = editNumarDeInmatriculare->text().toStdString();
		string producator_nou = editProducator->text().toStdString();
		string model_nou = editModel->text().toStdString();
		string tip_nou = editTip->text().toStdString();

		//golim QLineEdit-urile dupa apasarea butonului
		editNumarDeInmatriculare->clear();
		editProducator->clear();
		editModel->clear();
		editTip->clear();

		this->service.actualizareMasina(numarDeInmatriculare, producator_nou, model_nou, tip_nou);
		this->reloadListaMasini(this->service.getAllMasini());

		//afisam un mesaj pentru a anunta utilizatorul ca masina s-a modificat cu succes
		QMessageBox::information(this, "Info", QString::fromStdString("Masina modificata cu succes."));

	}
	catch (RepoException& mesajEroare) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(mesajEroare.getErrorMessage()));
	}
}


set<string> MasinaStoreGUI::getTip(const vector<Masina>& masini)
{
	set<string> tip;
	for (const auto& masina : masini)
		tip.insert(masina.getTip());
	return tip;
}

int acelasiTipDeMasina(const vector<Masina>& masini, string tip) {
	int numarMasini = count_if(masini.begin(), masini.end(), [&](Masina masina) {
		return masina.getTip() == tip; });
	return numarMasini;
}

void clearLayout(QLayout* layout)
{
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0)))
	{
		if (item->layout())
		{
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget())
			delete item->widget();
		delete item;
	}
}


void MasinaStoreGUI::updateDynamicButon()
{
	clearLayout(this->layoutButonDynamic);
	const vector<Masina>& masini = this->service.getAllMasini();
	set<string> tipuri = this->getTip(masini);

	for (string tip : tipuri)
	{
		QPushButton* buton = new QPushButton{ QString::fromStdString(tip) };
		layoutButonDynamic->addWidget(buton);
		int numarMasiniCuAcelasiTip = acelasiTipDeMasina(masini, tip);
		QObject::connect(buton, &QPushButton::clicked, [tip, numarMasiniCuAcelasiTip]() {
			QMessageBox::information(nullptr, "Info", QString::fromStdString("Masini cu tipul " + tip + ":" + to_string(numarMasiniCuAcelasiTip)));
			});

	}
}