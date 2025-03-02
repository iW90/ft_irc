#include "Vault.hpp"


Vault::Vault(const std::string& password) {
    std::string encrypted = password;
    for (size_t i = 0; i < password.length(); ++i)
        encrypted[i] = password[i] ^ 0xAA;

    _password = encrypted;
}

Vault::~Vault() {}


bool Vault::validate_password(const std::string& pass_to_validate) const {
    std::string encryptedInput = pass_to_validate;

    for (size_t i = 0; i < pass_to_validate.length(); ++i)
        encryptedInput[i] = pass_to_validate[i] ^ 0xAA;

    return encryptedInput == _password;
}
