#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class PrimMST {
private:
    typedef long long ll;
    typedef pair<int, int> ii;

    const ll INF = 10e9 +1;

    int n; // số lượng đỉnh trong đồ thị
    vector<vector<ii>> adj; //Một vector của các vector cặp (ii)
                            //Đại diện cho danh sách kề của đồ thị
    vector<bool> mark;//Một vector boolenan để theo dõi các đỉnh đã được thăm
    vector<ll> dist;// là khoảng cách nhỏ nhất từ một đỉnh 
                    //đã được chọn vào cây khung đến đỉnh u.
    vector<int> parent;//Một vector int để lưu cha của mỗi đỉnh trong MST

public:
    // Phương thức khởi tạo đối tượng PrimMST với số đỉnh đã cho(numNodes)
    PrimMST(int numNodes) : n(numNodes),// đặt tổng số đỉnh(n) 
        adj(numNodes + 1), // tạo một danh sách kề (adj)
                           // với numNodes + 1 vector (một cho mỗi đỉnh)
        mark(numNodes + 1, false),//khởi tạo vector mark với numNodes + 1 phần tử
                            //(ban đầu đều là false)
        dist(numNodes + 1, INF),//khởi tạo vector dist với numNodes + 1 phần tử
                                //(ban đầu đặt tất cả khoảng cách là INF) 
        parent(numNodes + 1, -1) {}//Khởi tạo vector parent với numNodes + 1 phần tử,
                                    //đặt tất cả cha thành - 1.
     // Ta khởi tạo numNodes + 1 phần tử để dự phòng cho việc đánh số các đỉnh
     // từ 1 đến numNodes

    //Hàm thêm một cạnh vô hướng giữa các nút u và v với trọng số đã cho
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight));
    }

    //hàm tìm cây khung nhỏ nhất, đầu vào là 1 đỉnh bất kỳ
    //hàm trả về tổng trọng số của cây khung
    ll findMST(int source) {
        ll res = 0;
        // Một hàng đợi ưu tiên, lưu trữ cặp (ii) với thứ tự tăng dần
        // ở đây ii có giá trị first là dist[u], giá trị second là u (u là đỉnh)
        // nên pq sẽ lấy dist[u] để so sánh
        priority_queue<ii, vector<ii>, greater<ii>> pq;

        dist[source] = 0; // gán dist của đỉnh bắt đầu là 0
        pq.push(make_pair(0, source)); // thêm cặp(0, source) vào pq

        while (!pq.empty()) {
            int u = pq.top().second; //lấy đỉnh từ phần từ đầu tiên của pq
            pq.pop();// xóa phần tử vừa lấy
            if (mark[u]) continue;// nếu đỉnh u đã được đánh dẫu, tiếp tục vòng lặp
            mark[u] = true;//nếu chưa thì đánh dấu đỉnh u là đã thăm

            res += dist[u];// thêm khoảng cách của u vào kết quả

            //với mỗi cặp kề v của u 
            //(biểu diễn bằng cặp (v.first, v.second) trongdanh sách kề )
            //v.fisrt là đỉnh, v.second là cạnh nối giữa u và đỉnh đó
            //Nếu khoảng cách từ u đến v (v.second) nhỏ hơn khoảng cách được lưu trữ hiện tại (dist[v.first]):
            //Cập nhật cha của v.first thành u.
            //Cập nhật khoảng cách dist[v.first] thành giá trị mới(v.second).
            //Đẩy khoảng cách đã cập nhật và v.first vào pq.
            for (ii v : adj[u]) {
                if (v.second < dist[v.first]) {
                    parent[v.first] = u;
                    dist[v.first] = v.second;
                    pq.push(make_pair(dist[v.first], v.first));
                }
            }
        }

        return res;
    }

    // in ra cạnh của cây khung nhỏ nhất
    void printMST() {
        cout << "Edge \tWeight\n";
        for (int i = 2; i <= n; i++) {
            cout << parent[i] << " - " << i << " \t " <<dist[i]<< endl;
        }
    }
};

int main() {
    //Nhập từ bàn phím
    //int n, m
    //cin >> n >> m;

    //PrimMST prim(n);

    //for (int i = 0; i < m; ++i) {
    //    int u, v, k;
    //    cin >> u >> v >> k;
    //    prim.addEdge(u, v, k);
    //}
    
    //Thêm luôn dữ liệu
    int n = 5, m = 7;
    PrimMST prim(n);
    prim.addEdge(1, 2, 3); prim.addEdge(4, 5, 4);
    prim.addEdge(2, 4, 7); prim.addEdge(2, 5, 3);
    prim.addEdge(3, 5, 6); prim.addEdge(1, 3, 2);
    prim.addEdge(2, 3, 4);
    
    

    cout << "Weight of MST: " << prim.findMST(1) << endl;
    cout << "Edges in MST: " << endl;
    prim.printMST();

    return 0;
}
