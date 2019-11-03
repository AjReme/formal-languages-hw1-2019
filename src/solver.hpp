#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>


class __solver
{

private:

    const char null_word = '1';
    const size_t inf = static_cast<size_t>(1ull << 60);

    struct auto_node
    {

        struct edge {
            size_t to;
            char symb;
        };

        std::vector<edge> next_nodes;

        void push(size_t next, char symb) {
            next_nodes.push_back({ next, symb });
        }

        auto_node() = default;

        ~auto_node() = default;

    };

    struct automata { size_t begin, end; };

    struct repeat_pair { size_t begin, end; };

    struct step { size_t begin, cur, len; };

    std::vector<auto_node> auto_nodes;
    std::vector<std::vector<size_t>> dist;
    std::vector<repeat_pair> possible_pairs;

    automata create_automata(char symb) {
        size_t begin = auto_nodes.size();
        size_t end = begin + 1;
        auto_nodes.emplace_back();
        auto_nodes.emplace_back();
        auto_nodes[begin].push(end, symb);
        return { begin, end };
    }

    automata unite_automata(automata lhs, automata rhs) {
        size_t begin = auto_nodes.size();
        size_t end = begin + 1;
        auto_nodes.emplace_back();
        auto_nodes.emplace_back();
        auto_nodes[begin].push(lhs.begin, null_word);
        auto_nodes[begin].push(rhs.begin, null_word);
        auto_nodes[lhs.end].push(end, null_word);
        auto_nodes[rhs.end].push(end, null_word);
        return { begin, end };
    }

    automata concatenate_automata(automata lhs, automata rhs) {
        auto_nodes[lhs.end].push(rhs.begin, null_word);
        return { lhs.begin, rhs.end };
    }

    automata repeat_automata(automata lhs) {
        size_t begin = auto_nodes.size();
        size_t end = begin + 1;
        auto_nodes.emplace_back();
        auto_nodes.emplace_back();
        auto_nodes[begin].push(lhs.begin, null_word);
        auto_nodes[lhs.end].push(begin, null_word);
        auto_nodes[begin].push(end, null_word);
        return { begin, end };
    }

    automata create_structures(const std::string& rp_regex) {
        std::stack<automata, std::vector<automata>> operands;
        for (size_t i = 0; i < rp_regex.size(); ++i) {
            char cur_symb = rp_regex[i];
            switch (cur_symb) {
                case '+': {
                    if (operands.size() < 2) {
                        throw std::logic_error(
                            ("Invalid regex provided. There are no operands for + operator in position " + std::to_string(i)).c_str()
                        );
                    }
                    auto lhs = operands.top();
                    operands.pop();
                    auto rhs = operands.top();
                    operands.pop();
                    operands.push(unite_automata(lhs, rhs));
                    break;
                }
                case '.': {
                    if (operands.size() < 2) {
                        throw std::logic_error(
                            ("Invalid regex provided. There are no operands for . operator in position " + std::to_string(i)).c_str()
                        );
                    }
                    auto lhs = operands.top();
                    operands.pop();
                    auto rhs = operands.top();
                    operands.pop();
                    operands.push(concatenate_automata(lhs, rhs));
                    break;
                }
                case '*': {
                    if (operands.size() < 1) {
                        throw std::logic_error(
                            ("Invalid regex provided. There are no operands for * operator in position " + std::to_string(i)).c_str()
                        );
                    }
                    auto lhs = operands.top();
                    operands.pop();
                    operands.push(repeat_automata(lhs));
                    break;
                }
                default: {
                    operands.push(create_automata(cur_symb));
                    break;
                }
            }
        }
        if (operands.size() != 1) {
            throw std::logic_error(
                ("Invalid language provided. Parsing exited with " + std::to_string(operands.size()) + " operands").c_str()
            );
        }
        return operands.top();
    }

    void calculate_pairs(char req_symb, size_t req_len) {
        std::queue<step> queue;
        for (size_t i = 0; i < auto_nodes.size(); ++i) {
            queue.push({ i, i, 0 });
        }
        while (!queue.empty()) {
            auto v = queue.front(); queue.pop();
            if (v.len == req_len) {
                possible_pairs.push_back({ v.begin, v.cur });
                continue;
            }
            for (auto& i : auto_nodes[v.cur].next_nodes) {
                if (i.symb == null_word) {
                    queue.push({ v.begin, i.to, v.len });
                }
                else if (i.symb == req_symb) {
                    queue.push({ v.begin, i.to, v.len + 1 });
                }
            }
        }
    }

    void calculate_distances() {
        size_t N = auto_nodes.size();
        dist.resize(N, std::vector<size_t>(N, inf));
        for (size_t i = 0; i < N; ++i) {
            dist[i][i] = 0;
            for (auto& j : auto_nodes[i].next_nodes) {
                dist[i][j.to] = (j.symb != null_word);
            }
        }
        for (size_t k = 0; k < N; ++k) {
            for (size_t i = 0; i < N; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

public:

    __solver() = default;

    size_t solve(const std::string& rp_regex, char req_symb, size_t req_len) {
        auto beg_end = create_structures(rp_regex);
        calculate_pairs(req_symb, req_len);
        calculate_distances();
        size_t ans = inf;
        for (auto& i : possible_pairs) {
            ans = std::min(ans, dist[beg_end.begin][i.begin] + req_len + dist[i.end][beg_end.end]);
        }
        if (ans == inf) {
            throw std::logic_error(
                "Error: there is no answer in regular expression."
            );
        }
        return ans;
    }

};


size_t solve(const std::string& rp_regex, char req_symb, size_t req_len) {
    return __solver().solve(rp_regex, req_symb, req_len);
}
