#include <print>
#include <string>
#include <fstream>
#include <expected>
#include <system_error>
#include <vector>

std::expected<std::vector<std::string>, std::error_code>
lerArquivo(const std::string& caminho) {
    std::ifstream arquivo(caminho);

    // verifica se abriu.
    if(!arquivo) {
        // retorna o erro do sistema.
        return std::unexpected(std::make_error_code(std::errc::no_such_file_or_directory));
    }

    std::vector<std::string> linhas;
    std::string linha;

    while (std::getline(arquivo, linha)) {
        linhas.push_back(linha);
    }

    // verifica se houve erro de leitura durante o loop.
    if (arquivo.bad()) {
        return std::unexpected(std::make_error_code(std::errc::io_error));
    }

    return linhas;
}

std::expected<void, std::error_code>
escreverArquivo(const std::vector<std::string>& data) {
    std::ofstream file("datafile.txt");
    if(!file){
        return std::unexpected(std::make_error_code(std::errc::no_such_file_or_directory));
    }

    for (auto& line : data) {
        std::print(file, "{}\n", line);
    }

    return {};
}

int main(int argc, char *argv[])
{

    std::vector<std::string> buffer{
        {"the quick brown fox jumps over the lazy dog"},
        {"the quick brown fox jumps over the lazy dog"}
    };

    auto resultado = escreverArquivo(buffer);
    if (!resultado.has_value()) {
        std::println(stderr, "Erro: {}", resultado.error().message());
    }

    // gravar arquivos binários.

    std::ofstream arquivo("data.bin", std::ios::binary);
    if (!arquivo) {
        std::println(stderr, "Erro: falha ao criar arquivo.");
        return 1;
    }

    int numero{42};
    double pi{3.14159};
    arquivo.write(reinterpret_cast<const char*>(&numero), sizeof(numero));
    arquivo.write(reinterpret_cast<const char*>(&pi), sizeof(pi));

    auto resultado1 = lerArquivo("datafile.txt");

    if(resultado1.has_value()) {
        std::println("Sucesso!!! {} linhas lidas.", resultado1->size());
    } else {
        std::println(stderr, "Erro: {}", resultado1.error().message());
    }

    return 0;
}
