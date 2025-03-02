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

        
        std::string                 get_key() const;
        size_t                      get_limit() const;
        bool                        is_external_messages_allowed() const;

        size_t                      get_size() const;
        std::vector<std::string>    get_nicknames();

        void                        set_admin(Client* admin);
        void                        set_name(const std::string& name);

        void                        set_key(const std::string& key);
        void                        set_limit(size_t limit);
        void                        set_external_messages_allowed(bool flag);

        void                        add_to_black_list(Client* client);
        void                        add_to_clients(Client* client);

};

#endif // CHANNEL_HPP