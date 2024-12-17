#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct Point {
    int x, y;
};

bool isValid(int x, int y, int numRows, int numCols, const vector<vector<int>>& grid) {
    return (x >= 0 && x < numRows && y >= 0 && y < numCols && grid[x][y] != -1);
}

void bfs(const vector<vector<int>>& grid, vector<vector<int>>& distances, Point start) {
    int numRows = grid.size();
    int numCols = grid[0].size();
    queue<Point> q;
    q.push(start);
    distances[start.x][start.y] = 0;

    vector<int> dx = {-1, 1, 0, 0}; // Up, down, left, right
    vector<int> dy = {0, 0, -1, 1};

    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            if (isValid(newX, newY, numRows, numCols, grid) && distances[newX][newY] == -1) {
                distances[newX][newY] = distances[current.x][current.y] + 1;
                q.push({newX, newY});
            }
        }
    }
}

int main() {
    const int numRows = 4;
    const int numCols = 4;

    // Initialize the grid with all cells accessible
    vector<vector<int>> grid(numRows, vector<int>(numCols, 0));

    // Prompt user to enter starting coordinates
    int startRow, startCol;
    cout << "Enter the starting row number (from bottom up, 1 to " << numRows << "): ";
    cin >> startRow;
    cout << "Enter the starting column number (from left to right, 1 to " << numCols << "): ";
    cin >> startCol;

    // Convert user input to zero-based indices
    int startRowIndex = numRows - startRow;
    int startColIndex = startCol - 1;

    // Check for valid input
    if (startRowIndex < 0 || startRowIndex >= numRows || startColIndex < 0 || startColIndex >= numCols) {
        cout << "Invalid coordinates!" << endl;
        return 1;
    }

    // Prompt user to enter the number of walls
    int numWalls;
    cout << "Enter the number of walls: ";
    cin >> numWalls;

    // Get the coordinates for each wall and mark them on the grid
    for (int i = 0; i < numWalls; ++i) {
        int wallRow, wallCol;
        cout << "Enter the row number for wall " << i + 1 << " (from bottom up, 1 to " << numRows << "): ";
        cin >> wallRow;
        cout << "Enter the column number for wall " << i + 1 << " (from left to right, 1 to " << numCols << "): ";
        cin >> wallCol;

        int wallRowIndex = numRows - wallRow;
        int wallColIndex = wallCol - 1;

        if (wallRowIndex >= 0 && wallRowIndex < numRows && wallColIndex >= 0 && wallColIndex < numCols) {
            grid[wallRowIndex][wallColIndex] = -1; // Mark as wall
        } else {
            cout << "Invalid wall coordinates!" << endl;
            return 1;
        }
    }

    // Create a 2D vector to store distances and initialize with -1
    vector<vector<int>> distances(numRows, vector<int>(numCols, -1));

    // Calculate distances using BFS
    bfs(grid, distances, {startRowIndex, startColIndex});

    // Print the grid of distances
    cout << "Distances: " << endl;
    for (const auto& row : distances) {
        for (int distance : row) {
            if (distance == -1) {
                cout << "W "; // Indicate walls
            } else {
                cout << distance << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
