#ifndef ISOCKET_HPP
#define ISOCKET_HPP

class ISocket {
    public:
        virtual ~ISocket() {}

        // Método para obter o descritor de arquivo do socket
        virtual int get_fd() const = 0;
};

#endif // ISOCKET_HPP
