#include "raylib.h"
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
int mazeCols = 20; // Default maze columns
int mazeRows = 15; // Default maze rows
int cellSize = 40; // Default cell size

// Cell structure for maze generation
struct Cell {
    int x, y;
    bool visited = false;
    bool walls[4] = { true, true, true, true }; // top, right, bottom, left
};

// Maze class
class Maze {
public:

    Color wallColor; // Variable for change of wall color
    Maze() : wallColor(GREEN) { // default color initialization
        GenerateMaze();
    }
    void GenerateMaze() {
        grid.clear();
        grid.resize(mazeCols * mazeRows);

        // Initialize grid
        for (int y = 0; y < mazeRows; ++y) {
            for (int x = 0; x < mazeCols; ++x) {
                grid[y * mazeCols + x] = { x, y };
            }
        }

        // DFS maze generation
        std::stack<Cell*> stack;
        Cell* current = &grid[0];
        current->visited = true;

        while (true) {
            Cell* next = GetUnvisitedNeighbor(*current);
            if (next) {
                stack.push(current);
                RemoveWalls(*current, *next);
                current = next;
                current->visited = true;
            }
            else if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            }
            else {
                break;
            }
        }
    }

    void DrawMaze() const {

        for (const Cell& cell : grid) {
            int x = cell.x * cellSize;
            int y = cell.y * cellSize;

            if (cell.walls[0]) DrawLine(x, y, x + cellSize, y, wallColor);           // Top
            if (cell.walls[1]) DrawLine(x + cellSize, y, x + cellSize, y + cellSize, wallColor); // Right
            if (cell.walls[2]) DrawLine(x, y + cellSize, x + cellSize, y + cellSize, wallColor); // Bottom
            if (cell.walls[3]) DrawLine(x, y, x, y + cellSize, wallColor);           // Left
        }
    }

    bool IsWall(int x, int y, int dir) const {
        int index = y * mazeCols + x;
        if (index < 0 || index >= (int)grid.size()) return true;
        return grid[index].walls[dir];
    }

private:
    std::vector<Cell> grid;

    Cell* GetUnvisitedNeighbor(const Cell& cell) {
        std::vector<Cell*> neighbors;

        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { -1, 0, 1, 0 };

        for (int i = 0; i < 4; ++i) {
            int nx = cell.x + dx[i];
            int ny = cell.y + dy[i];

            if (nx >= 0 && nx < mazeCols && ny >= 0 && ny < mazeRows) {
                Cell* neighbor = &grid[ny * mazeCols + nx];
                if (!neighbor->visited) {
                    neighbors.push_back(neighbor);
                }
            }
        }

        if (!neighbors.empty()) {
            return neighbors[std::rand() % neighbors.size()];
        }
        return nullptr;
    }

    void RemoveWalls(Cell& a, Cell& b) {
        int dx = b.x - a.x;
        int dy = b.y - a.y;

        if (dx == 1) { a.walls[1] = false; b.walls[3] = false; }
        if (dx == -1) { a.walls[3] = false; b.walls[1] = false; }
        if (dy == 1) { a.walls[2] = false; b.walls[0] = false; }
        if (dy == -1) { a.walls[0] = false; b.walls[2] = false; }
    }
};