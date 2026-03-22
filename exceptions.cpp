#include <expected>
#include <print>
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>

float dividir(float a, float b) {
    if (b == 0.0f) {
        throw std::string("Erro: divisão por zero!");
    }

    return a / b;
}

void processarIdade(int idade) {
    if (idade < 0) {
        throw std::invalid_argument("A idade não pode ser negativa.");
    }
    if (idade > 150) {
        throw std::runtime_error("Idade improvável.");
    }
}

// Exceção customizada.
class ErrConnection: public std::runtime_error {
public:
    explicit ErrConnection(const std::string& msg)
        :std::runtime_error("Falha na conexão: " + msg) {
    }
};

void conectar() {
    throw ErrConnection("O servidor não responde.");
}

class ObjetoSimples {
public:
    // Destrutores devem ser noexcept
    // (implicito no c++11, mas bom explicitar).
    ~ObjetoSimples() noexcept {}
    // Move constructor deve ser noexcept para otimização
    // no std::vector.
    ObjetoSimples(ObjetoSimples&& outro) noexcept {}
    ObjetoSimples() {}
};

enum class ErroArquivo {
    NaoEncontrado,
    SemPermissao
};

// Retorna um valor ou um erro, sem lançar exceção:
std::expected<std::string, ErroArquivo> lerArquivo(const std::string& nome) {
    if (nome.empty()) {
        return std::unexpected(ErroArquivo::NaoEncontrado);
    }
    if (nome == "proibido.txt") {
        return std::unexpected(ErroArquivo::SemPermissao);
    }
    return "Conteudo do arquivo: " + nome;
}

int main(int argc, char *argv[])
{
    // 1. Basico de tratamento de exceções.

    try {
        float result{dividir(10, 0)};
        std::print("Resultado da divisão: {}", result);
    } catch (const std::string& e) {
        std::println("Capturado: {}", e);
    }

    // 2. Exceções da biblioteca padrão.
    // Em c++ moderno, nunca lance tipos primitivos(int ou char*) ou std::string diretamente.
    // Use as classes de hierarquia std::exception.
    // As mais comuns estão em <stdexception>:
    // std::runtime_error: Erros detectáveis apenas durante a execução.
    // std::invalid_argument: Argumento inválido passado para uma função.
    // std::out_of_range: Acesso fora dos limites: (ex: std::vector::at).
    // std::logic_error: Erros na lógica do programa.
    // Exemplo:

    try {
        processarIdade(-5);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Erro de argumento: " << e.what() << "\n";
    } catch(const std::runtime_error& e) {
        std::cerr << "Erro de execução: " << e.what() << "\n";
    } catch(const std::exception& e) {
        std::cerr << "Erro genérico: " << e.what() << "\n";
    }

    // 3. Criando exceções personalizadas.
    try {
        conectar();
    } catch (const ErrConnection& e) {
        std::cerr << "Erro ao tentar conectar: " << e.what() << "\n";
    }

    // 4. Operações arriscadas.
    try {
        std::unique_ptr<int[]> ptr{new int[1000]};
        std::vector<int> dados;
        throw std::runtime_error("Algo deu errado.");
    } catch (std::runtime_error& e) {
        std::cerr << "Erro fatal tratado com smartpointers: " << e.what() << "\n";
    }

    // 5. O especificador noexcept.
    // No c++23, o uso de noexcept é crucial para performance e contratos de interface.
    // Ele diz ao compilador: "Esta função nunca lançará uma exceção.

    try {
        ObjetoSimples p;
    } catch (...) {
        std::cerr << "Houve alguma falha." << "\n";
    }

    // 6. A novidade do c++23. std::expected.

    auto resultado = lerArquivo("proibido.txt");
    if (resultado.has_value()) {
        std::println("Sucesso: {}", resultado.value());
    } else {
        switch (resultado.error()) {
        case ErroArquivo::NaoEncontrado:
            std::cerr << "Erro: arquivo não existe.\n";
            break;
        case ErroArquivo::SemPermissao:
            std::cerr << "Erro: sem permissão de acesso.\n";
            break;
        default:
            break;
        }
    }

    // Boas práticas no c++23:
    // 1: Não lance no destrutor: Destrutores devem ser noexcept.
    // 2: Capture por referencia: catch(const std::exception& e).
    // 3: Especificidade: Capture exeções específicas antes das genéricas.
    // 4: Prefira expected para fluxo. Se o erro é parte normal da lógica.
    // 5: Evite lançar em blocos de performance crítica: O lançamento é caro.

    return 0;
}
