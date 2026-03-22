#include <iostream>
#include <cstdio>
#include <iomanip>
#include <format>
#include <numbers>
#include <strings.h>

void io_example1(int a, unsigned long long b, double c, const std::string& d)
{
    std::printf("Values using printf()\n");
    std::printf("a: %d\n", a);
    std::printf("b: 0x%016llX\n", b);
    std::printf("c: %-10.8lf\n", c);
    std::printf("d: %40s\n", d.c_str());
}

void io_example2(int a, unsigned long long b, double c, const std::string& d)
{
    std::cout << "Values using osteam operator << \n";
    std::cout << "a: " << a << '\n';
    std::cout << std::setfill('0') << "b: 0x" << std::hex << std::setw(16)
              << b << '\n';
    std::cout << std::setfill(' ')
              << "c: " << std::fixed << std::setprecision(8)
              << std::left << std::setw(10) << c << '\n';
    std::cout << "d: " << std::right << std::setw(40) << d << '\n';
}

void io_example3(int a, unsigned long long b, double c, const std::string& d)
{
    std::cout << "Values using std::format()\n";
    std::cout << std::format("a: {}\n", a);
    std::cout << std::format("b: 0x{:016X}\n", b);
    std::cout << std::format("c: {:<10.8f}\n", c);
    std::cout << std::format("d: {:>40s}\n", d);
}

int main()
{
    std::cout << "Exemplos de IO formatados." << std::endl;
    constexpr int a{100};
    constexpr unsigned long long b{0x4444'3333'2222'1111};
    constexpr double c{std::numbers::pi};
    std::string d{"Four score and seven years ago, ..."};
    io_example1(a, b, c, d);
    io_example2(a, b, c, d);
    io_example3(a, b, c, d);

    return 0;
}
