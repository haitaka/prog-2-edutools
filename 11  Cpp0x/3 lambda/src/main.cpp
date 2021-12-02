#include <iostream>
#include <vector>
#include <functional>

struct Filter {
    int k;

    bool operator()(int x) const {
        return x > k;
    }
};

void printFiltered(std::vector<int> const & data, std::function<bool(int)> const & filter) {
    for (int x : data) {
        if (filter(x)) {
            std::cout << x << std::endl;
        }
    }
}

bool isEven(int x) {
    return x % 2 == 0;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> data = {4, 8, 15, 16, 23, 42};

    std::function<bool(int)> filterEven = isEven;
    std::function<bool(int)> filterGreater = Filter{n};
    std::function<bool(int)> filterGreaterL = [=](int x){
        return x > n;
    };

    n = 23;

    std::cout << "even" << std::endl;
    printFiltered(data, filterEven);
    std::cout << "greater than " << n << std::endl;
    printFiltered(data, filterGreater);
    std::cout << "(lambda) greater than " << n << std::endl;
    printFiltered(data, filterGreaterL);

    return 0;
}
