#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include <QMessageBox>
#include "FileRepository.h"
#include "Medicine.h"
#include "MedicineValidator.h"
#include <algorithm>
#include <memory>

using namespace std;

typedef int(*cmp)(const Medicine&, const Medicine&);

class ControllerException:public std::exception {
private:
	string message;
public:
	 ControllerException(string message){
		this->message = message;
	}
	virtual const char* what() const throw(){
		return message.c_str();
	}
	virtual ~ ControllerException()throw(){

	}
};

class MedicineController {

    private:
        auto_ptr<Repository<Medicine> > repo;
        vector<int> undo_switch;
		vector<Medicine> last_medicine;

    public:

        MedicineController(auto_ptr<Repository<Medicine> > repo);
		void addMedicine(int id, string name, string type, int qty) throw(const ControllerException&);
		void removeMedicine(int id);
		void updateMedicine(int id, string name, string type, int qty);
		vector<Medicine> sortMedicine(cmp compare);
		vector<Medicine> filterName(string name);
		vector<Medicine> filterType(string type);
		vector<Medicine> filterQty(int qty);
		vector<Medicine> getAll();
        void undo();
		virtual ~MedicineController();

};

#endif // CONTROLLER_H_INCLUDED
