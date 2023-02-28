/*
http://code.mynereus.com/#/class/homework/practical/1
HINT Definitions：
Life is really a simulation, not a game with players. It takes place on unbounded rectangular grid in which each cell can either be occupied by an organism or not. Occupied cells are called alived; unoccupied cells are called dead. Which cells are alive changes from generation to generation according to the number of neighboring cells that are alive, as follows transition rules:
(1) The neighbors of a given cell are the eight cells that touch it vertically, horizontally, or diagonally.
(2) If a cell is alive but either has no neighboring cells alive or only one alive, then in the next generation the cell dies of loneliness.
(3) If a cell is alive and has four or more neighboring cells also alive, then in the next generation the cell dies of overcrowding.
(4) A living cell with either two or three living neighbors remains alive in the next generation.
(5) If a cell is dead, then in the next generation it will become alive if it has exactly three neighboring cells, no more or fewer, that are already alive. All other dead cells remain dead in the next generation.
(6) All births and deaths take place at exactly the same time.
(7) The size of grid is 20*60
HINT Input:
the coordinates of living cells (Terminate the list with the special pair -1 -1).
The number (n) of generation. (n=0 means the initial Grid)
HINT Output:
the next n generations of the grid.
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define PER(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
int main() {
    const int C = 20;
    const int R = 60;
    vector<vector<int>> cell(C + 1, vector<int>(R + 1, 0));
    vector<vector<int>> neighbor(C + 1, vector<int>(R + 1, 0));
    while (true) {
        int x, y;
        cin >> x >> y;
        if (x == -1 && y == -1) break;
        cell[x][y] = 1;
    }
    int n;
    cin >> n;
    while (n--) {
        REP(i, 1, C) {
            REP(j, 1, R) {
                neighbor[i][j] = 0;
                REP(x, -1, 1) {
                    REP(y, -1, 1) {
                        int nx = i + x;
                        int ny = j + y;
                        if (x == 0 && y == 0) continue;
                        if (nx >= 0 && nx <= C && ny >= 0 && ny <= R) {
                            neighbor[i][j] += cell[nx][ny];
                        }
                    }
                }
            }
        }

        REP(i, 1, C) {
            REP(j, 1, R) {
                if (cell[i][j] == 1
                    && (neighbor[i][j] < 2 || neighbor[i][j] > 3)) {
                    cell[i][j] = 0;
                }
                if (cell[i][j] == 0 && neighbor[i][j] == 3) {
                    cell[i][j] = 1;
                }
            }
        }
    }
    REP(i, 1, C) {
        REP(j, 1, R) {
            if (cell[i][j] == 1) {
                cout << "*";
            } else {
                cout << "-";
            }
        }
        cout << endl;
    }
}