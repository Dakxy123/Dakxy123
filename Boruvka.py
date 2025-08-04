import graphviz
import os

class BoruvkasMST:
    def __init__(self, vertices):
        self.V = vertices
        self.edges = []
        self.parent = list(range(vertices))
        self.rank = [0] * vertices
        self.mst_edges = []
        self.total_cost = 0
        self.output_folder = "pngs"
        os.makedirs(self.output_folder, exist_ok=True)

    def add_edge(self, u, v, w):
        self.edges.append((u - 1, v - 1, w))  # Store edges with zero-based indexing

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

    def boruvka_mst(self):
        num_components = self.V
        while num_components > 1:
            cheapest = [-1] * self.V  
            edges_added = False

            for index, (u, v, w) in enumerate(self.edges):
                set_u = self.find(u)
                set_v = self.find(v)

                if set_u != set_v:
                    # Check if this edge is cheaper than the current cheapest for component set_u
                    if cheapest[set_u] == -1 or self.edges[cheapest[set_u]][2] > w:
                        cheapest[set_u] = index
                    # Check if this edge is cheaper than the current cheapest for component set_v
                    if cheapest[set_v] == -1 or self.edges[cheapest[set_v]][2] > w:
                        cheapest[set_v] = index

            for i in range(self.V):
                if cheapest[i] != -1:  # If there is a cheapest edge for this component
                    u, v, w = self.edges[cheapest[i]]
                    set_u = self.find(u)
                    set_v = self.find(v)

                    if set_u != set_v:  
                        self.union(set_u, set_v)
                        self.mst_edges.append((u, v, w))
                        self.total_cost += w
                        print(f"{u + 1} - {v + 1}  ||  {w}")
                        num_components -= 1
                        edges_added = True  

            if not edges_added:
                print("No edges were added in this iteration. Exiting to avoid infinite loop.")
                break

        print(f"\nTotal MST cost: {self.total_cost}")

    def visualize_full_graph(self):
        dot = graphviz.Graph("FullGraph", comment="Full Graph with All Edges")
        for u, v, w in self.edges:
            dot.node(str(u + 1), str(u + 1))
            dot.node(str(v + 1), str(v + 1))
            dot.edge(str(u + 1), str(v + 1), label=str(w))

        output_path = os.path.join(self.output_folder, 'full_graph.png')
        dot.render(filename=output_path, format='png', cleanup=True)
        output_path_with_ext = output_path + ".png"
        print(f"Full graph saved as '{output_path_with_ext}'.")
        os.startfile(output_path_with_ext)

    def visualize_mst(self):
        dot = graphviz.Graph("MST", comment="Boruvka's MST")

        for u, v, w in self.edges:
            dot.node(str(u + 1), str(u + 1))
            dot.node(str(v + 1), str(v + 1))

            if (u, v, w) in self.mst_edges or (v, u, w) in self.mst_edges:
                dot.edge(str(u + 1), str(v + 1), label=str(w), color='black') 
            else:
                dot.edge(str(u + 1), str(v + 1), label=str(w), color='red') 

        output_path = os.path.join(self.output_folder, 'user_boruvka_mst.png')
        dot.render(filename=output_path, format='png', cleanup=True)
        output_path_with_ext = output_path + ".png"
        print(f"MST visualization saved as '{output_path_with_ext}'.")
        os.startfile(output_path_with_ext)

def get_user_input():
    print("Enter the number of nodes:")
    nodes = int(input().strip())
    mst = BoruvkasMST(nodes)

    print("Enter the number of edges:")
    edges = int(input().strip())

    print("Enter each edge in the format 'start end weight':")
    for _ in range(edges):
        u, v, w = map(int, input("Edge (start end weight): ").strip().split())
        mst.add_edge(u, v, w)

    return mst

if __name__ == "__main__":
    mst = get_user_input()
    mst.boruvka_mst()
    mst.visualize_full_graph()
    mst.visualize_mst()
