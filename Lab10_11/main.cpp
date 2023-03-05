#include "Lab10_11.h"
#include <QtWidgets/QApplication>

#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "UI.h"
#include "MasinaStoreGUI.h"

using namespace std;
using std::cout;
using std::endl;


void testAll()
{
    testeDomain();
    cout << "Domain tests passed!\n";
    testeRepo();
    cout << "Repo tests passed!\n";
    testeService();
    cout << "Service tests passed!\n";



}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MasinaRepoFile repositoryFile{ "masini.txt" };
    //MasinaRepo repository;
    MasinaValidator validator;
    MasinaStore service{ repositoryFile, validator };
    MasinaStoreGUI gui{ service };
    gui.show();
    gui.resize(742, 500);

    return a.exec();
}

