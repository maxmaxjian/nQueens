#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iterator>
#include <algorithm>

class solution {
  public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::vector<int>> cands;
        for (int i = 0; i < n; i++) {
            auto temp = addOne(n, std::vector<int>{i});
            for (auto tmp : temp)
                cands.push_back(tmp);
        }

        std::vector<std::vector<std::string>> result;
        std::transform(cands.begin(), cands.end(), std::inserter(result, result.begin()),
                       [&](const std::vector<int> & vec){
                           return vec2str(vec);
                       });
        return result;
    }

  private:
    std::vector<std::vector<int>> addOne(int n, const std::vector<int> & curr) {
        std::vector<std::vector<int>> result;
        if (curr.size() == n)
            result.push_back(curr);
        else if (curr.size() < n){            
            std::vector<int> vec;
            int count = 0;
            std::generate_n(std::inserter(vec, vec.begin()), n, [&](){return count++;});
            std::vector<int> next;
            std::copy_if(vec.begin(), vec.end(), std::inserter(next, next.begin()),
                         [&](int i){
                             return isValid(curr, i);
                         });

            for (auto nx : next) {
                auto cpy = curr;
                cpy.push_back(nx);
                auto temp = addOne(n, cpy);
                for (auto tmp : temp)
                    result.push_back(tmp);
            }
        }
        return result;
    }

    bool isValid(const std::vector<int> & vec, int val) {
        if (std::find(vec.begin(), vec.end(), val) != vec.end())
            return false;
        for (size_t i = 0; i < vec.size(); i++)
            if (abs(int(i)-int(vec.size())) == abs(int(vec[i])-int(val)))
                return false;
        return true;
    }

    std::vector<std::string> vec2str(const std::vector<int> & vec) {
        std::vector<std::string> strs;
        std::transform(vec.begin(), vec.end(), std::inserter(strs, strs.begin()),
                       [&](int i){
                           std::string s(vec.size(), '.');
                           s[i] = 'Q';
                           return s;
                       });
        return strs;
    }
};

int main() {
    int numQ = 8;

    solution soln;
    auto sols = soln.solveNQueens(numQ);
    std::cout << "All the solutions are:\n";
    for (auto sol : sols) {
        std::copy(sol.begin(), sol.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
        std::cout << std::endl;
    }
}
