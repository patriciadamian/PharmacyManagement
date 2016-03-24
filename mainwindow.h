#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidget>
#include "Medicine.h"
#include "Repository.h"
#include "InMemoryRepository.h"
#include "FileRepository.h"
#include "Controller.h"
using namespace std;

class ConsoleException:public std::exception {
private:
    string message;
public:
     ConsoleException(string message){
        this->message = message;
    }
    virtual const char* what() const throw(){
        return message.c_str();
    }
    virtual ~ ConsoleException()throw(){

    }
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(auto_ptr<MedicineController> ctrl, QWidget *parent = 0);
    ~MainWindow();


private:
    void setupUi();
        void initGUI();
        Ui::MainWindow *ui;
        auto_ptr<MedicineController> ctrl;
        QListWidget* medicineList;
        QLineEdit* txtId;
        QLineEdit* txtName;
        QLineEdit* txtType;
        QLineEdit* txtQty;
        int getFirstSelectedIndex();

private slots:
    void selectionChaged();
    void addMedicine();
    void updateMedicine();
    void removeMedicine();
    void filterName();
    void filterType();
    void filterQty();
    void sortName();
    void sortQty();
    void sortType();
    void undo();
    void reload();

};

#endif // MAINWINDOW_H
