// Thuật toán tìm cây khung nhỏ nhất Prim
// viết bằng ngôn ngữ C++. Chương trình dành cho
// đồ thị được biểu diễn bằng ma trận liền kề.
// Ta sẽ không nhập đữ liệu bằng bàn phím ở đoạn code này.

#include <iostream>
using namespace std;

// Số đỉnh trong đồ thị
#define V 5

// Hàm này dùng để tìm đỉnh với giá 
// trị khóa nhỏ nhất, từ tập các đỉnh chưa
// nằm trong MST
int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// Hàm này dùng để in ra cấu trúc được
// lưu trữ trong mảng parent[] và giá trị của MST
void printMST(int parent[], int graph[V][V])
{
    int size = 0;
    cout << "Edges in MST: " << endl;
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " \t"
            << graph[i][parent[i]] << " \n";
        size += graph[i][parent[i]];
    }
    cout << "Total size of MST: " << size << endl;
}

// Hàm xây dựng và gọi hàm in MST ra màn hình
void primMST(int graph[V][V])
{
    // Mảng lưu trữ cấu trúc của MST
    int parent[V];

    // Giá trị khóa sử dụng để chọn cạnh
    // có trọng số nhỏ nhất từ vết cắt
    int key[V];

    // Cho biết các đỉnh đang nằm trongg MST
    bool mstSet[V];

    // Khởi tạo tất cả giá trị khóa ban đầu là INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Luôn có đỉnh đầu tiên là đỉnh bắt đầu trong MST
    // Tạo giá trị khóa 0 thể hiện đỉnh này được chọn đầu tiên
    key[0] = 0;

    // Node đầu tiên luôn là gốc của MST
    parent[0] = -1;

    // MST bao gồm V đỉnh
    for (int count = 0; count < V - 1; count++) {

        // Chọn đỉnh có khóa nhỏ nhất từ tập các
        // đỉnh chưa nằm trong MST
        int u = minKey(key, mstSet);

        // Thêm đỉnh được chọn ở trên vào trong MST
        mstSet[u] = true;

        // Cập nhật giá trị khóa và chỉ mục gốc
        // của các đỉnh liền kề của đỉnh đã chọn.
        // Chỉ xem xét những đỉnh chưa có trong MST
        for (int v = 0; v < V; v++)

            // graph[u][v] khác 0 chỉ với các đỉnh
            // liền kề của m, mstSet[v] là false cho mọi đỉnh
            // không nằm trong MST. Cập nhật giá trị khóa khi mà
            // graph[u][v] nhỏ hơn key[v]
            if (graph[u][v] && mstSet[v] == false
                && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // In ra cấu trúc MST
    printMST(parent, graph);
}

// Driver's code
int main()
{
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };

    // in ra kết quả
    primMST(graph);

    return 0;
}