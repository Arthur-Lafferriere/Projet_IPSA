#include <iostream>
#include <string>
using namespace std;

class Person
{
private:
    // Attributs
    string name;
    int age;

public:
    Person()
    {
        name = "";
        age = 0;
    }

    // Methodes
    Person(string name, int age)
    {
        this->name = name;
        this->age = age;
    }

    // Get et Set
    string getName()
    {
        return name;
    }
    int getAge()
    {
        return age;
    }

    void setName(string name)
    {
        this->name = name;
    }
    void setAge(int age)
    {
        this->age = age;
    }

    void saisir()
    {
        cout << "Enter name : ";
        cin >> name;
        cout << "Enter age : ";
        cin >> age;
    }
};

int main()
{
    Person person1;
    cout << "Name and age " << endl;
    person1.saisir();
    cout << endl;
    cout << "Name : " << person1.getName() << " , age = " << person1.getAge() << endl;
    return 0;
}