#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>


class solver
{

private:

    const std::string _a;
    const char _x;
    const size_t _k;

    struct operand
    {

        size_t k;
        size_t smallest;
        size_t ans;
        std::map<size_t, size_t> prefixes;
        std::map<size_t, size_t> suffixes;
        std::set<size_t> repeating;

        static const size_t inf = ~static_cast<size_t>(1ull << 63);

        void metainfo() {
            std::cout << "k value: " << k << std::endl;
            std::cout << "prefixes: " << std::endl;
            for (auto i : prefixes) {
                std::cout << "(" << i.first << ' ' << i.second << ")" << std::endl;
            }
            std::cout << "suffixes: " << std::endl;
            for (auto i : suffixes) {
                std::cout << "(" << i.first << ' ' << i.second << ")" << std::endl;
            }
            std::cout << "repeating: " << std::endl;
            for (auto i : repeating) {
                std::cout << i << std::endl;
            }
            std::cout << "ans: " << ans << std::endl;
            std::cout << "smallest: " << smallest << std::endl;
            std::cout << "---------------------" << std::endl << std::endl;
        }

        operand(char C, char x, size_t k) : k(k) {
            if (C == '1') {
                ans = inf;
                smallest = 0;
                prefixes[0] = 0;
                suffixes[0] = 0;
            }
            else if (C == x) {
                smallest = 1;
                repeating.insert(1);
                if (k == 1) {
                    ans = 1;
                }
                else {
                    ans = inf;
                }
            }
            else {
                smallest = 1;
                ans = inf;
                prefixes[0] = 1;
                suffixes[0] = 1;
            }
        }

        static void insert_or_update(std::map<size_t, size_t>& mp, size_t val1, size_t val2) {
            auto it = mp.find(val1);
            if (it == mp.end()) {
                mp[val1] = val2;
            }
            else {
                it->second = std::min(it->second, val2);
            }
        }

        void concat(const operand& rhs) {
            ans = std::min(ans + rhs.smallest, smallest + rhs.ans);
            for (auto& i : suffixes) {
                for (auto& j : rhs.prefixes) {
                    if (i.first + j.first >= k) {
                        ans = std::min(ans, i.second + j.second);
                    }
                }
                for (auto& j : rhs.repeating) {
                    if (i.first + j >= k) {
                        ans = std::min(ans, i.second + j);
                    }
                }
            }
            for (auto& i : repeating) {
                for (auto& j : rhs.prefixes) {
                    if (i + j.first >= k) {
                        ans = std::min(ans, i + j.second);
                    }
                }
                for (auto& j : rhs.repeating) {
                    if (i + j >= k) {
                        ans = std::min(ans, i + j);
                    }
                }
            }
            std::map<size_t, size_t> new_prefixes;
            std::map<size_t, size_t> new_suffixes;
            std::set<size_t> new_repeating;
            for (auto& i : prefixes) {
                new_prefixes[i.first] = i.second + rhs.smallest;
            }
            for (auto& i : rhs.suffixes) {
                new_suffixes[i.first] = smallest + i.second;
            }
            for (auto& i : repeating) {
                for (auto& j : rhs.prefixes) {
                    insert_or_update(new_prefixes, i + j.first, i + j.second);
                }
            }
            for (auto& i : suffixes) {
                for (auto& j : rhs.repeating) {
                    insert_or_update(new_suffixes, i.first + j, i.second + j);
                }
            }
            for (auto& i : repeating) {
                for (auto& j : rhs.repeating) {
                    new_repeating.insert(i + j);
                }
            }
            prefixes = new_prefixes;
            suffixes = new_suffixes;
            repeating = new_repeating;
            smallest += rhs.smallest;
        }

        void uni(const operand& rhs) {
            ans = std::min(ans, rhs.ans);
            smallest = std::min(smallest, rhs.smallest);
            for (const auto& i : rhs.prefixes) {
                insert_or_update(prefixes, i.first, i.second);
            }
            for (const auto& i : rhs.suffixes) {
                insert_or_update(suffixes, i.first, i.second);
            }
            for (const auto& i : rhs.repeating) {
                repeating.insert(i);
            }
        }

        void brut(std::set<size_t>::iterator it, size_t cur_rep, size_t exc_len) {
            if (it == repeating.end()) {
                return;
            }
            else {
                auto nxt = it;
                ++nxt;
                for (size_t i = 0;; ++i) {
                    if (cur_rep + *it * i >= k) {
                        ans = std::min(ans, cur_rep + *it * i + exc_len);
                        return;
                    }
                    brut(nxt, cur_rep + *it * i, exc_len);
                }
            }
        }

        void repeat() {
            smallest = 0;
            insert_or_update(prefixes, 0, 0);
            insert_or_update(suffixes, 0, 0);
            for (auto& i : suffixes) {
                for (auto& j : prefixes) {
                    if (i.first + j.first >= k) {
                        //std::cout << "errrrrrrrrrrrrrrrrrrrrrrrrrrr\n";
                        ans = std::min(ans, i.second + j.second);
                    }
                    else {
                        brut(repeating.begin(), i.first + j.first, i.second + j.second);
                    }
                }
            }
        }

    };

public:

    solver(const std::string& a, const char x, const size_t k) : _a(a), _x(x), _k(k) {
        if (a.empty()) {
            throw std::logic_error("Regex is empty");
        }
    }

    size_t solve() {
        std::stack<operand, std::vector<operand>> operands;
        for (size_t i = 0; i < _a.size(); ++i) {
            const char cur = _a[i];
            switch (cur) {
                case '+': {
                    if (operands.size() < 2) {
                        throw std::out_of_range(
                            ("Invalid regex provided. There are no operands for + operator in position " + std::to_string(i)).c_str()
                        );
                    }
                    auto tmp = operands.top();
                    operands.pop();
                    operands.top().uni(tmp);
                    //std::cout << "uni:\n";
                    //operands.top().metainfo();
                    break;
                }
                case '.': {
                    if (operands.size() < 2) {
                        throw std::out_of_range(
                            ("Invalid regex provided. There are no operands for . operator in position " + std::to_string(i)).c_str()
                        );
                    }
                    auto tmp = operands.top();
                    operands.pop();
                    operands.top().concat(tmp);
                    //std::cout << "concat:\n";
                    //operands.top().metainfo();
                    break;
                }
                case '*': {
                    if (operands.size() < 1) {
                        throw std::out_of_range(
                            ("Invalid regex provided. There are no operands for * operator in position " + std::to_string(i)).c_str()
                        );
                    }
                    operands.top().repeat();
                    //std::cout << "repeat:\n";
                    //operands.top().metainfo();
                    break;
                }
                default: {
                    operands.emplace(cur, _x, _k);
                    //std::cout << "create:\n";
                    //operands.top().metainfo();
                    break;
                }
            }
        }
        if (operands.size() != 1) {
            throw std::logic_error(
                ("Invalid language provided. Parsing exited with " + std::to_string(operands.size()) + " operands").c_str()
            );
        }
        return operands.top().ans;
    }

};
