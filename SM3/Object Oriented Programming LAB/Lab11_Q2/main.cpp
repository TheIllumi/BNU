#include <iostream>
#include <vector>
using namespace std;

class Data {
protected:
    vector<int> numbers;

public:
    explicit Data(const vector<int>& nums) : numbers(nums) {}

    void display() const {
        for (int num : numbers) {
            cout << num << " ";
        }
        cout << endl;
    }
};

class Statistics : private Data {
public:
    explicit Statistics(const vector<int>& nums) : Data(nums) {}

    [[nodiscard]] int sum() const {
        int total = 0;
        for (int num : numbers) {
            total += num;
        }
        return total;
    }
};

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    Statistics stats(nums);
    cout << stats.sum() << endl;
    return 0;
}