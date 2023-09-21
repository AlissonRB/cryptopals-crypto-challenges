#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Função para converter uma string hexadecimal em bytes
vector<uint8_t> convert_bytes(const string& hex_string) {
    vector<uint8_t> bytes;
    
    for (size_t i = 0; i < hex_string.length(); i += 2) {
        string byteString = hex_string.substr(i, 2);
        uint8_t byte = std::stoi(byteString, nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

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

int main() {
    // Single-byte XOR cipher
    vector<vector<uint8_t>> results(256); //vetor para todas as possiveis respostas
    int scores[256]; //vetor de scores, score é a pontucao de uma string

    string message_hex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    vector<uint8_t> message_bytes = convert_bytes(message_hex);

    // xor com cada chave(256 chaves)
    for (int key = 0; key < results.size(); key++) { 
        vector<uint8_t> decrypted_bytes = xor_with_key(message_bytes, static_cast<uint8_t>(key));
        results[key] = decrypted_bytes;
    }

    //contagem de pontos
    for (int i = 0; i < results.size(); i++) {
        const vector<uint8_t>& decrypted_message = results[i];
        int count = count_common_letters(decrypted_message);
        scores[i] = count;
    }

    //descobrir qual string tem o maior score
    int bigger = 0;
    int highest_value = 0;
    for (int i = 0; i < 256; i++) {
        if (scores[i] > bigger) {
            bigger = scores[i];
            highest_value = i;
        }
    }

    const vector<uint8_t>& decrypted_message = results[highest_value];
    for(const uint8_t& byte : decrypted_message) {
        cout << static_cast<char>(byte);
    } 
    cout << endl;      
    return 0;
} 
