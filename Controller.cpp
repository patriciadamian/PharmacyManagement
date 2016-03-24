#include "Controller.h"

MedicineController::MedicineController(auto_ptr<Repository<Medicine> > repo) {
    this->repo = move(repo);
}

void MedicineController::addMedicine(int id, string name, string type, int qty) throw(const ControllerException&) {
    Medicine e(id, name, type, qty);
	MedicineValidator v;
	try {
		v.validateMedicine(e);
        repo->add(e);
	} catch(const ValidatorException& ve) {
        throw ControllerException(ve.what());
    } catch(const RepositoryException& re) {
        throw ControllerException(re.what());
    }

	this->undo_switch.push_back(1);
    this->last_medicine.push_back(e);
}

void MedicineController::removeMedicine(int id) {

	Medicine me;
	vector<Medicine> all = repo->getAll();

	for_each(all.begin(), all.end(), [&id, &me](Medicine m) {
    if(m.getId() == id)
        me = m;
    });

	this->last_medicine.push_back(me);

	try {
        repo->del(id);
	} catch(const RepositoryException& e) {
		throw ControllerException(e.what());
	}

	this->undo_switch.push_back(2);
}

void MedicineController::updateMedicine(int id, string name, string type, int qty) {

	Medicine me;
	vector<Medicine> all = repo->getAll();

	for_each(all.begin(), all.end(), [&id, &me](Medicine m) {
    if(m.getId() == id)
        me = m;
    });

	this->last_medicine.push_back(me);

	Medicine e(id, name, type, qty);
	MedicineValidator v;
	try {
		v.validateMedicine(e);
        repo->mod(id, e);
	} catch(const RepositoryException& e) {
		throw ControllerException(e.what());
	}

	this->undo_switch.push_back(3);
}

vector<Medicine> MedicineController::sortMedicine(cmp compare){

	vector<Medicine> all = repo->getAll();
    sort(all.begin(), all.end(), compare);
    return all;

}

vector<Medicine> MedicineController::filterName(string name){

	vector<Medicine> all = repo->getAll();
	vector<Medicine> res;

	for_each(all.begin(), all.end(), [&res, &name](Medicine m) {
    if(m.getName() == name)
        res.push_back(m);
    });

    return res;
}

vector<Medicine> MedicineController::filterType(string type){

	vector<Medicine> all = repo->getAll();
	vector<Medicine> res;

	for_each(all.begin(), all.end(), [&res, &type](Medicine m) {
    if(m.getType() == type)
        res.push_back(m);
    });

    return res;
}

vector<Medicine> MedicineController::filterQty(int qty){

	vector<Medicine> all = repo->getAll();
	vector<Medicine> res;

	for_each(all.begin(), all.end(), [&res, &qty](Medicine m) {
    if(m.getQty() == qty)
        res.push_back(m);
    });

    return res;
}

vector<Medicine> MedicineController::getAll(){
    return repo->getAll();
}

void MedicineController::undo() {
    auto dim1 = undo_switch.size() - 1;
	auto dim2 = last_medicine.size() - 1;

    if(undo_switch.size() == 0) {

        throw ControllerException("Nothing to undo! ");

    } else if (undo_switch[dim1] == 1) {

		repo->del(last_medicine[dim2].getId());
        undo_switch.pop_back();
		last_medicine.pop_back();

    } else if (undo_switch[dim1] == 2) {

		repo->add(last_medicine[dim2]);
        undo_switch.pop_back();
		last_medicine.pop_back();

    } else if (undo_switch[dim1] == 3) {

		repo->mod(last_medicine[dim2].getId(), last_medicine[dim2]);
        undo_switch.pop_back();
		last_medicine.pop_back();

    } else {

        throw ControllerException("Nothing to undo! ");

    }
}

MedicineController::~MedicineController() {
    //delete repo;
}

