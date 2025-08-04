import graphviz
import os
import time
import heapq

class DijkstraSP:
    def __init__(self, vertices):
        self.V = vertices
        self.edges = []
        self.distances = [float('inf')] * vertices
        self.parents = [-1] * vertices
        self.output_folder = "pngs"
        os.makedirs(self.output_folder, exist_ok=True)

    def add_edge(self, u, v, w):
        self.edges.append((u - 1, v - 1, w))

    def dijkstra(self, source):
        source -= 1  # Adjusting for 0-based indexing
        graph = {i: [] for i in range(self.V)}
        for u, v, w in self.edges:
            graph[u].append((w, v))
            graph[v].append((w, u))

        self.distances[source] = 0
        min_heap = [(0, source)]

        print("\nNode | Distance | Parent")
        while min_heap:
            dist_u, u = heapq.heappop(min_heap)

            for weight, v in graph[u]:
                if self.distances[u] + weight < self.distances[v]:
                    self.distances[v] = self.distances[u] + weight
                    self.parents[v] = u
                    heapq.heappush(min_heap, (self.distances[v], v))

        # Display results
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
        dot = graphviz.Graph("SPT", comment="Dijkstra's Shortest Path Tree")

        for u, v, w in self.edges:
            dot.node(str(u + 1), str(u + 1))
            dot.node(str(v + 1), str(v + 1))

            # Highlight edges in the shortest path tree
            if (self.parents[v] == u or self.parents[u] == v):
                dot.edge(str(u + 1), str(v + 1), label=str(w), color='black')
            else:
                dot.edge(str(u + 1), str(v + 1), label=str(w), color='red')

        output_path = os.path.join(self.output_folder, 'user_dijkstra_spt')
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
    sp = DijkstraSP(nodes)

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
    sp.dijkstra(source)
    sp.visualize_full_graph()
    sp.visualize_shortest_path_tree()
