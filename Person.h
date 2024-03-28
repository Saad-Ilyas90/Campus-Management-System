//
// Created by basit on 12/18/2023.
//

#ifndef OOP_NEW_PROJECT_PERSON_H
#define OOP_NEW_PROJECT_PERSON_H
using namespace std;

#include <string>

class Person {
protected:
    string name;
    string fname; // Added fname
    string email;
    string id;
public:
    Person(const string& name, const string& email, const string& id)
            : name(name), email(email), id(id) {}

    virtual ~Person() {}

    // Accessor methods
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getID() const { return id; }

    // Setter methods
    void setName(const string& name) { this->name = name; }
    void setEmail(const string& email) { this->email = email; }
    void setFName(const string& fname) { this->fname = fname; }

    // Getter method
    string getFName() const { return fname; }

    // Virtual methods to be overridden by derived classes
    virtual void printDetails() const = 0; // Pure virtual function makes this class Abstract
};
#endif //OOP_NEW_PROJECT_PERSON_H
