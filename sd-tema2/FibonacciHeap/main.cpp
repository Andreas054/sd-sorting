#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("mergeheap.in");
ofstream fout("mergeheap.out");

class node {
public:
    int n;
    int degree;
    node *child;
    node *left;
    node *right;
};

const int MAX_NODES = 1000000;
node nodes[MAX_NODES];
int next_free_node = 0;

class FibonacciHeap {
public:
    int nH;

    node *insert(node *, int);
    void fib_leg(node *, node *, node *);
    node *fib_union(node *, node *);
    node *extract_min(node *);
    void fib_repair(node *);
    void display_root(node *);
    FibonacciHeap() {
        nH = 0;
    }
};

node *FibonacciHeap::insert(node *H, int value) {
//    node *x = new node;
    node *x = &nodes[next_free_node];
    next_free_node++;



    x->n = value;

    x->degree = 0;
    x->child = NULL;
    x->left = x;
    x->right = x;
    if (H == NULL) {
        H = x;
    } else {
        (H->left)->right = x;
        x->right = H;
        x->left = H->left;
        H->left = x;
        if (x->n < H->n)
            H = x;
    }
    nH = nH + 1;

    return H;
}

void FibonacciHeap::fib_leg(node *H1, node *y, node *z) {
    (y->left)->right = y->right;
    (y->right)->left = y->left;
    if (z->right == z)
        H1 = z;
    y->left = y;
    y->right = y;

    if (z->child == NULL)
        z->child = y;

    y->right = z->child;
    y->left = (z->child)->left;
    ((z->child)->left)->right = y;
    (z->child)->left = y;

    if (y->n < (z->child)->n)
        z->child = y;
    z->degree++;
}

node *FibonacciHeap::fib_union(node *H1, node *H2) {
    node *np;
    node *H = NULL;
    if (H1 != NULL && H2 != NULL) {
        H = H1;
        (H->left)->right = H2;
        (H2->left)->right = H;
        np = H->left;
        H->left = H2->left;
        H2->left = np;
    }
    else {
        if (H1 == NULL)
            H = H2;
        else
            H = H1;
    }
    return H;
}

void FibonacciHeap::display_root(node *H) {
    node *p = H;
    /*
    if (p == NULL) {
        cout << "Empty Heap" << endl;
    }
    else {
        cout << "Root Nodes: " << endl;

        do {
            cout << p->n;
            p = p->right;
            if (p != H) {
                cout << " - ";
            }
        } while (p != H && p->right != NULL);
        cout << endl;
    }
    */
    if (p != NULL) {
        fout << p->n << "\n";
    }
}

node *FibonacciHeap::extract_min(node *H1) {
    node *z = H1;

    if (z == NULL)
        return z;

    node *x = NULL;

    if (z->child != NULL) {
        x = z->child;

        x->left->right = H1->left;
        (H1->left)->right = x;
        (H1->left)->left = x->left;
        x->left = H1->left;

        // NOT OK
        H1 = x;
//        cout << "Afisare\t" << H1->n << H1->right->n << H1->right->right->n << endl;

        fib_repair(H1);
    }
    else {
        (z->left)->right = z->right;
        (z->right)->left = z->left;

        if (z == z->right && z->child == NULL)
            H1 = NULL;
        else {
            H1 = z->right;
            fib_repair(H1);
        }
    }
    nH = nH - 1;

    return H1;
}

int countNoRoot(node *H1) {
    int nr = 0;
    node *p = H1;
    do {
        nr++;
        p = p->right;
    } while(p != H1);
    return nr;
}

