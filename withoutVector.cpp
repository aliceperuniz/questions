#include <iostream>
#include <set>

using namespace std;

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector *v, size_t initial_capacity) {
    v->data = new int[initial_capacity];
    v->size = 0;
    v->capacity = initial_capacity;
}

void vector_add(Vector *v, int value) {
    if (v->size >= v->capacity) {
        v->capacity *= 2;
        int *new_data = new int[v->capacity];
        for (size_t i = 0; i < v->size; i++) {
            new_data[i] = v->data[i];
        }
        delete[] v->data;
        v->data = new_data;
    }
    v->data[v->size] = value;
    v->size++;
}

void vector_free(Vector *v) {
    delete[] v->data;
    v->data = nullptr;
    v->size = 0;
    v->capacity = 0;
}

void vector_print(const Vector *v) {
    for (size_t i = 0; i < v->size; i++) {
        cout << v->data[i] << " ";
    }
    cout << endl;
}

void findCombinations(int n, int index, const int* coins, Vector* current, set<string>& result) {
    if (n == 0) {
        string combination;
        for (size_t i = 0; i < current->size; i++) {
            combination += to_string(current->data[i]);
            if (i < current->size - 1) {
                combination += ",";
            }
        }
        result.insert(combination);
        return;
    }
    if (n < 0 || index < 0) {
        return;
    }

    for (int count = 0; count <= n / coins[index]; count++) {
        while (current->size <= index) {
            vector_add(current, 0);
        }
        current->data[index] = count;
        findCombinations(n - count * coins[index], index - 1, coins, current, result);
    }

    current->data[index] = 0;
}

void makeChange(int n, set<string>& result) {
    int coins[] = {25, 10, 5, 1};
    Vector current;
    vector_init(&current, 4);

    findCombinations(n, 3, coins, &current, result);
    vector_free(&current);
}

int main() {
    int n;
    cin >> n;

    set<string> combinations;
    makeChange(n, combinations);

    cout << "[";
    bool first = true;
    for (const auto& combination : combinations) {
        if (!first) {
            cout << ",";
        }
        cout << "[" << combination << "]";
        first = false;
    }
    cout << "]";

    return 0;
}
