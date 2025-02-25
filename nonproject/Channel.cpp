#include "Channel.hpp"

Channel::Channel(const std::string& name, const std::string& key, Client* admin) :
    _name(name), 
    _admin(admin), 
    _key(key), 
    _limit(0), 
    _external_messages(false) {}

Channel::~Channel() {}


std::string Channel::get_name() const { return _name; }
Client* Channel::get_admin() const { return _admin; }
std::vector<Client*>& Channel::get_clients() { return _clients; }

std::string Channel::get_key() const { return _key; }
size_t Channel::get_limit() const { return _limit; }
bool Channel::is_external_messages_allowed() const { return _external_messages; }

size_t Channel::get_size() const { return _clients.size(); }

std::vector<std::string> Channel::get_nicknames() {
    std::vector<std::string> nicknames;

    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        Client* client = *it;

        std::string nick = (client == _admin ? "admin: " : "user: ") + client->get_nickname();
        nicknames.push_back(nick);
    }

    return nicknames;
}


void Channel::set_key(const std::string& key) { _key = key; }
void Channel::set_limit(size_t limit) { _limit = limit; }
void Channel::set_external_messages_allowed(bool flag) { _external_messages = flag; }
void Channel::set_admin(Client* admin) { _admin = admin; }
void Channel::set_name(const std::string& name) { _name = name; }