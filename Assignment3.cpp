// Rules:
// lT+sW = shortGreen
// lT+mW = mediumGreen
// lT+lW = mediumGreen
// hT+sW = mediumGreen
// hT+lW = longGreen
// hT+mW = longGreen
// mT+mW = mediumGreen
// mT+lW = longGreen
// mT+sW = shortGreen

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class TrafficSystem
{
    int n = 4;

    string direction[4] = {"North", "South", "East", "West"};

    int vehicles[4];
    int waitingTime[4];

    int greenTime[4];
    int yellowTime[4];
    int redTime[4];

    // Membership function
    double value(double x, double a, double b, double c)
    {
        if(x <= a)
            return 0;

        if(x >= c)
            return 0;

        if(x == b)
            return 1;

        if(x < b)
            return (x - a) / (b - a);

        return (c - x) / (c - b);
    }

    // Calculate green time using fuzzy rules
    int calculateGreen(int i)
    {
        if(vehicles[i] == 0)
            return 0;

        // Traffic membership
        double low = value(vehicles[i], 0, 10, 30);
        double medium = value(vehicles[i], 10, 30, 50);
        double high = value(vehicles[i], 30, 50, 70);

        // Waiting time membership
        double shortWait = value(waitingTime[i], 0, 10, 30);
        double mediumWait = value(waitingTime[i], 20, 40, 60);
        double longWait = value(waitingTime[i], 40, 60, 100);

        // Fuzzy rules
        double shortGreen =
            max(min(low, shortWait),
                min(medium, shortWait));

        double mediumGreen =
            max(max(min(low, mediumWait),
                    min(low, longWait)),
                max(min(high, shortWait),
                    min(medium, mediumWait)));

        double longGreen =
            max(min(high, mediumWait),
                max(min(high, longWait),
                    min(medium, longWait)));

        // Select highest membership
        if(longGreen >= mediumGreen && longGreen >= shortGreen)
            return 50;

        if(mediumGreen >= shortGreen)
            return 35;

        return 20;
    }

public:

    // Input traffic details
    void input()
    {
        cout << "\nEnter initial traffic details:\n";

        for(int i = 0; i < n; i++)
        {
            cout << "\n" << direction[i] << ":\n";

            cout << "No of vehicles: ";
            cin >> vehicles[i];

            cout << "Waiting time: ";
            cin >> waitingTime[i];
        }
    }

    // Calculate green, yellow and red times
    void calculateSignals()
    {
        int totalGreen = 0;

        for(int i = 0; i < n; i++)
        {
            greenTime[i] = calculateGreen(i);

            // Fixed yellow time
            yellowTime[i] = 5;

            totalGreen += greenTime[i];
        }

        // Maximum cycle time = 200 seconds
        // Reserve 20 seconds for yellow
        while(totalGreen > 180)
        {
            for(int i = 0; i < n; i++)
            {
                if(greenTime[i] > 20)
                {
                    greenTime[i] -= 5;
                    totalGreen -= 5;

                    if(totalGreen <= 180)
                        break;
                }
            }
        }

        // Red time = remaining cycle time
        for(int i = 0; i < n; i++)
        {
            redTime[i] = 200 - greenTime[i] - yellowTime[i];
        }
    }

    // Green bar
    string greenBar(int time)
    {
        int length = time / 2;

        string bar = "\033[32m";

        for(int i = 0; i < length; i++)
            bar += "█";

        bar += "\033[0m";

        return bar;
    }

    // Yellow bar
    string yellowBar(int time)
    {
        int length = time;

        string bar = "\033[33m";

        for(int i = 0; i < length; i++)
            bar += "█";

        bar += "\033[0m";

        return bar;
    }

    // Red bar
    string redBar(int time)
    {
        int length = time / 5;

        string bar = "\033[31m";

        for(int i = 0; i < length; i++)
            bar += "█";

        bar += "\033[0m";

        return bar;
    }

    // Display results
    void display(int cycle)
    {
        cout << "CYCLE " << cycle << "\n";

        cout << "Direction\tVehicles\tWaiting\tGreen\tYellow\tRed\n";

        for(int i = 0; i < n; i++)
        {
            cout << direction[i] << "\t\t"
                 << vehicles[i] << "\t\t"
                 << waitingTime[i] << "\t"
                 << greenTime[i] << "s\t"
                 << yellowTime[i] << "s\t"
                 << redTime[i] << "s\n";

            // All three bars in the same row
            cout << "\t\t\t\t"
                 << greenBar(greenTime[i])
                 << " "
                 << yellowBar(yellowTime[i])
                 << " "
                 << redBar(redTime[i])
                 << "\n";
        }
    }

    // Update traffic after each cycle
    void updateTraffic()
    {
        cout << "\nUpdating traffic\n";

        for(int i = 0; i < n; i++)
        {
            int newVehicles;

            cout << "New vehicles at "
                 << direction[i] << ": ";

            cin >> newVehicles;

            // One vehicle passes every 2 seconds
            int vehiclesPassed = greenTime[i] / 2;

            vehicles[i] =
                vehicles[i] - vehiclesPassed + newVehicles;

            if(vehicles[i] < 0)
                vehicles[i] = 0;

            // Increase waiting time if vehicles remain
            if(vehicles[i] > 0)
                waitingTime[i] += 10;
            else
                waitingTime[i] = 0;
        }
    }

    // Run multiple cycles
    void run(int cycles)
    {
        for(int i = 1; i <= cycles; i++)
        {
            calculateSignals();

            display(i);

            if(i < cycles)
                updateTraffic();
        }
    }
};

int main(){
    TrafficSystem obj;
    obj.input();
    int cycles;
    cout << "\nEnter number of cycles: ";
    cin >> cycles;
    obj.run(cycles);
    return 0;
}