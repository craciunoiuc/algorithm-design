// Copyright [2019] <Cezar Craciunoiu>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream fin("p1.in");
    std::ofstream fout("p1.out");
    int n;
    fin >> n;
    std::vector<std::pair<int, int>> distances(n);
    for (int i = 0; i < n; ++i) {
        int read_aux;
        fin >> read_aux;
        distances[i] = {i + 1, read_aux};
    }
    fin.close();

    // Se sorteaza crescator dupa distante
    std::sort(distances.begin(), distances.end(),
             [](std::pair<int, int> a, std::pair<int, int> b) -> bool
                {return a.second < b.second;});

    // Se verifica ca este doar o radacina
    if (distances[0].second == 0 &&
        distances[0].second == distances[1].second) {
        fout << -1;
        fout.close();
        return 0;
    }

    // Se verifica ca graful poate fi realizat
    for (size_t i = 1; i < distances.size(); ++i) {
        if (distances[i - 1].second != distances[i].second &&
            distances[i - 1].second + 1 != distances[i].second) {
            fout << -1 << "\n";
            fout.close();
            return 0;
        }
    }

    // Uneste la ultimul nod de la adancimea trecuta toate nodurile de la
    // adancimea curenta cat timp adancimea din distante e egala.
    size_t currDepth = 0;
    fout << distances.size() - 1 << "\n";
    for (size_t i = 1; i < distances.size();) {
        currDepth = i - 1;
        do {
            i++;
            fout << distances[currDepth].first << " "
                 << distances[i - 1].first     << " ";
        } while (distances[i].second == distances[i - 1].second &&
                 i < distances.size());
    }
    fout.close();
    return 0;
}
