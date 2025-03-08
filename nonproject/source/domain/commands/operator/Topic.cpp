#include "commands/operator/Topic.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "ClientService.hpp"
#include "ChannelService.hpp"
#include "Macros.hpp"
#include "Server.hpp"


Topic::Topic(Server* server) : ACommand(server, true) {}
Topic::~Topic() {}


// syntax:  TOPIC <channel> :<new_topic>
//          TOPIC <channel>
void Topic::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    std::string target = args.at(0);
    Channel* channel = _server->get_channel(target);
    if (!_is_valid_channel(client, channel, target))
        return;

    if (args.size() == 1) {
        _send_current_topic(client, channel);
        std::cout << "SUCCEDED PART" << std::endl;
        return;
    }

    if (!_has_channel_privileges(client, channel))
        return;
    
    _set_new_topic(client, channel, args);
    std::cout << "SUCCEDED TOPIC" << std::endl;
}


// Funções auxiliares

bool Topic::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    std::cout << "TOPIC::Validate parameters..." << std::endl;
    if (args.empty()) {
        ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "TOPIC"));
        return false;
    }
    return true;
}

void Topic::_send_current_topic(Client* client, Channel* channel) {
    ClientService::reply_message(client, RPL_TOPIC(client->get_prefix(), channel->get_name(), channel->get_topic().second));
}

void Topic::_set_new_topic(Client* client, Channel* channel, const std::vector<std::string>& args) {
    std::cout << "TOPIC::Defining new topic description..." << std::endl;
    if ((!channel->get_operators().first) || \
        (channel->get_operators().first && client == channel->get_operator(client))) {
        std::string topic = _extract_topic(args);
        channel->set_topic(true, topic);
        ChannelService::broadcast(channel, RPL_TOPIC(client->get_prefix(), channel->get_name(), channel->get_topic().second));
    }
}

std::string Topic::_extract_topic(const std::vector<std::string>& args) {
    std::cout << "TOPIC::Extracting topic description..." << std::endl;
    std::string topic = "";
    if (args.size() >= 2 && (args[1][0] != ':' || args[1].size() > 1)) {
        for (size_t i = 2; i < args.size(); ++i) {
            topic.append(args[i]);
            topic.append(" ");
        }
    }
    return topic;
}
