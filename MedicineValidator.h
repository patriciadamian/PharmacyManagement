#ifndef MEDICINEVALIDATOR_H_INCLUDED
#define MEDICINEVALIDATOR_H_INCLUDED

class ValidatorException: public PharmacyException {
public:
	ValidatorException(string msg) :
			PharmacyException(msg) {
	}

    virtual const char* what() const throw(){
		return getMsg().c_str();
	}

};

class MedicineValidator {

    public:

		void validateMedicine(const Medicine& m) throw (const ValidatorException&) {

                if (m.getId() < 0) {
                    throw ValidatorException("Id is negative.");
                }

                if (m.getName().length() == 0) {
                    throw ValidatorException("Name is empty.");
                }

                if (m.getType().length() == 0) {
                    throw ValidatorException("Type is empty.");
                }

                if (m.getQty() <= 0) {
                    throw ValidatorException("Quantity is null/negative. ");
                }
        }

};

#endif // MEDICINEVALIDATOR_H_INCLUDED
