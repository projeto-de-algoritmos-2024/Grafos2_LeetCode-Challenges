import heapq
from collections import defaultdict

def dijkstra(arestas, inicio):
    grafo = defaultdict(list)
    for origem, destino, peso in arestas:
        grafo[origem].append((destino, peso))
        grafo[destino].append((origem, peso))

    distancias = {no: float('inf') for no in range(n)}
    distancias[inicio] = 0  

    fila_prioridade = [(0, inicio)]

    while fila_prioridade:
        distancia_atual, no_atual = heapq.heappop(fila_prioridade)
        
        if distancia_atual > distancias[no_atual]:
            continue
        
        for vizinho, peso in grafo[no_atual]:
            nova_distancia = distancia_atual + peso

            if nova_distancia < distancias[vizinho]:
                distancias[vizinho] = nova_distancia
                heapq.heappush(fila_prioridade, (nova_distancia, vizinho))

    return distancias

def encontrar_arestas_importantes(n, arestas):
    dist_do_inicio = dijkstra(arestas, 0)
    dist_do_fim = dijkstra(arestas, n - 1)
    
    menor_distancia = dist_do_inicio[n - 1]
    
    resposta = []
    for origem, destino, peso in arestas:
        if (
            dist_do_inicio[origem] + peso + dist_do_fim[destino] == menor_distancia or
            dist_do_inicio[destino] + peso + dist_do_fim[origem] == menor_distancia
        ):
            resposta.append(True)
        else:
            resposta.append(False)

    return resposta
