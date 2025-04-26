#include <iostream>
#include <string>
#include <vector>

int lowest (std::string str, int strLen) {
    int lowest = 10e6, lindex;
    for (int i = 0; i < strLen; ++i) {
        if (str[i] < lowest && str[i] != '*') {
            lowest = str[i];
            lindex = i;
        }
    }
    return lindex;
}

std::string encrypt (std::string key, std::string message, int kLen, int divFactor) {
    std::string encrypted;
    std::vector<std::string> table(divFactor, "");
    int mPtr = 0, curr;
    for (int i = 0; i < divFactor; ++i) {
        for (int j = 0; j < kLen; ++j) {
            table[i] += message[mPtr++];
        }
    }
    std::string cell;
    for (int i = 0; i < kLen; ++i) {
        curr = lowest(key, kLen);
        key[curr] = '*';
        for (int j = 0; j < divFactor; ++j) {
            cell = table[j][curr];
            if (cell != "\n") encrypted += cell;
        }
    }
    return encrypted;
}

std::string decrypt (std::string key, std::string encrypted, int kLen, int divFactor) {
    std::string decrypted;
    char table[divFactor][kLen];
    int ePtr = 0, curr;
    for (int i = 0; i < kLen; ++i) {
        curr = lowest(key, kLen);
        key[curr] = '*';
        for (int j = 0; j < divFactor; ++j) {
            table[j][curr] = encrypted[ePtr++];
        }
    }
    for (int i = 0; i < divFactor; ++i) {
        for (int j = 0; j < kLen; ++j) {
            if (table[i][j] != '*') {
                decrypted += table[i][j];   
            }
        }
    }
    return decrypted;
}

int menu(int var, std::string message) {
    while (1) {
        std::cout<<message;
        std::cin>>var;
        if (var != 1 && var != 2 && var != 3) {
            std::cout<<"*Invalid option*\n";
        }
        return var;
    }
}

void input (std::string& key, std::string& message, int& kLen, int& mLen) {
    while (true) {
        std::cout<<"Key: ";
        std::cin>>key;
        std::cout<<"Message: ";
        std::cin>>message;
        kLen = key.length(), mLen = message.length();
        if (mLen % kLen != 0) {
            std::cout<<"*The message's length has to be divisible by the key's length*\n";
        } else {
            break;
        }
    }
}

int main() {
    int ans, kLen, mLen, divFactor;
    std::string key, message;
    std::cout<<"Welcome to Raphael's column transposition cipher program!\n";
    while (true) {
        ans = menu(ans, "Do you wish to:\n\n1) Encrypt\n2) Decrypt\n3) Exit\n\n");
        if (ans != 3) {
            input(key, message, kLen, mLen);
            divFactor = mLen / kLen;
            if (ans == 1) {
                std::cout<<"\n\nMESSAGE: "<<message<<"\nENCRYPTED MESSAGE: "<<encrypt(key, message, kLen, divFactor)<<"\n\n";
            } else {
                std::cout<<"\n\nENCRYPTED MESSAGE: "<<message<<"\nDECRYPTED MESSAGE: "<<decrypt(key, message, kLen, divFactor)<<"\n\n";
            }
        } else {
            std::cout<<"Goodbye!\n";
            break;
        }
    }
    return 0;
}