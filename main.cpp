#include <iostream>
#include <utility>
#include "SharedPtr.h"

using namespace std;

class User
{
private:
    string name = "";
    int id = 0;

public:
    void printNameId() noexcept
    {
        cout << "Name: " << this->name << endl;
        cout << "ID: " << this->id << endl;
    }
    void setName(string name) noexcept { this->name = name; }
    void setId(int id) noexcept { this->id = id; }
};

int main()
{
    SharedPtr<User> ptr1(new User());
    {
        ptr1->setName("Mark");
        ptr1->setId(28);
        SharedPtr<User> ptr2 = ptr1; // Shared ownership
        SharedPtr<User> ptr3(new User());
        ptr3 = ptr2;
        ptr3->printNameId();
        ptr2->printNameId();
        ptr1->printNameId();

        SharedPtr<User> ptr4(std::move(ptr2));
        ptr4->printNameId();
        SharedPtr<User> ptr5;
        ptr3->setName("John");
        ptr5 = std::move(ptr3);
        ptr5->printNameId();
        ptr1->printNameId();
        cout << "There are " << ptr1.getRefCount() << " shared pointers" << endl;
    }
    ptr1.reset();
}