#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

// Função para converter uma string hexadecimal em bytes
vector<uint8_t> convert_bytes(const std::string& hex_string) {
    std::vector<uint8_t> bytes;
    
    for (size_t i = 0; i < hex_string.length(); i += 2) {
        std::string byteString = hex_string.substr(i, 2);
        uint8_t byte = std::stoi(byteString, nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

//xor da string com uma chave
vector<uint8_t> xor_with_key(const std::vector<uint8_t>& message_bytes, uint8_t key) {
    std::vector<uint8_t> decrypted_bytes;

    for (const uint8_t& byte : message_bytes) {
        decrypted_bytes.push_back(byte ^ key);
    }
    return decrypted_bytes;
}

//retorna a pontuacao de uma string
int count_common_letters(const vector<uint8_t>& message_bytes) {
    const string common_letters = "etaoin shrdlu";
    int count = 0;

    for (const uint8_t& byte : message_bytes) {
        char character = static_cast<char>(byte);
        if (common_letters.find(character) != string::npos) {
            count++;
        }
    }
    return count;
}

//parte do codigo do desafio 3 - retorna a melhor opcao para a linha
vector<uint8_t> xor_cipher (string message_hex) {

    vector<uint8_t> message_bytes = convert_bytes(message_hex); //converter hexa -> bytes
    vector<vector<uint8_t>> results(256); //vetor com todas as possiveis respostas em binario, depois da xor
    int scores[256];

    /// xor com cada chave(256 chaves)
    for (int key = 0; key < 256; key++) {
        vector<uint8_t> decrypted_bytes = xor_with_key(message_bytes, static_cast<uint8_t>(key));
        results[key] = decrypted_bytes;
    }

    //para cada item em results pega o score
    for (int i = 0; i < results.size(); i++) {
        const vector<uint8_t>& decrypted_message = results[i];
        int count = count_common_letters(decrypted_message);
        scores[i] = count;
    }

    int highest_score = 0;
    int highest_value = 0;
    for (int i = 0; i < 256; i++) {
        if (scores[i] > highest_score) {
            highest_score = scores[i];
            highest_value = i;
        }
    }
    const vector<uint8_t>& decrypted_message = results[highest_value];
    return decrypted_message;
}

int main() {
    ifstream file("src/cryptopals-challenge4.txt");

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return -1;
    }

    string line;
    vector<vector<uint8_t>> results; //armazena os melhores resultados para cada linha

    while (getline(file, line)) { //para cada linha do arquivo, faz o que foi feito no desafio 3
        vector<uint8_t> result = xor_cipher(line);
        results.push_back(result);
    }
    file.close();

    //encontra a posicao do resultado com maior score
    int highest_score = 0;
    int highest_score_index = 0;

    for ( int i = 0; i < results.size(); i++) {
        int score = count_common_letters(results[i]);
        if (score > highest_score) {
            highest_score = score;
            highest_score_index = i;
        }
    }

    //imprime a mensagem decifrada com maior score
    const vector<uint8_t>& decrypted_message = results[highest_score_index];
    for (const uint8_t& byte : decrypted_message) {
        cout << static_cast<char>(byte);
    }
    return 0;
}
