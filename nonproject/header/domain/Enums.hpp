#pragma once

#ifndef ENUMS_HPP
# define ENUMS_HPP

enum ChannelMode {
    INVITE_ONLY         = 'i',      // Canal somente para convidados (Invite-only)
    TOPIC_RESTRICTED    = 't',      // Restrições para o comando TOPIC (somente operadores de canal podem alterar)
    KEY_PASSWORD        = 'k',      // Canal com senha (key)
    OPERATOR            = 'o',      // Privilégios de operador de canal
    LIMIT               = 'l'       // Limite de usuários no canal
};

#endif ENUMS_HPP