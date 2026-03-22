#include <format>
#include <print>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>

using namespace std::string_literals;

int main(int argc, char *argv[])
{
    // pair<int, double>
    std::pair<int, double> pair1{100, 200.0};
    std::println("pair1.first: {:d}, pair1.second: {:.1f}", pair1.first, pair1.second);
    std::pair<std::string, long long> pair2{"Hello, World!", 42LL};
    std::println("pair2.first: {:s}, pair2.second: {:d}", pair2.first, pair2.second);

    // using std::make_pair()
    auto pair3 = std::make_pair("cm / inch", 2.54f);

    using pair_t = std::pair<std::string, double>;

    std::vector<pair_t> vec_1{
        {"Beryllium", 9.0122},
        {"Helium", 4.0026},
        {"Neon", 20.180}
    };

    // using emplace_back to add more elements
    vec_1.emplace_back(std::make_pair("Lithium", 6.94));

    // print lambda for std::vector<pair_t>.
    auto print_vec = [](const char* msg, const std::vector<pair_t>& vec)
    {
        std::print("{:s}", msg);
        for(const auto& v: vec)
            std::println("{:<12s} {:12.4f}", v.first, v.second);
    };

    print_vec("\nvec_1 (initial values):\n", vec_1);

    // using std::ranges::sort (custom predicate)
    auto cmp_op = [](const pair_t& pair1, const pair_t& pair2)
    {
        return pair1.second < pair2.second;
    };

    std::ranges::sort(vec_1);

    print_vec("\nvec_1 (initial values):\n", vec_1);

    return 0;
}
