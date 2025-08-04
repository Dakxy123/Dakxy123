import graphviz
import os

class KruskalMST:
    def __init__(self, vertices):
        self.V = vertices
        self.edges = []
        self.parent = list(range(vertices))
        self.rank = [0] * vertices
        self.mst_edges = []
        self.cycle_edges = []  # To store cycle edges separately
        self.total_cost = 0
        self.output_folder = "pngs"
        os.makedirs(self.output_folder, exist_ok=True)

    def add_edge(self, u, v, w):
        self.edges.append((u - 1, v - 1, w))

    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def union(self, u, v):
        root_u = self.find(u)
        root_v = self.find(v)
        if root_u != root_v:
            if self.rank[root_u] < self.rank[root_v]:
                self.parent[root_u] = root_v
            elif self.rank[root_u] > self.rank[root_v]:
                self.parent[root_v] = root_u
            else:
                self.parent[root_v] = root_u
                self.rank[root_u] += 1

    def kruskal_mst(self):
        self.edges = sorted(self.edges, key=lambda item: item[2])
        print("\nChoose edges to include in the MST:")
        for idx, (u, v, weight) in enumerate(self.edges):
            print(f"{idx + 1}. Edge ({u + 1} -- {v + 1}) with weight {weight}")

        while True:
            print("\nEnter the edge number to include it in the MST or type 'done' to finish:")
            choice = input().strip()
            if choice.lower() == 'done':
                break

            try:
                edge_idx = int(choice) - 1
                if 0 <= edge_idx < len(self.edges):
                    u, v, weight = self.edges[edge_idx]
                    if self.find(u) != self.find(v): 
                        self.union(u, v)
                        self.mst_edges.append((u, v, weight))
                        self.total_cost += weight
                        print(f"Added edge ({u + 1} -- {v + 1}) with weight {weight}")
                    else:
                        print("Adding this edge would create a cycle. Highlighting the edge:")
                        self.cycle_edges.append((u, v, weight))
                else:
                    print("Invalid edge number. Please try again.")
            except ValueError:
                print("Please enter a valid number.")

        print("\nNode's connected  ||  Their Weight")
        for u, v, weight in self.mst_edges:
            print(f"{u + 1} - {v + 1}  ||  {weight}")
        for u, v, weight in self.cycle_edges:
            print(f"{u + 1} - {v + 1} (cycle)  ||  {weight}")

        print(f"\nTotal MST cost: {self.total_cost}")

    def visualize_full_graph(self):
        dot = graphviz.Graph("FullGraph", comment="Full Graph with All Edges")
        for u, v, w in self.edges:
            dot.node(str(u + 1), str(u + 1))
            dot.node(str(v + 1), str(v + 1))
            dot.edge(str(u + 1), str(v + 1), label=str(w))

        output_path = os.path.join(self.output_folder, 'full_graph')
        dot.render(filename=output_path, format='png', cleanup=False)
        print(f"Full graph saved as '{output_path}.png'.")
        os.startfile(output_path + ".png")

    def visualize_mst(self):
        dot = graphviz.Graph("MST", comment="User-Selected MST")
        for u, v, w in self.edges:
            dot.node(str(u + 1), str(u + 1))
            dot.node(str(v + 1), str(v + 1))
            if (u, v, w) in self.mst_edges or (v, u, w) in self.mst_edges:
                dot.edge(str(u + 1), str(v + 1), label=str(w), color='black')  # MST edges
            elif (u, v, w) in self.cycle_edges or (v, u, w) in self.cycle_edges:
                dot.edge(str(u + 1), str(v + 1), label=str(w), color='red')  # Cycle edges
            else:
                dot.edge(str(u + 1), str(v + 1), label=str(w), color='grey')  # Other edges

        output_path = os.path.join(self.output_folder, 'user_kruskal_mst')
        dot.render(filename=output_path, format='png', cleanup=False)
        print(f"MST visualization saved as '{output_path}.png'.")
        os.startfile(output_path + ".png")

def get_user_input():
    print("Enter the number of nodes:")
    nodes = int(input().strip())
    mst = KruskalMST(nodes)

    print("Enter the number of edges:")
    edges = int(input().strip())

    print("Enter each edge in the format 'start end weight':")
    for _ in range(edges):
        u, v, w = map(int, input("Edge (start end weight): ").strip().split())
        mst.add_edge(u, v, w)

    return mst

if __name__ == "__main__":
    mst = get_user_input()

    print("Choose node representation:")
    print("1. Letters")
    print("2. Circles with numbers")
    node_style_choice = input("Enter your choice (1 or 2): ").strip()
    node_style = 'letters' if node_style_choice == '1' else 'circles'

    mst.kruskal_mst()
    mst.visualize_full_graph()
    mst.visualize_mst()
