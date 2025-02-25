#include "Vault.hpp"


Vault::Vault(const std::string& password) {
    std::string encrypted = password;
    for (size_t i = 0; i < password.length(); ++i)
        encrypted[i] = password[i] ^ 0xAA;

    _password = encrypted;
}

Vault::~Vault() {}


bool Vault::validatePassword(const std::string& passwordToValidate) const {
    std::string encryptedInput = passwordToValidate;

    for (size_t i = 0; i < passwordToValidate.length(); ++i)
        encryptedInput[i] = passwordToValidate[i] ^ 0xAA;

    return encryptedInput == _password;
}
