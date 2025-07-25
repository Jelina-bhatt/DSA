#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

// Thermodynamic State
struct State {
    double temperature;
    double pressure;
    double energy;

    // Custom comparator for priority queue
    bool operator<(const State& other) const {
        return energy > other.energy; // min-heap
    }
};

int main() {
    // Map to store thermodynamic states
    map<pair<double, double>, double> stateEnergy;

    // Sample states: (Temperature, Pressure) => Energy
    stateEnergy[{300, 1}] = 120;
    stateEnergy[{350, 1}] = 100;
    stateEnergy[{400, 2}] = 80;
    stateEnergy[{450, 3}] = 60;
    stateEnergy[{500, 4}] = 50;

    // Priority Queue to find lowest energy state
    priority_queue<State> pq;

    for (auto& entry : stateEnergy) {
        State s;
        s.temperature = entry.first.first;
        s.pressure = entry.first.second;
        s.energy = entry.second;
        pq.push(s);
    }

    cout << "Thermodynamic states ordered by lowest energy:\n";
    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();
        cout << "Temp: " << current.temperature << " K, "
             << "Pressure: " << current.pressure << " atm, "
             << "Energy: " << current.energy << " kJ\n";
    }

    return 0;
}
