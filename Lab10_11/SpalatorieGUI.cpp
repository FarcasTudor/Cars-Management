#include "SpalatorieGUI.h"

void SpalatorieGUI::initializareGUI()
{
	mainLayout = new QHBoxLayout{};
	this->setLayout(mainLayout);

	QWidget* left = new QWidget{};
	QVBoxLayout* layoutLeft = new QVBoxLayout{};
	left->setLayout(layoutLeft);

	QWidget* formWidget = new QWidget{};
	QFormLayout* layoutEdits = new QFormLayout{};
	labelNumarDeInmatriculare = new QLabel{ "Numar de inmatriculare" };
	editNumarDeInmatriculare = new QLineEdit{};

	labelSlider = new QLabel{ "Numar de masini de generat" };
	editNoSlider = new QLineEdit{};
	layoutEdits->addRow(labelNumarDeInmatriculare,editNumarDeInmatriculare);
	layoutEdits->addRow(labelSlider, editNoSlider);
	formWidget->setLayout(layoutEdits);

	butonAdd = new QPushButton{ "Adauga in spalatorie" };
	butonAdd->setStyleSheet("background-color: silver");

	butonGenerate = new QPushButton{ "Genereaza random" };
	butonGenerate->setStyleSheet("background-color: silver");

	butonEmpty = new QPushButton{ "Goleste spalatorie" };
	butonEmpty->setStyleSheet("background-color: silver");

	butonExport = new QPushButton{ "Export spalatorie" };
	butonExport->setStyleSheet("background-color: silver");

	butonClose = new QPushButton{ "Close" };
	butonClose->setStyleSheet("background-color: silver");


	butonLabelWindow = new QPushButton{ "Fereasta label" };
	butonLabelWindow->setStyleSheet("background-color: cyan");

	butonTableWindow = new QPushButton{ "Fereastra spalatorie tabel" };
	butonTableWindow->setStyleSheet("background-color: cyan");

	butonDrawWindow = new QPushButton{ "Ferestra desen" };
	butonDrawWindow->setStyleSheet("background-color: orange");

	sliderGenerate = new QSlider{};
	sliderGenerate->setMinimum(1);
	sliderGenerate->setMaximum(static_cast<int>(service.getAllMasini().size()));

	layoutLeft->addWidget(formWidget);
	layoutLeft->addWidget(butonAdd);
	layoutLeft->addWidget(butonGenerate);
	layoutLeft->addWidget(butonEmpty);
	layoutLeft->addWidget(butonExport);
	layoutLeft->addWidget(butonClose);
	//layoutLeft->addWidget(butonLabelWindow);
	layoutLeft->addWidget(butonTableWindow);
	layoutLeft->addWidget(butonDrawWindow);

	QWidget* right = new QWidget{};
	QVBoxLayout* layoutRight = new QVBoxLayout{};
	right->setLayout(layoutRight);

	listaMasini = new QListWidget{};
	listaMasini->setFixedHeight(320);
	listaMasini->setSelectionMode(QAbstractItemView::SingleSelection);
	
	layoutRight->addWidget(listaMasini);

	mainLayout->addWidget(left);
	mainLayout->addWidget(sliderGenerate);
	mainLayout->addWidget(right);

}

void SpalatorieGUI::connectSignalSlots()
{
	service.getSpalatorie().addObserver(this);
	QObject::connect(butonAdd, &QPushButton::clicked, this, &SpalatorieGUI::addMasinaLaSpalatorie);
	QObject::connect(sliderGenerate, &QSlider::sliderReleased, [&]() {
		qDebug() << sliderGenerate->value();
		});
	QObject::connect(butonGenerate, &QPushButton::clicked, [&]() {
		int numarMasini = this->sliderGenerate->value();
		editNoSlider->setText(QString::number(numarMasini));
		qDebug() << "Numar masini de adaugat: " << numarMasini;
		service.addRandomMasiniToSpalatorie(numarMasini);
		this->reloadSpalatorie();
		});
	QObject::connect(butonEmpty, &QPushButton::clicked, [&]() {
		service.emptySpaltorie();
		this->reloadSpalatorie();
		});
	QObject::connect(butonExport, &QPushButton::clicked, [&]() {

		});
	QObject::connect(butonClose, &QPushButton::clicked, this, &SpalatorieGUI::close);

	QObject::connect(butonLabelWindow, &QPushButton::clicked, this, [&]() {
		auto labelWindow = new SpalatorieGUILabel{
			service.getSpalatorie() };
		labelWindow->show();
		});
	QObject::connect(butonTableWindow, &QPushButton::clicked, this, [&]() {
		auto tableWindow = new SpalatorieGUITable{
			service.getSpalatorie() };
		tableWindow->show();
		});
	QObject::connect(butonDrawWindow, &QPushButton::clicked, this, [&]() {
		auto drawWindow = new SpalatorieGUIDraw{ service.getSpalatorie() };
		drawWindow->show();
		});
	QObject::connect(listaMasini, &QListWidget::itemSelectionChanged, [&]() {
		auto selectedItems = listaMasini->selectedItems();
		for (auto item : selectedItems)
		{
			qDebug() << item->text();
			item->setBackground(Qt::green);
		}

		});
}

void SpalatorieGUI::reloadSpalatorie()
{
	this->listaMasini->clear();
	const vector<Masina> masini = service.getMasiniFromSpalatorie();
	for (auto& masina : masini)
	{
		QString currentItem = QString::fromStdString(masina.getNumarInmatriculare() + "\t" + masina.getProducator() + "\t" + masina.getModel() + "\n" + masina.getTip());
		this->listaMasini->addItem(currentItem);
	}
}

void SpalatorieGUI::addMasinaLaSpalatorie()
{
	try {
		string numarDeInmatriculare = editNumarDeInmatriculare->text().toStdString();
		editNumarDeInmatriculare->clear();

		this->service.addMasinaToSpalatorie(numarDeInmatriculare);
		this->reloadSpalatorie();

		QMessageBox::information(this, "Info", QString::fromStdString("Masina adaugata cu succes."));

	}
	catch (RepoException& mesajEroare) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(mesajEroare.getErrorMessage()));
	}
	catch (ValidationException& mesajEroare) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(mesajEroare.getErrorMessages()));
	}
}

