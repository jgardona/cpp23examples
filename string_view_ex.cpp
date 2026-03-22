#include <string_view>
#include <string>
#include <print>

using namespace std::string_view_literals;

// Aceita qualquer coisa que seja lida como string sem copiar.
void imprimirInfo(std::string_view texto) {
    std::println("Tamanho: {}, Conteúdeo: {}", texto.size(), texto);
}

int main(int argc, char *argv[])
{
    // Podemos criar um string_view a partir de uma string.
    std::string str{"Olá mundo!!"};
    std::string_view view1{str};
    // Usando o sufixo sv (c++17).
    auto view2{"Outro texto"sv};

    std::println("view1: {}", view1);
    std::println("view2: {}", view2);

    // O método contains: c++23.
    std::string_view texto{"Aprender c++23 é ótimo"};
    if (texto.contains("c++23")) {
        std::println("Encontrado c++23 no texto {}. (jeito c++23).", texto);
    }

    // Funções úteis:
    // starts_with() (c++20).
    // ends_with() (c++20).
    // substr(9, 5)

    std::string s{"String Dinâmica"};
    const char* c = "Literal C";
    auto sv{"StringView"sv};
    imprimirInfo(s);
    imprimirInfo(c);
    imprimirInfo(sv);
    return 0;
}
