#include <bits/stdc++.h>
int main()
{
    int c, m;
    std::cin >> c >> m;
    std::vector<std::vector<int>> matrix(c);
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        matrix[x - 1].push_back(y);
    }
    for (auto i : matrix) {
        for (auto j : i)
            std::cout << j << ' ';
        std::cout << '\n';
    }
}