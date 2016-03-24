#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
using namespace std;

class RepositoryException:public std::exception
{
private:
	string message;
public:
	 RepositoryException(string message){
		this->message = message;
	}
	virtual const char* what() const throw(){
		return message.c_str();
	}
	virtual ~ RepositoryException()throw(){

	}
};

template <typename T>
class Repository {

	vector<T>* elems;

public:
    Repository() {
        elems = new vector<T>;
    }
	virtual void add(T t)=0;
	virtual void del(int id)=0;
	virtual void mod(int id, T t)=0;
	virtual T get(int pos)throw(const RepositoryException&)=0;
	virtual vector<T> getAll()=0;
	virtual int size()=0;
	virtual ~Repository() {
        delete elems;
	}
};

#endif // REPOSITORY_H
