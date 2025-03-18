#pragma once

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <set>         // Necessário para std::set
# include <map>         // Necessário para std::map
# include <utility>     // Necessário para pair
# include <algorithm>   // Necessário para std::find
# include <vector>
# include <string>


class Client;

class Channel {
    typedef std::vector<Client*>::iterator client_iterator;

    private:
        std::string             _name;
        Client*                 _admin;
        std::set<Client*>       _clients;
        std::map<Client*, int>  _black_list;
        std::pair<std::string, std::string> _created;

        /* Modes */
        std::pair<bool, std::set<Client*> >     _operators;
        std::pair<bool, std::set<Client*> >     _inviteds;
        std::pair<bool, std::string>            _topic;
        std::pair<bool, std::string>            _key;
        std::pair<bool, int>                    _limit;

    public:
        Channel(Client* admin, const std::string& name);
        ~Channel();

        std::pair<bool, std::set<Client*> >&     get_operators();
        std::pair<bool, std::set<Client*> >&     get_inviteds();
        std::pair<bool, std::string>&            get_topic();
        std::pair<bool, std::string>&            get_key();
        std::pair<bool, int>&                    get_limit();

        std::string                 get_name() const;
        Client*                     get_admin() const;
        std::set<Client*>&          get_clients();
        std::map<Client*, int>&     get_black_list();

        // setters
        void                        set_name(const std::string& name);
        void                        set_admin(Client* admin);

        void                        set_operators(bool state);
        void                        set_inviteds(bool state);
        void                        set_topic(bool state, const std::string& topic);
        void                        set_key(bool state, const std::string& key);
        void                        set_limit(bool state, int limit);

        // others
        Client*                     get_operator(Client* target);
        Client*                     get_invited(Client* target);

        void                        add_to_black_list(Client* client);
        void                        add_to_clients(Client* client);
        void                        add_to_inviteds(Client* client);
        void                        add_to_operators(Client* client);

        void                        remove_from_clients(Client* client);
        void                        remove_from_inviteds(Client* client);
        void                        remove_from_operators(Client* client);

        std::string                 get_creation();
        std::string                 get_creator();
};

#endif // CHANNEL_HPP
