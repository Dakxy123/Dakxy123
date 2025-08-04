import graphviz
import os
import time
import heapq

class PrimsMST:
    def __init__(self, vertices):
        self.V = vertices
        self.edges = []
        self.mst_edges = []
        self.total_cost = 0
        self.output_folder = "pngs"
        os.makedirs(self.output_folder, exist_ok=True)

    def add_edge(self, u, v, w):
        self.edges.append((u - 1, v - 1, w))

    def prim_mst(self):
        if not self.edges:
            print("No edges to form an MST.")
            return

        graph = {i: [] for i in range(self.V)}
        for u, v, w in self.edges:
            graph[u].append((w, v))
            graph[v].append((w, u))

        visited = [False] * self.V
        min_heap = [(0, 0)]
        total_cost = 0

        print("\nNode's connected  ||  Their Weight")
        while min_heap and len(self.mst_edges) < self.V - 1:
            weight, u = heapq.heappop(min_heap)

            if visited[u]:
                continue

            visited[u] = True
            total_cost += weight

            for edge in graph[u]:
                w, v = edge
                if not visited[v]:
                    heapq.heappush(min_heap, (w, v))
                    self.mst_edges.append((u, v, w))
                    print(f"{u + 1} - {v + 1}  ||  {w}")

        self.total_cost = total_cost
        print(f"\nTotal MST cost: {self.total_cost}")

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

    def visualize_mst(self):
        dot = graphviz.Graph("MST", comment="Prim's MST")

        for u, v, w in self.edges:
            dot.node(str(u + 1), str(u + 1))
            dot.node(str(v + 1), str(v + 1))

            if (u, v, w) in self.mst_edges or (v, u, w) in self.mst_edges:
                dot.edge(str(u + 1), str(v + 1), label=str(w), color='black')
            else:
                dot.edge(str(u + 1), str(v + 1), label=str(w), color='red')

        output_path = os.path.join(self.output_folder, 'user_prims_mst')
        dot.render(filename=output_path, format='png', cleanup=False)
        output_path_with_ext = output_path + ".png"
        print(f"MST visualization saved as '{output_path_with_ext}'.")

        time.sleep(0.5)
        if os.path.exists(output_path_with_ext):
            os.startfile(output_path_with_ext)
        else:
            print(f"Error: '{output_path_with_ext}' could not be found.")


def get_user_input():
    print("Enter the number of nodes:")
    nodes = int(input().strip())
    mst = PrimsMST(nodes)

    print("Enter the number of edges:")
    edges = int(input().strip())

    print("Enter each edge in the format 'start end weight':")
    for _ in range(edges):
        u, v, w = map(int, input("Edge (start end weight): ").strip().split())
        mst.add_edge(u, v, w)

    return mst

if __name__ == "__main__":
    mst = get_user_input()
    mst.prim_mst()
    mst.visualize_full_graph()
    mst.visualize_mst()
