#include <iostream>
#include <queue>
#include <cmath>
#include <string>
#define M_PI 3.14159265358979323846

using namespace std;

const float g = 9.8; // Acceleration due to gravity

// Define the Projectile structure
struct Projectile {
    string name;
    float angle, velocity;
    float maxHeight, timeOfFlight, range;

    // Constructor
    Projectile(string n, float a, float v) {
        name = n;
        angle = a;
        velocity = v;
        calculate();
    }

    // Calculate physics values
    void calculate() {
        float radians = angle * M_PI / 180;  // Convert angle to radians
        maxHeight = (velocity * velocity * pow(sin(radians), 2)) / (2 * g);
        timeOfFlight = (2 * velocity * sin(radians)) / g;
        range = (velocity * velocity * sin(2 * radians)) / g;
    }
};

// Comparator for priority queue (max height)
struct CompareHeight {
    bool operator()(Projectile const& p1, Projectile const& p2) {
        return p1.maxHeight < p2.maxHeight;  // Max-Heap
    }
};

int main() {
    queue<Projectile> launchQueue;
    priority_queue<Projectile, vector<Projectile>, CompareHeight> heightQueue;

    // Example projectiles (you can replace these with user input later)
    Projectile p1("Ball1", 45, 20);
    Projectile p2("Ball2", 60, 25);
    Projectile p3("Ball3", 30, 18);

    // Push into queue and priority queue
    launchQueue.push(p1);
    launchQueue.push(p2);
    launchQueue.push(p3);

    heightQueue.push(p1);
    heightQueue.push(p2);
    heightQueue.push(p3);

    cout << "📥 Simulate by Launch Time (Queue Order):\n";
    while (!launchQueue.empty()) {
        Projectile p = launchQueue.front();
        launchQueue.pop();
        cout << "Name: " << p.name
             << ", Max Height: " << p.maxHeight
             << " m, Range: " << p.range
             << " m, Time of Flight: " << p.timeOfFlight
             << " s\n";
    }

    cout << "\n🚀 Simulate by Max Height (Priority Queue):\n";
    while (!heightQueue.empty()) {
        Projectile p = heightQueue.top();
        heightQueue.pop();
        cout << "Name: " << p.name
             << ", Max Height: " << p.maxHeight
             << " m, Range: " << p.range
             << " m, Time of Flight: " << p.timeOfFlight
             << " s\n";
    }

    return 0;
}
