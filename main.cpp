#include "mainwindow.h"
#include <QApplication>
#include <QSharedPointer>
#include "Repository.h"
#include "InMemoryRepository.h"
#include "FileRepository.h"
#include "Controller.h"
#include "Medicine.h"
using namespace std;

int main(int argc, char *argv[])
{
    auto_ptr<Repository<Medicine> > repo(new FileRepository("/home/patri/qt_workspace/qt_pharmacy/test.txt"));
    auto_ptr<MedicineController> ctrl(new MedicineController(repo));


    QApplication a(argc, argv);
    MainWindow w(ctrl);
    w.show();

    return a.exec();
}
