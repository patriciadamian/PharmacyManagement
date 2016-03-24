#ifndef INMEMORYREPOSITORY_H_INCLUDED
#define INMEMORYREPOSITORY_H_INCLUDED

#include "Medicine.h"
#include "Repository.h"

class InMemoryRepository:public Repository<Medicine> {

	vector<Medicine>* elems;

public:

	InMemoryRepository() {
		elems = new vector<Medicine>;
	}

	virtual ~InMemoryRepository() {
		delete elems;
	}

	void add(Medicine e) {

		Medicine m;
		if (getById(e.getId()) != m) {
			throw RepositoryException("Object already in repo!");
		}

		elems->push_back(e);
	}

	void del(int id) {
		Medicine m;

		if (getById(id) == m) {
			throw RepositoryException("Object not found!");
		}

		for (unsigned i = 0; i < elems->size(); i++) {
            if (id == get(i).getId()) {
                elems->erase(elems->begin() + i);
            }
        }
	}

	void mod(int id, Medicine e) {
		Medicine m;

		if (getById(id) == m) {
			throw RepositoryException("Object not found!");
		}

		for (unsigned i = 0; i < elems->size(); i++) {
            if (id == get(i).getId()) {
                elems->at(i) = e;
            }
        }
    }

	Medicine get(int pos) throw(const RepositoryException&) {

		if (pos < 0 || pos >= size()) {
            throw new RepositoryException("Invalid position! ");
        }

        return elems->at(pos);

	}

	Medicine getById(int id) {
		Medicine m;
		for (unsigned i = 0; i < elems->size(); i++) {
			if (id == elems->at(i).getId()) {
                return elems->at(i);
			}
		}
		return m;
	}

	vector<Medicine> getAll() {
		vector<Medicine> rez;
        copy(elems->begin(), elems->end(), back_inserter(rez));
        return rez;
    }

    int size() {
        return elems->size();
    }

};

#endif // INMEMORYREPOSITORY_H_INCLUDED
