#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

int calulcarMST(int tam, vector<vector<int>>& arestas, int arestaIgnorada, int arestaForcada) {
    vector<vector<pair<int, int>>> grafo(tam);
    vector<bool> visitado(tam, false);

    if (arestaForcada != -1) {
        int u = arestas[arestaForcada][0];
        int v = arestas[arestaForcada][1];
        int w = arestas[arestaForcada][2];
        grafo[u].push_back({v, w});
        grafo[v].push_back({u, w});
    }

    for (int i = 0; i < arestas.size(); ++i) {
        if (i == arestaIgnorada || i == arestaForcada) continue;
        int u = arestas[i][0];
        int v = arestas[i][1];
        int w = arestas[i][2];
        grafo[u].push_back({v, w});
        grafo[v].push_back({u, w});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0}); // (pesos, vértice)
    int peso = 0, qtdArestasUsadas = 0;

    while (!pq.empty() && qtdArestasUsadas < n) {
        int weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visitado[u]) continue;

        visitado[u] = true;
        peso += weight;
        qtdArestasUsadas++;

        for (auto& [v, w] : grafo[u]) {
            if (!visitado[v]) {
                pq.push({w, v});
            }
        }
    }

    return qtdArestasUsadas == n ? peso : INT_MAX;
}


class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int qtd_arestas = edges.size();
        vector<vector<int>> arestas_i;

        for (int i = 0; i < qtd_arestas; ++i) {
            arestas_i.push_back({edges[i][0], edges[i][1], edges[i][2], i});
        }

        sort(arestas_i.begin(), arestas_i.end(), [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2];
        });

        int pesoBase = calulcarMST(n, arestas_i, -1, -1);

        vector<int> arestas_criticas, arestas_pseudas;

        for (int i = 0; i < qtd_arestas; ++i) {
            int pesoSemAresta = calulcarMST(n, arestas_i, i, -1);
            if (pesoSemAresta > pesoBase) {
                arestas_criticas.push_back(arestas_i[i][3]);
            } else {
                int pesoComAresta = calulcarMST(n, arestas_i, -1, i);
                if (pesoComAresta == pesoBase) {
                    arestas_pseudas.push_back(arestas_i[i][3]);
                }
            }
        }

        return {arestas_criticas, arestas_pseudas};
    }
};

