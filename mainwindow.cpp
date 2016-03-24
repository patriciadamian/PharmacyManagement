#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

using namespace std;

int nameSort(const Medicine& s1, const Medicine& s2) {

    if (s1.getName() < s2.getName())
        return true;
    else
        return false;
}

int qtySort(const Medicine& s1, const Medicine& s2) {

    if (s1.getQty() < s2.getQty())
        return true;
    else
        return false;
}

int typeSort(const Medicine& s1, const Medicine& s2) {

    if (s1.getType() < s2.getType())
        return true;
    else
        return false;
}




MainWindow::MainWindow(auto_ptr<MedicineController> ctrl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    initGUI();
    this->ctrl = ctrl;
    reload();
}

void MainWindow::initGUI() {
    //
    //General layout of the window
    //
    QHBoxLayout* layout = new QHBoxLayout(this);


    QWidget* leftWidget = new QWidget();
    QVBoxLayout* lLeft = new QVBoxLayout(leftWidget);

    QLabel* lbl = new QLabel("Main");
    lLeft->addWidget(lbl);
    medicineList = new QListWidget();
    QObject::connect(medicineList, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChaged()));
    lLeft->addWidget(medicineList);

    QWidget* rightWidget = new QWidget();
    QVBoxLayout* lRight = new QVBoxLayout(rightWidget);

    lbl = new QLabel("Id");
    lRight->addWidget(lbl);
    txtId = new QLineEdit();
    lRight->addWidget(txtId);

    lbl = new QLabel("Name");
    lRight->addWidget(lbl);
    txtName = new QLineEdit();
    lRight->addWidget(txtName);

    lbl = new QLabel("Type");
    lRight->addWidget(lbl);
    txtType = new QLineEdit();
    lRight->addWidget(txtType);

    lbl = new QLabel("Quantity");
    lRight->addWidget(lbl);
    txtQty = new QLineEdit();
    lRight->addWidget(txtQty);

    QPushButton* btnAdd = new QPushButton("Add");
    QObject::connect(btnAdd, SIGNAL(clicked()), this, SLOT(addMedicine()));
    QObject::connect(btnAdd,SIGNAL(clicked()),this,SLOT(reload()));
    lRight->addWidget(btnAdd);

    QPushButton* btnUpdate = new QPushButton("Update");
    QObject::connect(btnUpdate, SIGNAL(clicked()), this, SLOT(updateMedicine()));
    QObject::connect(btnUpdate,SIGNAL(clicked()),this,SLOT(reload()));
    lRight->addWidget(btnUpdate);

    QPushButton* btnRemove = new QPushButton("Remove");
    QObject::connect(btnRemove, SIGNAL(clicked()), this, SLOT(removeMedicine()));
    QObject::connect(btnRemove,SIGNAL(clicked()),this,SLOT(reload()));
    lRight->addWidget(btnRemove);

    QPushButton* btnUndo = new QPushButton("Undo");
    QObject::connect(btnUndo,SIGNAL(clicked()),this,SLOT(undo()));
    QObject::connect(btnUndo,SIGNAL(clicked()),this,SLOT(reload()));
    lRight->addWidget(btnUndo);

    QPushButton* btnFN = new QPushButton("Filter by name");
    QObject::connect(btnFN,SIGNAL(clicked()),this,SLOT(filterName()));
    lRight->addWidget(btnFN);

    QPushButton* btnFT = new QPushButton("Filter by type");
    QObject::connect(btnFT,SIGNAL(clicked()),this,SLOT(filterType()));
    lRight->addWidget(btnFT);

    QPushButton* btnFQ = new QPushButton("Filter by quantity");
    QObject::connect(btnFQ,SIGNAL(clicked()),this,SLOT(filterQty()));
    lRight->addWidget(btnFQ);

    QPushButton* btnSN = new QPushButton("Sort by name");
    QObject::connect(btnSN,SIGNAL(clicked()),this,SLOT(sortName()));
    lLeft->addWidget(btnSN);

    QPushButton* btnSQ = new QPushButton("Sort by quantity");
    QObject::connect(btnSQ,SIGNAL(clicked()),this,SLOT(sortQty()));
    lLeft->addWidget(btnSQ);

    QPushButton* btnST = new QPushButton("Sort by type");
    QObject::connect(btnST,SIGNAL(clicked()),this,SLOT(sortType()));
    lLeft->addWidget(btnST);

    QPushButton* btnR = new QPushButton("Restore");
    QObject::connect(btnR,SIGNAL(clicked()),this,SLOT(reload()));
    lLeft->addWidget(btnR);

    layout->addWidget(leftWidget);
    layout->addWidget(rightWidget);
}

void MainWindow::addMedicine()
{
    try {
        ctrl->addMedicine(txtId->text().toInt(), txtName->text().toStdString(), txtType->text().toStdString(), txtQty->text().toInt());
    } catch(const ControllerException& ve) {
        QMessageBox::information(this, "Warning", ve.what());
    }
}

int MainWindow::getFirstSelectedIndex() {
    QModelIndexList indexes = medicineList->selectionModel()->selectedIndexes();
    if (indexes.size()==0) {
        return -1;
    }
    return indexes.at(0).row();

}

void MainWindow::updateMedicine()
{
    try {
        ctrl->updateMedicine(txtId->text().toInt(), txtName->text().toStdString(), txtType->text().toStdString(), txtQty->text().toInt());
        reload();
    } catch(const ControllerException& e) {
        if (QMessageBox::Yes== QMessageBox::question(this, "Warning", "No product with this ID. Want to add?",QMessageBox::Yes,QMessageBox::No)) {
            ctrl->addMedicine(txtId->text().toInt(), txtName->text().toStdString(), txtType->text().toStdString(), txtQty->text().toInt());
            reload();
        }
    } catch (const ValidatorException& ve) {
        QMessageBox::information(this, "Warning", ve.what());
    }
}


