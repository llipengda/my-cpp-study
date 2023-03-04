/*
http://code.mynereus.com/#/class/homework/practical/1
HINT Definitions：
One-Dimensional Life takes place on a straight line instead of a rectangular grid. Each cell has four neighboring positions: those at distance one or two from it on each side. The rules are similar to those of two-dimensional Life except (1) a dead cell with either two or three living neighbors will become alive in the next generation, and (2) a living cell dies if it has zero, one, or three living neighbors. (Hence a dead cell with zero, one, or four living neighbors stays dead; a living cell with two or four living neighbors stays alive.) The progress of sample communities is shown in Figure 1.6(Textbook page44）. Design, write, and test a program for one-dimensional Life.
The total count of the cells is less than 60.
HINT Input:
the position of living cells (1<=postion<=60. Terminate the list with the special number -1).
The number (n) of generation. (n=0 means the initial Grid)
HINT Output: 
the next n generations of the grid.
*/
#include <iostream>
#include <vector>
class LifeGame {
private:
    std::vector<int> cells = std::vector<int>(60, 0);
    std::vector<int> neighbors = std::vector<int>(60, 0);
public:
    void Init();
    void Update();
    void Print();
    void GetNeighborCnt();
};
void LifeGame::Init() {
    int t;
    while (true) {
        std::cin >> t;
        if (t == -1) break;
        cells[t - 1] = 1;
    }
}
void LifeGame::Print() {
    for (int i : cells) {
        std::cout << (i ? '*' : '-');
    }
    std::cout << std::endl;
}
void LifeGame::GetNeighborCnt() {
    std::fill(neighbors.begin(), neighbors.end(), 0);
    for (int i = 0; i < 60; i++) {
        for (int j = i >= 2 ? i - 2 : 0; j <= i + 2 && j < 60; j++) {
            if (j == i) continue;
            neighbors[j] += cells[i];
        }
    }
}
void LifeGame::Update() {
    for (int i = 0; i < 60; i++) {
        if (neighbors[i] == 2) cells[i] = 1;
        else if (cells[i] == 1 && neighbors[i] == 4) cells[i] = 1;
        else if (cells[i] == 0 && neighbors[i] == 3) cells[i] = 1;
        else cells[i] = 0;
    }
}
int main() {
    LifeGame solution;
    solution.Init();
    int t;
    std::cin >> t;
    while (t--) {
        solution.GetNeighborCnt();
        solution.Update();
    }
    solution.Print();
}