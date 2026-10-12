#include <iostream>
using namespace std;

int n = 5;
int adj[20][20] = {};
int col[20];
string name[20];
string clr(int c) {
    if(c == 0) return "\033[41m R \033[0m"; // Red
    if(c == 1) return "\033[42m G \033[0m"; // Green
    if(c == 2) return "\033[44m B \033[0m"; // Blue
    return "\033[43m Y \033[0m";             // Yellow
}


bool safe(int v, int c) {
    for(int i = 0; i < n; i++) {
        if(adj[v][i] == 1 && col[i] == c)
            return false;
    }
    return true;
}

// Backtracking
bool solve(int v) {
    if(v == n)
        return true;
    for(int c = 0; c < 4; c++) {
        if(safe(v, c)) {
            col[v] = c;
            if(solve(v + 1))
                return true;
            col[v] = -1;
        }
    }
    return false;
}

// Display 5-region map
void display() {
    cout << "\n\n             MAHARASHTRA MAP\n\n";
    cout << "                    "<< clr(col[2]) << " " << name[2] << endl;
    cout << "                   /       \\" << endl;
    cout << "          "<< clr(col[0]) << " " << name[0]<< "          "<< clr(col[4]) << " " << name[4] << endl;
    cout << "             |                 |" << endl;
    cout << "          "<< clr(col[1]) << " " << name[1]<< "          "<< clr(col[3]) << " " << name[3] << endl;
    cout << "\nR = Red   G = Green   B = Blue   Y = Yellow\n";
}

int main() {
    cout << "MAHARASHTRA MAP COLORING USING CSP\n\n";
    cout << "Enter 5 regions:\n";
    for(int i = 0; i < n; i++) {
        cout << "Enter region " << i + 1 << ": ";
        cin >> name[i];
        col[i] = -1;
    }

    int e;
    cout << "\nEnter number of neighboring pairs: ";
    cin >> e;
    cout << "Enter pairs using region numbers:\n";
    for(int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        adj[a - 1][b - 1] = 1;
        adj[b - 1][a - 1] = 1;
    }

    if(solve(0))
        display();
    else
        cout << "\nNo valid coloring exists.\n";

    return 0;
}