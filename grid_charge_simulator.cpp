#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int ROW = 10;
const int COL = 10;

struct Point {
    int x, y;
};

// Directions (N, S, E, W)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void bfs(vector<vector<char>>& grid, vector<vector<int>>& influence, Point start, int value) {
    queue<Point> q;
    q.push(start);
    influence[start.x][start.y] = value;

    while (!q.empty()) {
        Point p = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < ROW && ny < COL) {
                if (grid[nx][ny] == '.' && influence[nx][ny] == 0) {
                    influence[nx][ny] = value;
                    q.push({nx, ny});
                }
            }
        }
    }
}

void displayField(const vector<vector<char>>& grid, const vector<vector<int>>& influence) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (grid[i][j] != '.')
                cout << grid[i][j] << " ";
            else if (influence[i][j] > 0)
                cout << "+ ";
            else if (influence[i][j] < 0)
                cout << "- ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<char>> grid(ROW, vector<char>(COL, '.'));
    vector<vector<int>> influence(ROW, vector<int>(COL, 0));

    // Place charges
    grid[2][2] = '+';  // Positive charge
    grid[7][7] = '-';  // Negative charge

    // Run BFS from each charge
    bfs(grid, influence, {2, 2}, 1);
    bfs(grid, influence, {7, 7}, -1);

    cout << "Electromagnetic Influence Field:\n";
    displayField(grid, influence);

    return 0;
}
