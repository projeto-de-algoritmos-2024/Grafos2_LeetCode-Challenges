# Link: https://leetcode.com/problems/network-delay-time/description/?envType=problem-list-v2&envId=shortest-path
import heapq

class Solution:
    def networkDelayTime(self, times, n, k):
        table = {}
        for t in times:
            if not table.get(t[0]):
                table[t[0]] = {t[1]:t[2]}
            else:
                table[t[0]][t[1]] = t[2]
        
        min_heap = [(0, k)]
        distances = {k: 0}
        
        while min_heap:
            current_distance, current_node = heapq.heappop(min_heap)
            
            actual_node = table.get(current_node)
            
            if actual_node:
                for neighbor, weight in table[current_node].items():
                    dist_tab = distances.get(neighbor, float('inf'))
                    if current_distance + weight < dist_tab:
                        distances[neighbor] = current_distance + weight
                        heapq.heappush(min_heap, (current_distance + weight, neighbor))

        _max = -1
        
        if len(distances) < n:
            return _max
    
        for nodes, values in distances.items():
            _max = max(_max, values)
            
        if _max == 0:
            return -1
        
        return _max
