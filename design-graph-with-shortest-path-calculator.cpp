#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

class Graph {
private:
    unordered_map<int, vector<pair<int, int>>> listaAdj;
    int qtdNo;
;

public:
    Graph(int n, vector<vector<int>>& edges) {
        qtdNo = n;
        for (const auto& edge : edges) {
            listaAdj[edge[0]].emplace_back(edge[1], edge[2]);
        }
    }

    void addEdge(vector<int> edge) {
        listaAdj[edge[0]].emplace_back(edge[1], edge[2]);
    }

    int shortestPath(int no1, int no2) {
        vector<int> distancias(qtdNo, numeric_limits<int>::max());
        distancias[no1] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, no1);

        while (!pq.empty()) {
            auto [pesoAtual, noAtual] = pq.top();
            pq.pop();

            if (noAtual == no2) {
                return pesoAtual;
            }

            for (const auto& [vizinho, peso] : listaAdj[noAtual]) {
                int novoPeso = pesoAtual + peso;
                if (novoPeso < distancias[vizinho]) {
                    distancias[vizinho] = novoPeso;
                    pq.emplace(novoPeso, vizinho);
                }
            }
        }

        return -1;
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1, node2);
 */
