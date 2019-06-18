// Copyright [2019] <Cezar Craciunoiu>
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>
#include <deque>
#include <vector>
#include <tuple>
#include <set>

// Functia ruleaza un dijkstra din nodul 1 pana in n si apoi verifica daca
// exista schimbari de tipuri de muchii si le marcheaza adaugandu-le intr-un
// vector. La final calculeaza penalizarea adaugata si o returneaza.
int64_t dijkstra(int64_t source, int64_t n,
const std::vector<std::vector<std::tuple<int64_t, int64_t, int64_t>>>& adj_list,
const std::vector<std::vector<int64_t>>& penalties) {
    std::vector<int64_t> d(n + 1, -1);          // Vector distante
    std::vector<bool> visited(n + 1, false);    // Vector vizitati
    auto comparer = [](std::pair<int64_t, int64_t> left,
                       std::pair<int64_t, int64_t> rght)
                    {return (left.second > rght.second);};
    std::priority_queue<std::pair<int64_t, int64_t>,
                        std::vector<std::pair<int64_t, int64_t>>,
                        decltype(comparer)> coada(comparer);
    d[source] = 0;
    std::vector<std::pair<int64_t, int64_t>> parinti(n + 1);
    coada.push({source, d[source]});
    while (!coada.empty()) {
        std::pair<int64_t, int64_t> u = coada.top();
        coada.pop();
        if (!visited[u.first]) {
            visited[u.first] = true;
            for (auto& nod : adj_list[u.first]) {
                if (d[std::get<0>(nod)] == -1 || (!visited[std::get<0>(nod)] &&
                    d[std::get<0>(nod)] > d[u.first] + std::get<1>(nod))) {
                    d[std::get<0>(nod)] = d[u.first] + std::get<1>(nod);
                    parinti[std::get<0>(nod)] = u;
                    coada.push({std::get<0>(nod), d[std::get<0>(nod)]});
                }
            }
        }
    }
    std::vector<int64_t> uniqueTypes;
    for (int64_t i = n; i > source; i = parinti[i].first) {
        for (auto& nod : adj_list[i]) {
            if (std::get<0>(nod) == parinti[i].first) {
                uniqueTypes.push_back(std::get<2>(nod));
            }
        }
    }

    int64_t result = d[n];
    if (uniqueTypes.size() > 1) {
        for (auto nod = uniqueTypes.begin() + 1;
             nod != uniqueTypes.end(); ++nod) {
            result += penalties[*(nod - 1)][*(nod)];
        }
    }
    return result;
}

int main() {
    std::ifstream fin("p3.in");
    std::ofstream fout("p3.out");
    int64_t n, m, t;
    fin >> n >> m >> t;
    std::vector<std::vector<std::tuple<int64_t, int64_t, int64_t>>> adj(n + 1);
    std::vector<std::vector<int64_t>> penalties(t + 1,
                                                std::vector<int64_t>(t + 1));

    // Se citesc nodurile si se adauga in ambele directii (graf neorientat)
    for (int64_t i = 0; i < m; ++i) {
        int64_t src, dest, cost, type;
        fin >> src >> dest >> cost >> type;
        adj[src].push_back({dest, cost, type});
        adj[dest].push_back({src, cost, type});
    }

    for (int64_t i = 1; i < t + 1; ++i) {
        for (int64_t j = 1; j < t + 1; ++j) {
            fin >> penalties[i][j];
        }
    }
    fout << dijkstra(1, n, adj, penalties) << "\n";
    fin.close();
    fout.close();
    return 0;
}
