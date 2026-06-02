int compute(int n) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += i;
        sum *= 2;
        sum -= 1;
        sum += 3;
        sum *= 4;
        sum -= 2;
    }

    return sum;
}

int main() {
    return compute(100);
}
