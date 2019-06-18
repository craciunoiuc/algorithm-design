// Copyright [2019] <Cezar Craciunoiu>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>

class Solve {
 private:
    const int8_t dx[4] = {0, 0, 1, -1};  // Offset pentru OX
    const int8_t dy[4] = {1, -1, 0, 0};  // Offset pentru OY
    int64_t n;                           // Numar noduri
    int64_t m;                           // Numar muchii
    int64_t k;                           // Constanta k data
    int64_t count;                       // Numar elemente la un moment dat
    int64_t current_min;                 // Valoarea minima dintr-un moment dat
    int64_t current_max;                 // Valoarea maxima dintr-un moment dat
    std::vector<std::vector<int64_t>> matrix;           // Matricea data
    std::vector<std::vector<bool>> visited;             // Matricea de vizitare
    std::queue<std::pair<int64_t, int64_t>> bfs_queue;  // Coada folosita la BFS

    // Functie mica facuta pentru verificare ca o pozitie este valida
    inline bool valid_position(int64_t newX, int64_t newY) {
            return (newX < n && newY < m && newX >= 0 && newY >= 0 &&
                    !visited[newX][newY] && matrix[newX][newY] >= current_min);
    }

    // Functie de BFS clasica, modificata pentru a rula pe o matrice. La
    // fiecare pas se verifica daca se poate mari maximul sau s-a ajuns la
    // limita. (daca nu, se adauga si se schimba maximul)
    void BFS(int64_t i, int64_t j) {
        current_min = matrix[i][j];
        current_max = matrix[i][j];
        for (auto& row : visited) {
            fill(row.begin(), row.end(), false);
        }
        visited[i][j] = true;
        count = 1;
        bfs_queue.push({i, j});
        while (!bfs_queue.empty()) {
            auto cell = bfs_queue.front();
            bfs_queue.pop();
            for (uint8_t u = 0; u < 4; ++u) {
                const int64_t newY = cell.first + dy[u];
                const int64_t newX = cell.second + dx[u];
                if (valid_position(newY, newX)) {
                    if (matrix[newY][newX] > current_max) {
                        if (matrix[newY][newX] - current_min <= k) {
                            current_max = matrix[newY][newX];
                        } else {
                            continue;
                        }
                    }
                    bfs_queue.push({newY, newX});
                    visited[newY][newX] = true;
                    count++;
                }
            }
        }
    }

 public:
    // In constructor se citesc datele din fisier si se construiesc vectorii
    Solve() {
        std::ifstream fin("p2.in");
        fin >> n >> m >> k;
        matrix = std::vector<std::vector<int64_t>>(n, std::vector<int64_t>(m));
        visited = std::vector<std::vector<bool>>(n, std::vector<bool>(m));
        for (int64_t i = 0; i < n; ++i) {
            for (int64_t j = 0; j < m; ++j) {
                fin >> matrix[i][j];
            }
        }
        fin.close();
    }

    ~Solve() {
    }

    // Functia apelata pentru a afla cea mai mare "insula". Functia porneste
    // un BFS din fiecare pozitie ce are ca minim valoarea din acea pozitie.
    void componenta_conexa_maxima() {
        int64_t max_size = 0;
        for (int64_t i = 0; i < n; ++i) {
            for (int64_t j = 0; j < m; ++j) {
                BFS(i, j);
                if (count >= max_size) {
                    max_size = count;
                }
            }
        }

        std::ofstream fout("p2.out");
        fout << max_size << "\n";
        fout.close();
    }
};

int main() {
    Solve* solution = new Solve();
    solution->componenta_conexa_maxima();
    delete solution;
    return 0;
}
