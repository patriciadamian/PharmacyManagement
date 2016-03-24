#ifndef FILEREPOSITORY_H_INCLUDED
#define FILEREPOSITORY_H_INCLUDED

#include <memory>
#include <iostream>
#include "InMemoryRepository.h"


class FileRepository:public InMemoryRepository {

    string filename;
    auto_ptr<vector<Medicine> > elems;
	void readFromFile();
	void writeToFile();

public:

    FileRepository(string filename) :filename { filename } {
        auto_ptr<vector<Medicine> > aux(new vector<Medicine>);
        elems = move(aux);
        readFromFile();
    }

	void add(Medicine e);

	void del(int id);

	void mod(int id, Medicine e);

	Medicine get(unsigned pos) throw(const RepositoryException&);

	Medicine getById(int id);

	vector<Medicine> getAll();

	virtual ~FileRepository() {
        //delete elems;
    }

};

#endif // FILEREPOSITORY_H_INCLUDED
