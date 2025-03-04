#pragma once

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"

# include <set>         // Necessário para std::set
# include <map>         // Necessário para std::map
# include <algorithm>   // Necessário para std::find
# include <vector>


class Client;
class Channel {
    typedef std::vector<Client *>::iterator client_iterator;

    private:

        std::string             _name;
        Client*                 _admin;
        std::set<Client *>      _clients;
        std::map<Client *, int> _black_list;
        

        /* Modes */
        std::string             _topic;             // channel description
        std::set<Client *>      _invited_clients;   // invited clients
        std::set<Client *>      _operators;         // channel operators
        std::string             _key;               // channel key
        size_t                  _limit;             // limit of channel members
        bool                    _external_messages; // yes/no external messages

    public:
        Channel(const std::string &name, const std::string &key, Client* admin);
        ~Channel();

        std::string                 get_name() const;
        Client*                     get_admin() const;
        std::set<Client*>&          get_clients();
        std::map<Client*, int>&     get_black_list();
        std::string                 get_topic() const;
        Client*                     get_operator(Client* target) const;
        
        std::string                 get_key() const;
        size_t                      get_limit() const;
        bool                        is_external_messages_allowed() const;

        size_t                      get_total_clients() const;
        std::vector<std::string>    get_nicknames();

        void                        set_admin(Client* admin);
        void                        set_name(const std::string& name);
        void                        set_topic(const std::string& topic);

        void                        set_key(const std::string& key);
        void                        set_limit(size_t limit);
        void                        set_external_messages_allowed(bool flag);

        void                        add_to_black_list(Client* client);
        void                        add_to_clients(Client* client);
        void                        add_to_invited_clients(Client* client);
        void                        add_to_operators(Client* client);
};

#endif // CHANNEL_HPP

/*
    No IRC (Internet Relay Chat), os canais podem ter senhas.
    Isso é feito para restringir o acesso ao canal e garantir 
    que apenas usuários autorizados possam participar. Essas 
    senhas são configuradas pelos administradores ou opers 
    (operadores) do canal.

    A senha de um canal no IRC é definida com o comando
        /set #canal +k senha
    onde:

        - #canal é o nome do canal.
        - +k ativa a proteção por senha.
        - senha é a senha que os usuários precisam fornecer para 
            entrar no canal.

    Quando a proteção por senha está ativa, os usuários que tentam 
    entrar no canal precisam informar a senha usando o comando 
        /join #canal senha.

    Se você tentar entrar em um canal protegido sem fornecer a 
    senha, não conseguirá acessar o canal.

    Vale notar que nem todos os canais IRC usam senhas, e muitas 
    vezes os canais públicos não exigem nenhuma senha para acesso.
*/