#include "commands/operator/Topic.hpp"


Topic::Topic(Server& server) : ACommand(server, true) {}
Topic::~Topic() {}


// syntax:  TOPIC <channel> :<new_topic>
//          TOPIC <channel>
void Topic::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    Channel* channel = _server.get_channel(args[0]);
    if (!_has_valid_channel(client, channel))
        return;
    
    
    if (args.size() == 1) {
        // VALIDAR QUAL DESSAS DUAS OPÇÕES DE ENVIO, BROADCAST OU REPLY
        ClientService::reply_message(client, channel->get_topic());
        ChannelService::broadcast(channel, channel->get_topic()); // LEMBRAR DE CONSTRUIR A MENSAGEM COM MACRO
        return;
    }

    if (!_has_channel_privileges(client, channel))
        return;
    
    std::string topic = _extract_topic(args);
    channel->set_topic(topic);
    ChannelService::broadcast(channel, topic); // LEMBRAR DE CONSTRUIR A MENSAGEM COM MACRO
}


bool Topic::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    if (args.empty()) {
        ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "TOPIC"));
        return false;
    }
    return true;
}

std::string Topic::_extract_topic(const std::vector<std::string>& args) {
    std::string topic = "";
    if (args.size() >= 2 && (args[1][0] != ':' || args[1].size() > 1)) {
        for (size_t i = 2; i < args.size(); ++i) {
            topic.append(args[i]);
            topic.append(" ");
        }
    }
    return topic;
}

bool Topic::_has_channel_privileges(Client* client, Channel* channel) {
    if (channel->get_admin() != client) {
        ClientService::reply_message(client, ERR_CHANOPRIVSNEEDED(client->get_nickname(), channel->get_name()));
        return false;
    }
    return true;
}

bool Topic::_has_valid_channel(Client* client, Channel* channel) {
    if (!channel) {
        // LEMBRAR DE CONSTRUIR A MENSAGEM COM MACRO
        ClientService::reply_message(client, ERR_NOSUCHCHANNEL(client->get_nickname(), ""));
        return false;
    }
    return true;
}
