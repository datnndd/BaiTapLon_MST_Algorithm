#include <iostream>
#include <vector>
//#include <algorithm>
using namespace std;

//Cấu trúc dữ liệu DSU
class DSU {
    int* parent; // một mảng lưu trữ đỉnh cha của các node
public:
    //Hàm khởi tạo hàm mảng parent với mỗi phần tử trỏ đến chỉnh nó
    DSU(int n) {
        parent = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    // Hàm đệ quy tìm gốc của node u
    int find_set(int u) {
        if (u == parent[u]) return u;
        return parent[u] = find_set(parent[u]);
    }
    // Hợp nhất 2 tập hợp u, v bằng cách cập nhật cha của chúng
    void union_set(int u, int v) {
        u = find_set(u);
        v = find_set(v);
        if (u == v) return;
        parent[u] = v;
    }
};
//Ta có thể coi edgelist là 1 mảng 2 chiều, khi đó:
//edgelist[][0]: là u (đỉnh thứ 1)
//edgelist[][1]: là v (đỉnh thứ 2)
//edgelist[][2]: là w (trọng số)
//Vậy nên hàm quickSort này sẽ sắp xếp edgelist theo trọng số
void quickSort(vector<vector<int>>& edgelist, int left, int right) {
    if (left >= right) return;
    int i = left, j = right;
    int pivot = edgelist[(left + right) / 2][2];
    while (i <= j) {
        while (edgelist[i][2] < pivot) i++;
        while (edgelist[j][2] > pivot) j--;
        if (i <= j) {
            swap(edgelist[i], edgelist[j]);
            i++;
            j--;
        }
    }
    quickSort(edgelist, left, j);
    quickSort(edgelist, i, right);
}
////hàm so sánh trọng số của 2 cạnh, sử dụng nếu dùng hàm sort
  //trong thư viện algorithm để sắp xếp
//static bool compareEdge (const vector<int>& edge1, const vector<int>& edge2) {
//    return edge1[2] < edge2[2];
//}

class Graph {
    vector<vector<int>> edgelist; // dùng để lưu trữ các cạnh của đồ thị, mỗi cạnh gồm 
                                  // 3 chỉ số: u(đỉnh thứ 1), v(đỉnh thứ 2), w(trọng số)
    int V; // số đỉnh của đồ thị

public:
    //khởi tạo một đối tượng Graph với số đỉnh là V
    Graph(int V) : V(V) {}

    //hàm thêm cạnh vào edgelist
    void addEdge(int u, int v, int w) {
        edgelist.push_back({ u, v, w });
    }

    void kruskals_mst() {
        //sort(edgelist.begin(), edgelist.end(), compareEdge);
        quickSort(edgelist, 0, edgelist.size() - 1);

        DSU s(V);
        int MST_Cost = 0;
        cout << "Following are the edges in the constructed MST:" << endl;
        cout << "Edge\tWeight\t" << endl;
        // Lần lượt duyệt qua các cạnh trong danh sách cạnh đã được sắp xếp
        // Nếu hai đỉnh chưa liên thông(cạnh nối giữa 2 đỉnh không tạo chu trình)
        // thêm trọng số cạnh đó vào kết quả, hợp nhất 2 tập hợp chứa 2 đỉnh
        for (vector<int> edge : edgelist) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            if (s.find_set(u) != s.find_set(v)) {
                s.union_set(u, v);
                MST_Cost += w;
                cout << u << " - " << w << "\t" << w << endl;
            }
        }
        cout << "Minimum Cost Spanning Tree: " << MST_Cost << endl;
    }
};
int main() {
    //Nhập dữ liệu từ bàn phím
    //int v, num_e;
    //cin >> v >> num_e;
    //Graph g(v);
    //for (int i = 0; i < num_e; i++) {
    //	int u, v, w;
    //	cin >> u >> v >> w;
    //	g.addEdge(u, v, w);
    //}

    //Thêm luôn dữ liệu
    Graph g(5);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 4);
    g.addEdge(2, 5, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);

    //hiển thị kết quả
    g.kruskals_mst();
    return 0;
}
