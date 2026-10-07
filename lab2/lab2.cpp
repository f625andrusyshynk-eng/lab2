#include <iostream> 
#include <cstring>
using namespace std;

class Worker {
private: 
    int id;
    char* name;
    double salary;
    int experience;
    int workedDays;
    int totalDays;
    double earnings;
    double tax;

public: 
    Worker() 
    { 
        id = 0; 
        name = new char[1];
        name[0] = '\0';
        salary = 0.0;
        experience = 0;
        workedDays = 0;
        totalDays = 22;
        earnings = 0.0;
        tax = 0.0; 
    }

    Worker(const Worker& other)
    {
        id = other.id;
        salary = other.salary;
        experience = other.experience;
        workedDays = other.workedDays;
        totalDays = other.totalDays;
        earnings = other.earnings;
        tax = other.tax;
        
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }

    Worker& operator=(const Worker& other)
    {
        if (this != &other)
        {
            delete[] name;

            id = other.id;
            salary = other.salary;
            experience = other.experience;
            workedDays = other.workedDays;
            totalDays = other.totalDays;
            earnings = other.earnings;
            tax = other.tax;

            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
        return *this;
    }

    ~Worker() 
    {
        delete[] name;
    }

    void set(int workerId, const char* workerName, double baseSalary, int exp, int days, int maxDays)
    {
        id = workerId;
        
        delete[] name;
        name = new char[strlen(workerName) + 1];
        strcpy(name, workerName);

        salary = baseSalary;
        experience = exp;
        workedDays = days;
        totalDays = maxDays;
        calculate();
    }

    void calculate()
    {
        if (totalDays > 0)
        {
            double base = (salary / totalDays) * workedDays;
            double bonus = base * (experience * 0.01);
            earnings = base + bonus;
            tax = earnings * 0.195;
        }
    }

    void setSalary(double newSalary)
    {
        salary = newSalary;
        calculate();
    }

    void setDays(int newDays)
    {
        workedDays = newDays;
        calculate();
    }

    int getId()
    {
        return id;
    }

    void show()
    {
        cout << "ID: " << id << " | Name: " << name << endl;
        cout << "Base Salary: " << salary << " | Experience: " << experience << " years" << endl;
        cout << "Days: " << workedDays << "/" << totalDays << endl;
        cout << "Earnings: " << earnings << " | Tax: " << tax << endl;
        cout << "Net Payout: " << (earnings - tax) << endl;
        cout << "-----------------------------------" << endl;
    }
};

class List {
private: 
    Worker items[20];
    int count;

public: 
    List() 
    { 
        count = 0; 
    }

    ~List() {}

    void add(Worker w)
    {
        if (count < 20)
        {
            items[count] = w;
            count++;
        }
    }

    void edit(int id, double newSalary, int newDays)
    {
        for (int i = 0; i < count; i++)
        {
            if (items[i].getId() == id)
            {
                items[i].setSalary(newSalary);
                items[i].setDays(newDays);
                return;
            }
        }
    }

    void remove(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (items[i].getId() == id)
            {
                for (int j = i; j < count - 1; j++)
                {
                    items[j] = items[j + 1];
                }
                count--;
                return;
            }
        }
    }

    void find(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (items[i].getId() == id)
            {
                items[i].show();
                return;
            }
        }
    }

    void showAll()
    {
        for (int i = 0; i < count; i++)
        {
            items[i].show();
        }
    }
};

int main() {
    List list;
    Worker w1, w2;

    w1.set(101, "John Smith", 20000, 5, 22, 22);
    w2.set(102, "Alex Brown", 18000, 3, 20, 22);

    list.add(w1);
    list.add(w2);

    list.showAll();

    list.edit(102, 19000, 22);
    list.find(102);
    list.remove(101);

    list.showAll();

    return 0;
}
