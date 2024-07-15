#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>

using namespace std;

class Graph {
private:
    unordered_map<char, list<char>> adj; // Adjacency list menggunakan unordered_map

public:
    // Konstruktor
    Graph() {}

    // Fungsi untuk menambahkan simpul baru
    void tambahVertex(char v) {
        if (adj.find(v) == adj.end()) { // Cek apakah vertex sudah ada
            adj[v] = list<char>(); // Jika tidak, tambahkan vertex baru
            cout << "Vertex " << v << " ditambahkan.\n";
        } else {
            cout << "Vertex " << v << " sudah ada.\n";
        }
    }

    // Fungsi untuk menghapus simpul
    void hapusVertex(char v) {
        if (adj.find(v) == adj.end()) { // Cek apakah vertex ada
            cout << "Simpul tidak ada.\n";
            return;
        }

        // Menghapus semua edge yang mengarah ke simpul v
        for (auto& pair : adj) {
            pair.second.remove(v); // Hapus edge yang menuju ke vertex v
        }

        adj.erase(v); // Hapus vertex dari adjacency list
        cout << "Vertex " << v << " dihapus.\n";
    }

    // Fungsi untuk menambahkan edge ke graph
    void tambahEdge(char v, char w) {
        if (adj.find(v) == adj.end() || adj.find(w) == adj.end()) { // Cek apakah kedua vertex ada
            cout << "Simpul tidak ada.\n";
            return;
        }
        adj[v].push_back(w); // Tambahkan w ke list v
        cout << "Edge ditambahkan dari " << v << " ke " << w << ".\n";
    }

    // Fungsi untuk menghapus edge dari graph
    void hapusEdge(char v, char w) {
        if (adj.find(v) == adj.end()) { // Cek apakah vertex v ada
            cout << "Simpul tidak ada.\n";
            return;
        }
        adj[v].remove(w); // Hapus w dari list v
        cout << "Edge dihapus dari " << v << " ke " << w << ".\n";
    }

    // Fungsi BFS
    void BFS(char s) {
        if (adj.find(s) == adj.end()) { // Cek apakah vertex s ada
            cout << "Simpul tidak ada.\n";
            return;
        }
        unordered_map<char, bool> visited; // Map untuk menandai simpul yang sudah dikunjungi
        for (auto& pair : adj) {
            visited[pair.first] = false; // Tandai semua simpul sebagai belum dikunjungi
        }

        queue<char> queue; // Queue untuk BFS
        visited[s] = true; // Tandai simpul awal sebagai sudah dikunjungi
        queue.push(s);

        while (!queue.empty()) {
            s = queue.front();
            cout << s << " ";
            queue.pop();

            // Periksa semua simpul tetangga
            for (auto adjecent : adj[s]) {
                if (!visited[adjecent]) {
                    visited[adjecent] = true;
                    queue.push(adjecent);
                }
            }
        }
        cout << endl;
    }

    // Fungsi utilitas DFS
    void DFSUtil(char v, unordered_map<char, bool>& visited) {
        visited[v] = true; // Tandai simpul v sebagai sudah dikunjungi
        cout << v << " ";

        // Rekursif untuk semua simpul tetangga
        for (auto adjecent : adj[v]) {
            if (!visited[adjecent]) {
                DFSUtil(adjecent, visited);
            }
        }
    }

    // Fungsi DFS
    void DFS(char v) {
        if (adj.find(v) == adj.end()) { // Cek apakah vertex v ada
            cout << "Simpul tidak ada.\n";
            return;
        }
        unordered_map<char, bool> visited; // Map untuk menandai simpul yang sudah dikunjungi
        for (auto& pair : adj) {
            visited[pair.first] = false; // Tandai semua simpul sebagai belum dikunjungi
        }

        DFSUtil(v, visited); // Panggil fungsi utilitas DFS
        cout << endl;
    }

    // Fungsi untuk mencari jalur antara dua simpul
    bool searchPathUtil(char u, char v, unordered_map<char, bool>& visited) {
        if (u == v) return true; // Jika u sama dengan v, jalur ditemukan
        visited[u] = true; // Tandai simpul u sebagai sudah dikunjungi

        // Periksa semua simpul tetangga
        for (char adjecent : adj[u]) {
            if (!visited[adjecent]) {
                if (searchPathUtil(adjecent, v, visited)) {
                    return true; // Jika jalur ditemukan, kembalikan true
                }
            }
        }
        return false; // Jika tidak ditemukan, kembalikan false
    }

    void searchPath(char u, char v) {
        if (adj.find(u) == adj.end() || adj.find(v) == adj.end()) { // Cek apakah kedua vertex ada
            cout << "Simpul tidak ada.\n";
            return;
        }
        unordered_map<char, bool> visited; // Map untuk menandai simpul yang sudah dikunjungi
        for (auto& pair : adj) {
            visited[pair.first] = false; // Tandai semua simpul sebagai belum dikunjungi
        }

        if (searchPathUtil(u, v, visited)) {
            cout << "Jalur ditemukan dari " << u << " ke " << v << ".\n";
        } else {
            cout << "Jalur tidak ditemukan dari " << u << " ke " << v << ".\n";
        }
    }

    // Fungsi untuk menampilkan semua vertex beserta edge
    void tampilkanGraph() {
        for (auto& pair : adj) {
            cout << pair.first << " : ";
            for (char adjecent : pair.second) {
                cout << adjecent << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    char choice, v, w, u;
    Graph g;

    do {
        cout << "PROGRAM GRAPH" << endl;
        cout << "1. Tambah Vertex (Node)\n";
        cout << "2. Hapus Vertex (Node)\n";
        cout << "3. Tambah Edge (Simpul)\n";
        cout << "4. Hapus Edge (Simpul)\n";
        cout << "5. Search Path\n";
        cout << "6. BFS\n";
        cout << "7. DFS\n";
        cout << "8. Tampilkan Graph\n";
        cout << "9. Exit\n";
        cout << "Pilihan: ";
        cin >> choice;

        system("cls"); // Hapus layar (hanya berfungsi di Windows)

        switch (choice) {
        case '1':
            cout << "Masukkan vertex: ";
            cin >> v;
            g.tambahVertex(v);
            system("pause");
            system("cls");
            break;
        case '2':
            cout << "Masukkan vertex yang akan dihapus: ";
            cin >> v;
            g.hapusVertex(v);
            system("pause");
            system("cls");
            break;
        case '3':
            cout << "Masukkan edge (format: v w): ";
            cin >> v >> w;
            g.tambahEdge(v, w);
            system("pause");
            system("cls");
            break;
        case '4':
            cout << "Masukkan edge yang akan dihapus (format: v w): ";
            cin >> v >> w;
            g.hapusEdge(v, w);
            system("pause");
            system("cls");
            break;
        case '5':
            cout << "Masukkan dua vertex (format: u v): ";
            cin >> u >> v;
            g.searchPath(u, v);
            system("pause");
            system("cls");
            break;
        case '6':
            cout << "Masukkan starting vertex untuk BFS: ";
            cin >> v;
            g.BFS(v);
            system("pause");
            system("cls");
            break;
        case '7':
            cout << "Masukkan starting vertex untuk DFS: ";
            cin >> v;
            g.DFS(v);
            system("pause");
            system("cls");
            break;
        case '8':
            g.tampilkanGraph();
            system("pause");
            system("cls");
            break;
        case '9':
            cout << "Terima kasih telah mencoba program ini.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (choice != '9');

    return 0;
}