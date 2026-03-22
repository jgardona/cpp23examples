#include <cmath>
#include <print>
#include <bit>
#include <cstdint>
#include <array>

class Base
{
public:
    Base() {}
    virtual void falar() {
        std::println("Sou base.");
    }
};

class Derivada: public Base
{
public:
    void falar() override {
        std::println("Sou derivada.");
    }
    void especifico() {
        std::println("Metodo exclusivo da derivada.");
    }
};

int main(int argc, char *argv[])
{
    // 1. conversão numérica.
    double pi{3.14159};
    int pi_int = static_cast<int>(pi);
    std::println("Pi double: {}, Pi int: {}", pi, pi_int);

    // 2. Upcasting (Seguro: Derivada -> Base).
    Derivada d;
    Base b = static_cast<Base>(d);
    b.falar();

    // 3. Downcasting (Perigoso: Base -> Derivada)
    // O static_cast não verifica se b é realmente uma derivada em runtime.
    // Se b_ptr apontasse para uma Base pura, isso causaria undefined behavior.
    Derivada* dd = static_cast<Derivada*>(&b);
    dd->especifico();

    // 4. Void* (Comum em apis C).
    int numero{42};
    void* v_ptr{&numero};
    int* recuperado = static_cast<int*>(v_ptr);
    std::println("O valor via void*: {}", *recuperado);

    // Começaremos os exemplos de bit_cast.

    // Cenário: queremos inspecionar a representação IEEE 754 de um float.
    float f{1.0};
    // ERRADO: UB Pontecial: int i = *reinterpret_cast<int*>(&f).

    // Certo: c++23:
    std::uint32_t bits = std::bit_cast<std::uint32_t>(f);
    std::println("Float: {}", f);
    // Formatação hexadecimal com std::println (c++23).
    std::println("Bits (HEX): {:08x}", bits);

    // Exemplo reverso: criar um float a partir de bits conhecidos (ex: NaN ou Inf).
    uint32_t inf_bits{0x7f800000};
    float infinito{std::bit_cast<float>(inf_bits)};
    std::println("Valor gerado dos bits: {}", infinito);
    std::println("É infinito? {}", std::isinf(infinito));

    // Exemplo constexpr (Cálculo em tempo de compilação).
    constexpr uint32_t compile_time_bits{std::bit_cast<uint32_t>(1.0f)};
    static_assert(compile_time_bits == 0x3f800000, "Bits incorretos");

    // Float para array de Bytes.
    float valor{-12.5f};
    // O destino deve ter o mesmo tamanho que a origem.
    // Sizeof(float) = 4, então o array precisa ter 4 elementos.
    std::array<uint8_t, 4> bytes = std::bit_cast<std::array<uint8_t, 4>>(valor);
    std::println("Float: {}", valor);
    std::print("Bytes: ");
    for (uint8_t b : bytes) {
        std::print("{:02x} ", b);
    }
    std::println();

    // Executa o caminho reverso.
    float result_float = std::bit_cast<float>(bytes);
    std::println("Float recuperado: {}", result_float);

    return 0;
}
