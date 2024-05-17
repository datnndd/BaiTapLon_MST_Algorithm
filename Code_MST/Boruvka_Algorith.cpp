#include <iostream>
#include <vector>
using namespace std;
//Lớp triển khai Disjoint Set Union
class DSU {
    int* parent;
public:
    DSU(int n) {
        parent = new int[n + 1];
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }
    // Tìm và trả về tập hợp chứa phần tử u
    int find_set(int u) {
        if (u == parent[u])   return u;
        return parent[u] = find_set(parent[u]);
    }
    // Hợp nhất hai tập hợp chứa u và v
    void union_set(int u, int v) {
        u = find_set(u);
        v = find_set(v);
        if (u == v) return;
        parent[u] = v;
    }
};
// Lớp biểu diễn một đồ thị
class Graph {
    int V; // Số đỉnh của đồ thị
    vector<vector<int> >edgeList; //dùng để lưu trữ các cạnh của đồ thị
                                  //mỗi cạnh lưu trữ 3 phần tử: u, v, w
public:
    Graph(int V): V(V) {};
    // phương thức thêm một cạnh với trọng số w giữa 2 đỉnh u và v;
    void addEdge(int u, int v, int w)
    {
        edgeList.push_back({ u, v, w });
    }
    //phương thức thực hiện thuật toán Boruvka
    void boruvkaMST()
    {
        DSU s(V);
        
        // danh sách cheapest lưu trữ cạnh nhỏ nhất cho mỗi tập hợp
        vector<vector<int>> cheapest(V + 1,vector<int>(3, -1));          
                                           
                                                                

        int numTrees = V;// dùng để theo dõi số lượng cây
                         // Ban đầu có V cây khác nhau
                         // Cuối cùng sẽ chỉ còn 1 cây, đó là cây khung nhỏ nhất
        int MSTweight = 0;
        cout << "Edges in MST: " << endl;
        cout << "Edge\tWeight" << endl;
        // Lặp cho đến khi chỉ còn 1 cây
        while (numTrees > 1) {

            // Duyệt qua tất cả các cạnh và
            // cập nhật cạnh nhỏ nhất của mỗi tập hợp
            for (vector<int> edge : edgeList) {
                
                int u = edge[0], v = edge[1],
                    w = edge[2];

                // Tìm tập hợp của hai đỉnh của cạnh hiện tại
                int set1 = s.find_set(u);
                int set2 = s.find_set(v);

                // Nếu hai đỉnh của cạnh hiện tại thuộc cùng một tập hợp
                // bỏ qua nó. Ngược lại, kiểm tra xem cạnh hiện tại có nhỏ
                // hơn so với các cạnh trước đó của cheapest[set1] và cheapest[set2] 
                if (set1 != set2) {
                    if (cheapest[set1][2] == -1
                        || cheapest[set1][2] > w) {
                        cheapest[set1] = { u, v, w };
                    }
                    if (cheapest[set2][2] == -1
                        || cheapest[set2][2] > w) {
                        cheapest[set2] = { u, v, w };
                    }
                }
            }
            // Xét các cạnh được chọn trong danh sách cheapest
            // hợp nhất các tập hợp tương ứng
            // và thêm chúng vào trong cây khung nhỏ nhất
            for (vector<int> edge : cheapest) {

                // Kiểm tra cheapest cho tập hiện tại tồn tại
                if (edge[2] != -1) {
                    int u = edge[0],
                        v = edge[1],
                        w = edge[2];
                    int set1 = s.find_set(u),
                        set2 = s.find_set(v);
                    if (set1 != set2) {
                        MSTweight += w;
                        s.union_set(set1, set2);
                        cout << u <<  "-" << v << "\t" << w << endl;
                        numTrees--;
                    }
                }
            }

            for (vector<int>& edge : cheapest) {
                // đặt lại danh sách cheapest
                // cho vòng lặp while tiếp theo
                edge[2] = -1;
            }
        }
        cout << "Weight of MST is: " << MSTweight << endl;
    }
};
int main(){
    //Nhập dữ liệu từ bàn phím
    //int num_v, num_e;
    //cin >> num_v >> num_e;
    //Graph g(num_v);
    //for (int i = 0; i < num_e; i++) {
    //    int u, v, w;
    //    cin >> u >> v >> w;
    //    g.addEdge(u, v, w);
    //}

    // Thêm dữ liệu trực tiếp
    Graph g(5);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 4);
    g.addEdge(2, 5, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);

    g.boruvkaMST();
    return 0;
}
