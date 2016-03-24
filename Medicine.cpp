#include "Medicine.h"

Medicine::Medicine() {
    this->id = 0;
	this->name = "none";
	this->type = "none";
	this->qty = 0;
}

Medicine::Medicine(int id, string name, string type, int qty) {
	this->id = id;
	this->name = name;
	this->type = type;
	this->qty = qty;
}

Medicine::Medicine(const Medicine &m) {
    id = m.id;
	name = m.name;
	type = m.type;
	qty = m.qty;
}

int Medicine::getId() const {
    return id;
}

string Medicine::getName() const {
	return name;
}

void Medicine::setName(const string name) {
	this->name = name;
}

string Medicine::getType() const {
	return type;
}

void Medicine::setType(const string type) {
	this->type = type;
}

int Medicine::getQty() const {
	return qty;
}

void Medicine::setQty(int quantity) {
	this->qty = quantity;
}

bool Medicine::operator ==(const Medicine m) const {
	bool check = 1;
	if (name != m.name) check = 0;
	if (type != m.type) check = 0;
	if (qty != m.qty) check = 0;
	return check;
}

bool Medicine::operator !=(const Medicine m) const {
	bool check = 1;
	if (name == m.name)
		if (type == m.type)
			if (qty == m.qty)
				check = 0;
	return check;

}

std::ostream& operator<<(std::ostream& stream, const Medicine& med) {
	stream << med.id << " " << med.name << " " << med.type << " " << med.qty;
	return stream;
}

std::istream& operator>>(std::istream& stream, Medicine& med) {
	stream >> med.id;
	stream >> med.name;
	stream >> med.type;
	stream >> med.qty;
	return stream;
}
