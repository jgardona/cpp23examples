#include <print>
#include <string>
#include <vector>
#include <functional>
#include <memory>

enum class Cor { Vermelho, Verde, Azul };
enum class Status { Vermelho, Verde, Azul };

int main(int argc, char *argv[])
{
    using Inteiro = int;
    using String = std::string;
    using IntVector = std::vector<int>;

    Inteiro val1{11};
    String val2{"Este é um simples string"};
    IntVector val3{1, 2, 3, 4};

    std::println("Valor da variavel Inteiro {}", val1);
    std::println("Valor da variavel String {}", val2);
    for (Inteiro el : val3) {
        std::println("elemento -> {}", el);
    }

    enum class EstadoPedido: u_int8_t {
        Pendente = 0,
        Processando = 1,
        Enviado = 2,
        Entregue
    };

    EstadoPedido estado{EstadoPedido::Pendente};
    // Se precisar do valor inteiro (ex: salvar no banco).
    auto valor = static_cast<std::uint8_t>(estado);
    // Comparação.
    if(estado == EstadoPedido::Pendente) {
        std::println("Estado pendente = {}", valor);
    }

    // Novidade c++23.
    using Task = std::move_only_function<void()>;
    auto ptr = std::make_unique<int>(42);
    Task t = [p = std::move(ptr)]() {
        std::println("Valor de ptr: {}", *p);
    };

    t();

    // auto t2 = t; // Não é copiável, somente movível.
    auto t2{std::move(t)};
    t2();

    return 0;
}
