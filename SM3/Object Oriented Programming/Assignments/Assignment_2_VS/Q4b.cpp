#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Appointment
{
protected:
    string description;

public:
    Appointment(const string &desc) : description(desc) {}

    virtual ~Appointment() {}

    virtual bool matches(int year, int month, int day) const = 0;

    string getDescription() const { return description; }
};

class Onetime : public Appointment
{
private:
    int appointmentYear, appointmentMonth, appointmentDay;

public:
    Onetime(const string &desc, int year, int month, int day)
        : Appointment(desc), appointmentYear(year), appointmentMonth(month), appointmentDay(day) {}

    bool matches(int year, int month, int day) const override
    {
        return appointmentYear == year && appointmentMonth == month && appointmentDay == day;
    }
};

class Daily : public Appointment
{
public:
    Daily(const string &desc) : Appointment(desc) {}

    bool matches(int, int, int) const override
    {
        return true;
    }
};

class Monthly : public Appointment
{
private:
    int appointmentDay;

public:
    Monthly(const string &desc, int day) : Appointment(desc), appointmentDay(day) {}

    bool matches(int, int, int day) const override
    {
        return appointmentDay == day;
    }
};

int main()
{
    vector<Appointment *> appointments;

    appointments.push_back(new Onetime("See the dentist", 2025, 6, 22));
    appointments.push_back(new Daily("Workout"));
    appointments.push_back(new Monthly("Bill payment", 15));

    int inputYear, inputMonth, inputDay;
    cout << "Enter a date (YYYY MM DD): ";
    cin >> inputYear >> inputMonth >> inputDay;

    if (inputMonth < 1 || inputMonth > 12)
    {
        cout << "Invalid month. Please enter a month between 1 and 12.\n";
        return 1;
    }

    if (inputDay < 1 || inputDay > 31)
    {
        cout << "Invalid day. Please enter a day between 1 and 31.\n";
        return 1;
    }

    cout << "Appointments on " << inputYear << "-" << inputMonth << "-" << inputDay << ":\n";

    bool found = false;
    for (const auto &appointment : appointments)
    {
        if (appointment->matches(inputYear, inputMonth, inputDay))
        {
            cout << "- " << appointment->getDescription() << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No appointments found on this date.\n";
    }

    for (auto appointment : appointments)
    {
        delete appointment;
    }

    return 0;
}