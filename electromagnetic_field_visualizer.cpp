#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int ROW = 5, COL = 5;

struct Cell {
    int row, col, attenuation;
};

// Directions: up, down, left, right
int dRow[] = {-1, 1, 0, 0};
int dCol[] = {0, 0, -1, 1};

// Sample material grid: 0=conductor (low attenuation), 1=insulator (high)
int materialGrid[ROW][COL] = {
    {0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 1},
    {1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0}
};

// Attenuation values
int getAttenuation(int type) {
    if (type == 0) return 1; // conductor
    else return 5;           // insulator
}

// BFS to simulate field propagation
void simulateField(int startRow, int startCol) {
    vector<vector<int>> fieldStrength(ROW, vector<int>(COL, INT_MAX));
    queue<Cell> q;

    q.push({startRow, startCol, 0});
    fieldStrength[startRow][startCol] = 0;

    while (!q.empty()) {
        Cell current = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dRow[i];
            int newCol = current.col + dCol[i];

            if (newRow >= 0 && newRow < ROW && newCol >= 0 && newCol < COL) {
                int attenuation = getAttenuation(materialGrid[newRow][newCol]);
                int newStrength = current.attenuation + attenuation;

                if (newStrength < fieldStrength[newRow][newCol]) {
                    fieldStrength[newRow][newCol] = newStrength;
                    q.push({newRow, newCol, newStrength});
                }
            }
        }
    }

    // Print field strength matrix
    cout << "\nField propagation strength from source:\n";
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (fieldStrength[i][j] == INT_MAX)
                cout << " X ";
            else
                cout << " " << fieldStrength[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int startRow = 0, startCol = 0;
    cout << "Source at (0,0) - Starting field simulation...\n";
    simulateField(startRow, startCol);
    return 0;
}