void FibonacciHeap::fib_repair(node *H1) {
    int degree, i;
    float f = (log(nH)) / (log(2));
    int D = f;
//    std::cout<<"D="<<D<<endl;

    vector<vector<node*>> A;

    for (i = 0; i <= D; i++) {
        vector<node *> tmp;
        A.push_back(tmp);
    }

    node *x = H1;
    node *y, *z;
    int poz = 0;

    int test = 0;
    int nr = 0;
    do {
        test+=1;
        degree = x->degree;

        auto i = A[degree].begin();
        for (i = A[degree].begin(); i != A[degree].end(); ++i) {
            if (x == *i)
                break;
        }
        if (i == A[degree].end()) {
            A[degree].push_back(x);
        }

        while (A[degree].size() > 1) {
            nr++;
            y = A[degree].back();
            A[degree].pop_back();
            z = A[degree].back();
            A[degree].pop_back();

//            cout << y->n << "=y\tz=" << z->n << endl;

//            if (y->n == 17 && z->n ==3) {
//                cout << "SPECIALE======\n";
//                cout << H1->n << "\t" << H1->right->n << "\t" << H1->right->right->n << endl;;
//                cout << H1->child->n << "\t" << H1->right->child->n << endl;
//                cout << "==============\n";
//            }

            if (z->n > y->n) {
                swap(y, z);
            }
            if (y == H1) {
                H1 = z;
            }

            fib_leg(H1, y, z);


//            if (y->n == 17 && z->n ==3) {
//                cout << "SPECIALE2=====\n";
//                cout << H1->n << "\t\t" << H1->right->n << endl;;
//                cout << H1->child->n << "\t" << H1->child->right->n << endl;
//                cout << "\t" << H1->child->right->child->n << endl;
//                cout << "==============\n";
//            }
//
//            if (y->n == 37 && z->n == 24) {
//                cout << "SPECIALE3=====\n";
//                cout << H1->n << "\t\t" << H1->right->n << endl;;
//                cout << H1->child->n << "\t" << H1->child->right->n << "\t" << H1->right->child->n << endl;
//                cout << "\t" << H1->child->right->child->n << endl;
//                cout << "==============\n";
//            }
//
//            if (y->n == 24 && z->n == 7) {
//                cout << "SPECIALE4=====\n";
//                cout << H1->n << endl;;
//                cout << H1->child->n << "\t" << H1->child->left->n << endl;
//                cout << "==============\n";
//            }
//
//            if (y->n == 17 && z->n == 7) {
//                cout << "SPECIALE5=====\n";
//                cout << H1->n << endl;
//                cout << H1->child->n << "\t" << H1->child->left->n << endl;
//                cout << H1->child->child->n << endl;
//                cout << "==============\n";
//            }
//
//            if (y->n == 24 && z->n == 17) {
//                cout << "SPECIALE6=====\n";
//                cout << H1->n << "\t" << H1->right->n << endl;
//                cout << "\t" << H1->right->child->n << "\t" << H1->right->child->right->n << endl;
//                cout << "\t" << H1->right->child->child->n << endl;
//                cout << "==============\n";
//            }

            if (z->right == z)
                H1 = z;

            poz -= 2;
        }

        poz++;

        x = H1;
        for (int i = 0; i < poz; i++) {
            x = x->right;
        }

//        for (auto i = A.begin(); i != A.end(); ++i) {
//            cout << "Dim=" << i->size() << endl;
//        }

    //} while (x != H1);
//    } while (test<10000);           // ??????????????????????????????????????????????????????????????????????????????????????? conditie de opririe
    } while (countNoRoot(H1) - 1 > D);

//    cout << "NR=" << nr<<endl;
}

int main() {
    int n, q, tipOp, a, b;
    vector<FibonacciHeap> fh;
    vector<node*> H;
    fin >> n >> q;
    for (int i = 0; i < n; ++i) {
        H.push_back(NULL);
        FibonacciHeap fhTMP;
        fh.push_back(fhTMP);
    }
    for (int i = 0; i < q; ++i) {
        fin >> tipOp >> a;
        switch(tipOp) {
            case 1: {
                fin >> b;
                H[a - 1] = fh[a - 1].insert(H[a - 1],  b);
                break;
            }
            case 2: {
                H[a - 1] = fh[a - 1].extract_min(H[a - 1]);
                fh[a-1].display_root(H[a-1]);
                break;
            }
            case 3: {
                fin >> b;
                H[a - 1] = fh[a - 1].fib_union(H[a - 1], H[b - 1]);
                H[b - 1] = NULL;
                break;
            }
        }
    }




//    FibonacciHeap fh1, fh2;
//    node *H1, *H2;
//    H1 = NULL;
//    H2 = NULL;
//
//    H1 = fh1.insert(H1, 3);
//    H1 = fh1.insert(H1, 7);
//    H1 = fh1.insert(H1, 17);
//    H1 = fh1.insert(H1, 27);
//    H1 = fh1.insert(H1, 37);
//    H1 = fh1.insert(H1, 24);
//    H1 = fh1.insert(H1, 1);
//
//    fh1.display_root(H1);
//
//    H1 = fh1.extract_min(H1);
//    H1 = fh1.extract_min(H1);
//
//    fh1.display_root(H1);
//
//
//
//
//    H2 = fh2.insert(H2, 6);
//    H2 = fh2.insert(H2, 5);
//    H2 = fh2.insert(H2, 10);
//    H2 = fh2.insert(H2, 9);
//    H2 = fh2.extract_min(H2);
//    fh2.display_root(H2);
//
//    H1 = fh1.fib_union(H1, H2);
//    cout << "\nUNIONUNIONUNIONUNIONUNIONUNIONUNIONUNION\n";
//    fh1.display_root(H1);



    return 0;
}