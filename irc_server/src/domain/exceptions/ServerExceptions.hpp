#ifndef SERVER_EXCEPTIONS_HPP
# define SERVER_EXCEPTIONS_HPP

# include <exception>
# include <iostream>
# include <cstring>

class ServerException : public std::exception {
    private:
        std::string message_;           // Variável para armazenar a mensagem personalizada
        std::string original_message_;  // Variável para armazenar a mensagem da exceção original

    public:
        explicit ServerException(const std::exception& e, const std::string& message);

        virtual ~ServerException() throw();

        const char* what() const throw();
};

#endif // SERVER_EXCEPTIONS_HPP