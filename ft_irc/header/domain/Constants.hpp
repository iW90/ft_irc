#pragma once

#ifndef CONSTANTS_HPP
# define CONSTANTS_HPP

#include <string>

// ChannelService
const int MAX_BLACKLIST_VIOLATIONS = 3;     // Máximo de violações da black list

// Socket
const int MAX_CONNECTIONS = 20;             // Máximo de conexões por socket

// Multiplexer
const int MAX_EVENTS = 20;                  // Máximo de eventos gerenciáveis
const int BUFFER_SIZE = 100;                // Máximo de bytes de uma mensagem (buffer)

// Server
const std::string IP_ADDRESS = "127.0.0.1";

#endif // CONSTANTS_HPP
