#include "Passenger.h"

Passenger::Passenger(std::string firstname, std::string lastname) {
    this->firstname = firstname;
    this->lastname = lastname;
}

const std::string &Passenger::getFirstname() const {
    return firstname;
}

const std::string &Passenger::getLastname() const {
    return lastname;
}

bool Passenger::operator<(const Passenger &rhs) const {
    /* TODO */
    int i = 0;
    while(rhs.lastname[i] != '\0' && lastname[i] != '\0'){
        if(rhs.lastname[i] > lastname[i]){
            return true;
        }
        else if(rhs.lastname[i] < lastname[i]){
            return false;
        }
        else
            i++;
    }
    int j = 0;
    while(rhs.firstname[j] != '\0' && firstname[j] != '\0'){
        if(rhs.firstname[j] > firstname[j]){
            return true;
        }
        else if(rhs.firstname[j] < firstname[j]){
            return false;
        }
        else
            j++;
    }
    
}

bool Passenger::operator>(const Passenger &rhs) const {
    return rhs < *this;
}

bool Passenger::operator==(const Passenger &rhs) const {
    return firstname == rhs.firstname && lastname == rhs.lastname;
}

bool Passenger::operator!=(const Passenger &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Passenger &passenger) {
    os << "Passenger(firstname: " << passenger.firstname;
    os << ", lastname: " << passenger.lastname << ")";
    return os;
}
