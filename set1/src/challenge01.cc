#include <iostream>
#include <string>
using namespace std;
#include <cmath>

//convert hexadecimal to binary
string hexadecimal_binary(string hexa_string){
    string binary_string;
    string bin[16] = {
        "0000", "0001", "0010", "0011",
        "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011",
        "1100", "1101", "1110", "1111"
    };  

    string hexa[16] = {
        "0", "1", "2", "3", "4", "5", "6", "7", "8",
        "9", "a", "b", "c", "d", "e", "f"
    };

    for (int i = 0; i < hexa_string.size(); i++) {
        char character = hexa_string[i];
        for (int j = 0; j < 16; j++) {
            if (character== hexa[j][0]) {
                binary_string  += bin[j];
            }
        }
    }
    return binary_string ;
}

//convert binary to decimal
int binary_decimal(string binary) {
    int size = binary.size();
    int decimal = 0;

    for (int i = size - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += pow(2, size - 1 - i);
        }
    }
    return decimal;
}

string base64_character(string binary){
    string base64[64];
    string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    for (int i = 0; i < 64; i++) {
        base64[i] = base64Chars[i];
    }
    int decimal_number = binary_decimal(binary);
    return base64[decimal_number];
}

string binary_base64(string str) {
    //para cada 6 bits da esquerda para a direita, cada um vale um caractere em base64
    int step = 6;
    string base64_string;
    int i = 0;

    while (i < str.size()) {
        string part = str.substr(i, step);
        i += step;
        while (part.size() < step) {
            part = "0" + part;
        }
        string character_base64 = base64_character(part);
        base64_string += character_base64;
    }
    return base64_string;
}

int main() {
    //Convert hex to base64
    string  input_word = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    string binary = hexadecimal_binary(input_word);

    string output = binary_base64(binary);

    string expected_output = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    if (expected_output  == output) {
        cout << output << endl;
    }
    else {
        cout << "N";
    }
    return 0;
}
