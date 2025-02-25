#ifndef VAULT_HPP
# define VAULT_HPP

# include <string>

class Vault {
    private:
        std::string _password;

    public:
        Vault(const std::string& password);
        ~Vault();

        bool validatePassword(const std::string& passwordToValidate) const;
};

#endif // VAULT_HPP
