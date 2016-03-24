#ifndef MEDICINE_H
#define MEDICINE_H

#include <string>
#include <iostream>
using namespace std;


class PharmacyException {
public:
	PharmacyException(string& msg) {
		this->msg = msg;
	}
	const string& getMsg() const {
		return msg;
	}

private:
	string msg;
};


class Medicine {
public:

	Medicine();
	Medicine(int id, string name, string type, int qty);
	Medicine(const Medicine &m);

    int getId() const;

    string getName() const;

	void setName(const string name);

    string getType() const;

	void setType(const string name);

    int getQty() const;

	void setQty(int quantity);

	bool operator ==(const Medicine m) const;

	bool operator !=(const Medicine m) const;

	friend ostream& operator<<(ostream& stream, const Medicine& med);

	friend istream& operator>>(istream& stream, Medicine& med);

private:

    int id;
	string name;
	string type;
	int qty;

};

#endif // MEDICINE_H
