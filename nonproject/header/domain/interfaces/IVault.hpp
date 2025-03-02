// IVault.hpp - Camada de domínio
#ifndef IVAULT_HPP
# define IVAULT_HPP

# include <string>

class IVault {
    public:
        virtual ~IVault() {}

        // Método para validar a senha
        virtual bool validate_password(const std::string& pass_to_validate) const = 0;
};

#endif // IVAULT_HPP
