// Copyright [2019] <Cezar Craciunoiu>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
#include <set>

// Functia se comporta asemanator ca la problema 3. La final se adauga toate
// tipurile de noduri prin care se trece intr-un set si se calculeaza
// penalizarea. Dupa aceea se adauga penalizarea la cost si se intoarce.
int64_t dijkstra(int64_t source, int64_t n,
const std::vector<std::vector<std::tuple<int64_t, int64_t, int64_t>>>& adj_list,
const std::vector<int64_t>& penalties) {
    std::vector<int64_t> d(n + 1, -1);        // Vector distante
    std::vector<bool> visited(n + 1, false);  // Vector vizitati
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
        auto u = coada.top();
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
    std::set<int64_t, std::greater<int64_t>> unique_types;
    for (int64_t i = n; i > source; i = parinti[i].first) {
        for (auto& nod : adj_list[i]) {
            if (std::get<0>(nod) == parinti[i].first) {
                unique_types.insert(std::get<2>(nod));
            }
        }
    }
    int64_t result = d[n];
    for (auto& nod : unique_types) {
        result += penalties[nod];
    }
    return result;
}

int main() {
    std::ifstream fin("p4.in");
    std::ofstream fout("p4.out");
    uint16_t n, m, t;
    fin >> n >> m >> t;
    std::vector<std::vector<std::tuple<int64_t, int64_t, int64_t>>>
                                                                adj_list(n + 1);
    std::vector<int64_t> penalties(t + 1);

    // Graf neorientat deci adauga in ambele directii
    for (uint16_t i = 0; i < m; ++i) {
        int64_t source_node, dest_node, cost, type;
        fin >> source_node >> dest_node >> cost >> type;
        adj_list[source_node].push_back({dest_node, cost, type});
        adj_list[dest_node].push_back({source_node, cost, type});
    }

    for (uint16_t i = 1; i < t + 1; ++i) {
        fin >> penalties[i];
    }
    fout << dijkstra(1, n, adj_list, penalties) << "\n";
    fin.close();
    fout.close();
    return 0;
}
