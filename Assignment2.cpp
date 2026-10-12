#include <iostream>
#include <string>
using namespace std;

class ParkingSystem
{
    int n;
    string *vehicleType;
    string *vehicleSize;
    string *slotType;
    string *slotSize;
    int *assignment;
    int *bestAssignment;
    int maxAllotted;

public:
    ParkingSystem(int size)
    {
        n = size;
        vehicleType = new string[n];
        vehicleSize = new string[n];
        slotType = new string[n];
        slotSize = new string[n];
        assignment = new int[n];
        bestAssignment = new int[n];

        maxAllotted = 0;

        for (int i = 0; i < n; i++)
        {
            assignment[i] = -1;
            bestAssignment[i] = -1;
        }
    }

    void input()
    {
        cout << "Enter vehicle info:\n";
        for (int i = 0; i < n; i++)
        {
            cout << "Vehicle" << i + 1 << endl;
            cout << "Type(car/bike):";
            cin >> vehicleType[i];
            cout << "Size (small/medium/large): ";
            cin >> vehicleSize[i];
        }

        cout << "\nEnter parking slot:\n";

        for (int i = 0; i < n; i++)
        {
            cout << "\nSlot " << i + 1 << endl;
            cout << "Type (car/bike): ";
            cin >> slotType[i];
            cout << "Size (small/medium/large): ";
            cin >> slotSize[i];
        }
    }

    int sizeValue(string size)
    {
        if (size == "small")
        {
            return 1;
        }
        if (size == "medium")
        {
            return 2;
        }
        return 3;
    }

    bool canAllot(int vehicle, int slot)
    {
        for (int i = 0; i < vehicle; i++)
        {
            if (assignment[i] == slot)
                return false;
        }

        if (vehicleType[vehicle] != slotType[slot])
            return false;

        if (sizeValue(vehicleSize[vehicle]) > sizeValue(slotSize[slot]))
            return false;
        return true;
    }

    void CSP(int vehicle, int allotted)
    {
        if (vehicle == n)
        {
            if (allotted > maxAllotted)
            {
                maxAllotted = allotted;
                for (int i = 0; i < n; i++)
                {
                    bestAssignment[i] = assignment[i];
                }
            }
            return;
        }

        for (int slot = 0; slot < n; slot++)
        {
            if (canAllot(vehicle, slot))
            {
                assignment[vehicle] = slot;
                CSP(vehicle + 1, allotted + 1);
                assignment[vehicle] = -1;
            }
        }

        assignment[vehicle] = -1;
        CSP(vehicle + 1, allotted);
    }

    void display()
    {
        CSP(0, 0);
        cout << "Allocation" << endl;

        int unallotted = 0;

        for (int i = 0; i < n; i++)
        {
            if (bestAssignment[i] != -1)
            {
                cout << "Vehicle " << i + 1 << " (" << vehicleType[i] << ", " << vehicleSize[i] << ")"
                     << "   Slot " << bestAssignment[i] + 1 << " (" << slotType[bestAssignment[i]] << ", " << slotSize[bestAssignment[i]] << ")" << endl;
            }
            else
            {
                cout << "Vehicle " << i + 1 << " (" << vehicleType[i] << ", " << vehicleSize[i] << ")" << "    Not allotted" << endl;
                unallotted++;
            }
        }

        cout << "\nVehicles allotted: " << maxAllotted << endl;

        cout << "Vehicles not allotted: " << unallotted << endl;
    }
};

int main()
{
    int n;
    cout << "Enter number of vehicles";
    cin >> n;

    ParkingSystem obj(n);
    obj.input();
    obj.display();

    return 0;
}