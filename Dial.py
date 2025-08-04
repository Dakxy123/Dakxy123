import graphviz
import os
import time
from collections import deque

class DialSP:
    def __init__(self, vertices, max_weight):
        self.V = vertices
        self.max_weight = max_weight
        self.edges = []
        self.distances = [float('inf')] * vertices
        self.parents = [-1] * vertices
        self.output_folder = "pngs"
        os.makedirs(self.output_folder, exist_ok=True)

    def add_edge(self, u, v, w):
        self.edges.append((u - 1, v - 1, w))

    def dial(self, source):
        source -= 1 
        graph = {i: [] for i in range(self.V)}
        for u, v, w in self.edges:
            graph[u].append((w, v))
            graph[v].append((w, u))

        self.distances[source] = 0
        max_distance = self.V * self.max_weight
        buckets = [deque() for _ in range(max_distance + 1)]
        buckets[0].append(source)

        print("\nNode | Distance | Parent")

        for i in range(max_distance + 1):
            while buckets[i]:
                u = buckets[i].popleft()

                if self.distances[u] < i:
                    continue

                for weight, v in graph[u]:
                    new_distance = self.distances[u] + weight
                    if new_distance < self.distances[v]:
                        self.distances[v] = new_distance
                        self.parents[v] = u
                        if new_distance <= max_distance:
                            buckets[new_distance].append(v)

        for i in range(self.V):
            parent = self.parents[i] + 1 if self.parents[i] != -1 else "None"
            print(f"{i + 1}     | {self.distances[i]:<8} | {parent}")

    def visualize_full_graph(self):
        dot = graphviz.Graph("FullGraph", comment="Full Graph with All Edges")
        for u, v, w in self.edges:
            dot.node(str(u + 1), str(u + 1))
            dot.node(str(v + 1), str(v + 1))
            dot.edge(str(u + 1), str(v + 1), label=str(w))

        output_path = os.path.join(self.output_folder, 'full_graph')
        dot.render(filename=output_path, format='png', cleanup=False)
        output_path_with_ext = output_path + ".png"
        print(f"Full graph saved as '{output_path_with_ext}'.")

        time.sleep(0.5)
        if os.path.exists(output_path_with_ext):
            os.startfile(output_path_with_ext)
        else:
            print(f"Error: '{output_path_with_ext}' could not be found.")

    def visualize_shortest_path_tree(self):
        dot = graphviz.Graph("SPT", comment="Dial's Shortest Path Tree")

        for u, v, w in self.edges:
            dot.node(str(u + 1), str(u + 1))
            dot.node(str(v + 1), str(v + 1))

            if (self.parents[v] == u or self.parents[u] == v):
                dot.edge(str(u + 1), str(v + 1), label=str(w), color='black')
            else:
                dot.edge(str(u + 1), str(v + 1), label=str(w), color='red')

        output_path = os.path.join(self.output_folder, 'user_dial_spt')
        dot.render(filename=output_path, format='png', cleanup=False)
        output_path_with_ext = output_path + ".png"
        print(f"Shortest Path Tree visualization saved as '{output_path_with_ext}'.")

        time.sleep(0.5)
        if os.path.exists(output_path_with_ext):
            os.startfile(output_path_with_ext)
        else:
            print(f"Error: '{output_path_with_ext}' could not be found.")


def get_user_input():
    print("Enter the number of nodes:")
    nodes = int(input().strip())
    print("Enter the maximum weight of edges:")
    max_weight = int(input().strip())
    sp = DialSP(nodes, max_weight)

    print("Enter the number of edges:")
    edges = int(input().strip())

    print("Enter each edge in the format 'start end weight':")
    for _ in range(edges):
        u, v, w = map(int, input("Edge (start end weight): ").strip().split())
        sp.add_edge(u, v, w)

    return sp

if __name__ == "__main__":
    sp = get_user_input()
    print("Enter the source node:")
    source = int(input().strip())
    sp.dial(source)
    sp.visualize_full_graph()
    sp.visualize_shortest_path_tree()
