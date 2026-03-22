#include <print>
#include <vector>
#include <ranges>

// Isto aqui vai quebrar o programa.
auto get_view() {
    std::vector<int> temp = {1, 2, 3};
    return temp | std::views::filter([](int i){ return true; })
           | std::ranges::to<std::vector>(); // necessário realocar o vetor. Comente essa linha para ver o problema.
    // 'temp' é destruído ao sair da função. A view retorna lixo.
}

int main(int argc, char *argv[])
{
    std::vector<int> numeros{1, 2, 3, 4, 5, 6};
    auto resultado = numeros
                     | std::views::filter([](int n){
                           return n % 2 == 0;
                       })
                     | std::views::transform([](int n){
                           return n * n;
                       })
                     | std::ranges::to<std::vector>();

    for (int n : resultado) {
        std::println("Elemento -> {:d}", n);
    }

    // Novidades do c++ 23.
    // std::views::zip.
    std::vector<int> ids{1, 2, 3};
    std::vector<std::string> nomes{"Alice", "Bob", "Charlie"};

    auto combinado = std::views::zip(ids, nomes);
    for (auto [id, nome] : combinado) {
        std::println("Id: {:d}, Nome: {:s}", id, nome);
    }

    // Chunk: divide em grupos de 3.
    for(auto grupo: numeros | std::views::chunk(3)) {
        for (int n : grupo) {
            std::println("Valores de n -> {:d}", n);
        }
        std::println();
    }

    // Slide: janela deslizante de tamanho 3.
    // resultado: {1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}.
    std::println("Slide(3):");

    for (auto grupo : numeros | std::views::slide(3)) {
        for (int n: grupo) {
            std::println("Valores de n pelo slide -> {:d}", n);
        }
        std::println();
    }

    // Essa função retorna um dangling pointer. Veja a doc acima.
    auto result = get_view();
    for (auto e : result) {
        std::println("{:d}", e);
    }

    return 0;
}