void MainWindow::removeMedicine()
{
    try {
        ctrl->removeMedicine(txtId->text().toInt());
        reload();
        txtId->clear();
        txtType->clear();
        txtName->clear();
        txtQty->clear();
    } catch(const ControllerException& ve) {
        QMessageBox::information(this, "Warning", ve.what());
    }
}

void MainWindow::sortName()
{
    medicineList->clear();
    vector<Medicine> all = ctrl->sortMedicine(nameSort);
    if(all.size() == 0)
        QMessageBox::information(this, "Warning", "Empty list");
    else
    for (unsigned i = 0;i < all.size();i++) {
        Medicine s = all[i];
        QString str = QString::number(s.getId());
        str.append(". ");
        str.append(QString::fromStdString(s.getName()));
        str.append(" ");
        str.append(QString::fromStdString(s.getType()));
        str.append(" ");
        str.append(QString::number(s.getQty()));
        medicineList->addItem(str);
    }
}




void MainWindow::sortQty()
{
    medicineList->clear();
    vector<Medicine> all = ctrl->sortMedicine(qtySort);
    if(all.size() == 0)
        QMessageBox::information(this, "Warning", "Empty list");
    else
    for (unsigned i = 0;i < all.size();i++) {
        Medicine s = all[i];
        QString str = QString::number(s.getId());
        str.append(". ");
        str.append(QString::fromStdString(s.getName()));
        str.append(" ");
        str.append(QString::fromStdString(s.getType()));
        str.append(" ");
        str.append(QString::number(s.getQty()));
        medicineList->addItem(str);
    }
}

void MainWindow::sortType()
{
    medicineList->clear();
    vector<Medicine> all = ctrl->sortMedicine(typeSort);
    if(all.size() == 0)
        QMessageBox::information(this, "Warning", "Empty list");
    else
    for (unsigned i = 0;i < all.size();i++) {
        Medicine s = all[i];
        QString str = QString::number(s.getId());
        str.append(". ");
        str.append(QString::fromStdString(s.getName()));
        str.append(" ");
        str.append(QString::fromStdString(s.getType()));
        str.append(" ");
        str.append(QString::number(s.getQty()));
        medicineList->addItem(str);
    }
}

void MainWindow::filterName()
{
    string name = txtName->text().toStdString();
    vector<Medicine> all = ctrl->filterName(name);

    if(all.size() == 0)
        QMessageBox::information(this, "Warning", "Empty list");
    else {
        medicineList->clear();
    for (unsigned i = 0;i < all.size();i++) {
        Medicine s = all[i];
        QString str = QString::number(s.getId());
        str.append(". ");
        str.append(QString::fromStdString(s.getName()));
        str.append(" ");
        str.append(QString::fromStdString(s.getType()));
        str.append(" ");
        str.append(QString::number(s.getQty()));
        medicineList->addItem(str);
    }
    }
}

void MainWindow::filterType()
{
    string type = txtType->text().toStdString();
    vector<Medicine> all = ctrl->filterType(type);

    if(all.size() == 0)
        QMessageBox::information(this, "Warning", "Empty list");
    else {
        medicineList->clear();
    for (unsigned i = 0;i < all.size();i++) {
        Medicine s = all[i];
        QString str = QString::number(s.getId());
        str.append(". ");
        str.append(QString::fromStdString(s.getName()));
        str.append(" ");
        str.append(QString::fromStdString(s.getType()));
        str.append(" ");
        str.append(QString::number(s.getQty()));
        medicineList->addItem(str);
    }
    }
}

void MainWindow::filterQty()
{
    int qty = txtQty->text().toInt();
    vector<Medicine> all = ctrl->filterQty(qty);

    if(all.size() == 0)
        QMessageBox::information(this, "Warning", "Empty list");
    else {
        medicineList->clear();
    for (unsigned i = 0;i < all.size();i++) {
        Medicine s = all[i];
        QString str = QString::number(s.getId());
        str.append(". ");
        str.append(QString::fromStdString(s.getName()));
        str.append(" ");
        str.append(QString::fromStdString(s.getType()));
        str.append(" ");
        str.append(QString::number(s.getQty()));
        medicineList->addItem(str);
    }
    }
}

void MainWindow::reload() {
    medicineList->clear();
    vector<Medicine> all = ctrl->getAll();

    if(all.size() == 0)
        QMessageBox::information(this, "Warning", "Empty list");
    else {
        medicineList->clear();
    for (unsigned i = 0;i < all.size();i++) {
        Medicine s = all[i];
        QString str = QString::number(s.getId());
        str.append(". ");
        str.append(QString::fromStdString(s.getName()));
        str.append(" ");
        str.append(QString::fromStdString(s.getType()));
        str.append(" ");
        str.append(QString::number(s.getQty()));
        medicineList->addItem(str);
    }
    }
}

void MainWindow::selectionChaged() {
    int index = getFirstSelectedIndex();

    if (index<0) {
        return;
    }

    vector<Medicine> all = ctrl->getAll();
    Medicine s = all[index];

    txtId->setText(QString::number(s.getId()));
    txtName->setText(QString::fromStdString(s.getName()));
    txtType->setText(QString::fromStdString(s.getType()));
    txtQty->setText(QString::number(s.getQty()));
}

void MainWindow::undo() {
    try {
        ctrl->undo();
    } catch(const ControllerException& ve) {
        QMessageBox::information(this, "Warning", ve.what());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
