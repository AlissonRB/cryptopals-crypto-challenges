#include <iostream>
using namespace std;

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

//4 digitos binario para hexadecimal equivalente
string binary_hexadecimal(string binary) {
    string hexa_value;
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

    for (int i = 0; i < binary.size(); i += 4) {
        string four_digits = binary.substr(i, 4);
        for (int j = 0; j < 16; j++) {
            if (four_digits == bin[j]) {
                hexa_value += hexa[j];
                break;
            }
        }
    }
    return hexa_value;
}

//recebe uma string binaria e retorna uma em hexadeciaml
string binary_string_hexadecimal(string binary) {
    int step = 4;
    string hexa_value;
    int size = binary.size();
    int i = size - 1;

    while (i >= 0) {
        string four_digits = binary.substr(i - 3, step); //pegar os proximos 4 digitos
        i -= step;

        while (four_digits.size() < step) { //quando precisar completar com 0's
            four_digits = "0" + four_digits;
        }
        string hexa_string = binary_hexadecimal(four_digits);
        hexa_value = hexa_string + hexa_value;
    }
    return hexa_value;
}

//retorna xor de dois binarios
string xor_function(string binaryA, string binaryB) {
    string xor_value;

    for (int i = 0 ; i < binaryA.size(); i++) {
        if (binaryA[i] == binaryB[i]) {
            xor_value += "0";
        } else {
            xor_value += "1";
        }
    }
    return xor_value;
}

string fixed_xor(string x1, string x2) {
    string binary1 = hexadecimal_binary(x1);
    string binary2 = hexadecimal_binary(x2);

    string xor_value = xor_function(binary1, binary2);
    string hexadecimal_result = binary_string_hexadecimal(xor_value);
    return hexadecimal_result;
}

int main() {
    //Fixed XOR
    string stringA = "1c0111001f010100061a024b53535009181c";
    string stringB = "686974207468652062756c6c277320657965";

    string output = fixed_xor(stringA, stringB);
    cout << output << endl;
    return 0;
}