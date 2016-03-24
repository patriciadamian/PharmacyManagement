#include "FileRepository.h"
#include "MedicineValidator.h"

#include <fstream>

void FileRepository::writeToFile() {
    ofstream out(this->filename.c_str());

    if (!out.is_open()) {
        throw RepositoryException("Unable to write to file. ");
    }

	vector<Medicine>::iterator it = elems->begin();
	while(it != elems->end()) {
		out << *it << endl;
		it++;
	}

	out.close();
}

void FileRepository::readFromFile() {

	ifstream f(this->filename.c_str());
	if (!f.is_open()) {
		throw RepositoryException("Unable to read from file. ");
	}

	MedicineValidator v;
	Medicine e;

    if(f.peek() == std::ifstream::traits_type::eof()) {
        f.close();
    } else {
    	while(f >> e) {
            try {
				v.validateMedicine(e);
                elems->push_back(e);
            } catch(const ValidatorException& ve) {
                throw ValidatorException(ve);
            }
        }

	f.close();
	}
}


void FileRepository::add(Medicine e) {

	Medicine m;
		if (getById(e.getId()) != m) {
			throw RepositoryException("Object already in repo!");
		}

		elems->push_back(e);

	writeToFile();
}

void FileRepository::del(int id) {

	Medicine m;

        if (getById(id) == m) {
			throw RepositoryException("Object not found!");
		}

        unsigned i = 0;

		for (vector<Medicine>::const_iterator it = elems->begin(); it != elems->end(); ++it) {
            if((*it).getId() == id){
                elems->erase(elems->begin() + i);
                writeToFile();
                break;
            }

            i++;
        }

    writeToFile();
}

void FileRepository::mod(int id, Medicine e) {

	Medicine m;

		if (getById(id) == m) {
			throw RepositoryException("Object not found!");
		}

        unsigned i = 0;

		for (vector<Medicine>::const_iterator it = elems->begin(); it != elems->end(); ++it) {
            if((*it).getId() == id)
                elems->at(i) = e;
            i++;
        }

    writeToFile();
}

Medicine FileRepository::get(unsigned pos) throw(const RepositoryException&) {

        if (pos > elems->size()) {
            throw new RepositoryException("Invalid position! ");
        }

        return elems->at(pos);
}

Medicine FileRepository::getById(int id) {
	Medicine m;

        unsigned i = 0;

		for (vector<Medicine>::const_iterator it = elems->begin(); it != elems->end(); ++it) {
            if((*it).getId() == id)
                return elems->at(i);
            ++i;
        }

		return m;
}

vector<Medicine> FileRepository::getAll() {
	vector<Medicine> rez;

    copy(elems->begin(), elems->end(), back_inserter(rez));

    return rez;
}


