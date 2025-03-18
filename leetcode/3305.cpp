#include "../helper/helper.h"
using std::string;

class Solution {
public:
    int countOfSubstrings(string word, int k) {
        int res{};
        std::set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        for (int i = 0; i < word.size(); i++) {
            int cnt{};
            std::set<char> o{};
            for (int j = i; j < word.size(); j++) {
                if (vowels.count(word[j])) {
                    o.insert(word[j]);
                } else {
                    cnt++;
                }
                if (o.size() == 5 && cnt == k) {
                    res++;
                }
            }
        }
        return res;
    }
};

int main() {
    string str{};
    int k{};
    read(str, k);
    std::cout << Solution().countOfSubstrings(str, k);
}