#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin( "mergeheap.in");
ofstream fout("mergeheap.out");

class MergeHeap {
public:
    struct node {
        long long n;
        node *left;
        node *right;

        node(long long n) {
            this->n = n;
            left = nullptr;
            right = nullptr;
        }
    };

    node* Hroot;

    MergeHeap() {
        Hroot = nullptr;
    }

    void insert(long long x) {
        node *new_node = new node(x);
        Hroot = mh_union(Hroot, new_node);
    }

    long long extract_min() {
        if (Hroot) {
            long long minn = Hroot->n;
            node *old_root = Hroot;
            Hroot = mh_union(Hroot->left, Hroot->right);
            delete old_root;
            return minn;
        }
    }

    static MergeHeap merge(MergeHeap& H1, MergeHeap& H2) {
        MergeHeap merged_heap;
        merged_heap.Hroot = mh_union(H1.Hroot, H2.Hroot);
        H1.Hroot = nullptr;
        H2.Hroot = nullptr;
        return merged_heap;
    }

    static node *mh_union(node *nod1, node *nod2) {
        if (nod1 == nullptr) {
            return nod2;
        }
        if (nod2 == nullptr) {
            return nod1;
        }
        if (nod1->n > nod2->n) {
            swap(nod1, nod2);
        }
        nod1->right = mh_union(nod1->right, nod2);
        swap(nod1->left, nod1->right);
        return nod1;
    }
};

int main() {
    int n, q, tipOp;
    long long a, b;
    vector<MergeHeap> h;
    fin >> n >> q;
    for (int i = 0; i < n; ++i) {
        MergeHeap hTMP;
        h.push_back(hTMP);
    }
    for (int i = 0; i < q; ++i) {
        fin >> tipOp >> a;
        switch(tipOp) {
            case 1: {
                fin >> b;
                h[a - 1].insert((-1) * b);
                break;
            }
            case 2: {
                fout << (-1) * h[a - 1].extract_min() << "\n";
                break;
            }
            case 3: {
                fin >> b;
                h[a - 1] = MergeHeap::merge(h[a - 1], h[b - 1]);
                break;
            }
        }
    }
    return 0;
}
