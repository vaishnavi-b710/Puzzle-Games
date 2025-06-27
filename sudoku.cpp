#include <iostream>
#include <stack>
#include <utility>
#include <cstdlib>

using namespace std;

typedef struct {
    int b[9][9]; 
} sudoku;

void clear(bool seen[10]) {
    for (int i = 0; i < 10; ++i) seen[i] = false;
}

bool is_valid(const sudoku& s) {
    bool seen[10];
    for (int row = 0; row < 9; ++row) {
        clear(seen);
        for (int col = 0; col < 9; ++col) {
            int v = s.b[row][col];
            if (v && seen[v]) return false;
            seen[v] = true;
        }
    }
    for (int col = 0; col < 9; ++col) {
        clear(seen);
        for (int row = 0; row < 9; ++row) {
            int v = s.b[row][col];
            if (v && seen[v]) return false;
            seen[v] = true;
        }
    }
    for (int boxrow = 0; boxrow < 9; boxrow += 3) {
        for (int boxcol = 0; boxcol < 9; boxcol += 3) {
            clear(seen);
            for (int r = 0; r < 3; ++r) {
                for (int c = 0; c < 3; ++c) {
                    int v = s.b[boxrow + r][boxcol + c];
                    if (v && seen[v]) return false;
                    seen[v] = true;
                }
            }
        }
    }
    return true;
}

sudoku place(const sudoku& s, int i, int j, int v) {
    sudoku t = s;
    t.b[i][j] = v;
    return t;
}

void print_board(const sudoku& s) {
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            int v = s.b[r][c];
            if (v == 0)
                cout << ". ";
            else
                cout << v << " ";
        }
        cout << endl;
    }
}

bool is_full(const sudoku& s) {
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            if (s.b[r][c] == 0) return false;
    return true;
}

pair<int, int> find_first_blank(const sudoku& s) {
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            if (s.b[r][c] == 0) return { r, c };
    return { -1, -1 };
}

sudoku solve(const sudoku& s) {
    stack<sudoku> st;
    st.push(s);

    while (!st.empty()) {
        sudoku v = st.top(); st.pop();
        if (is_full(v)) return v;

        pair<int, int> pos = find_first_blank(v);
        int i = pos.first, j = pos.second;
        if (i == -1) continue;

        for (int val = 1; val <= 9; ++val) {
            sudoku u = place(v, i, j, val);
            if (is_valid(u)) st.push(u);
        }
    }

    cout << "No solution exists.\n";
    exit(1);
}

int main() {
    sudoku s = { {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    } };

    cout << "Input Sudoku:\n";
    print_board(s);
    cout << "Solving...\n\n";

    sudoku solved = solve(s);
    cout << "Solved Sudoku:\n";
    print_board(solved);

    return 0;
}
