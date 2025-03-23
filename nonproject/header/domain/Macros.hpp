#pragma once

#ifndef MACROS_HPP
# define MACROS_HPP


/* General Responses */

# define RPL_WELCOME(client)                            "001 :Welcome " + client + " to the ft_irc network"
# define RPL_YOURHOST(server)                           "002 :Your host is " + server + ", running version 1.0"
# define RPL_CREATED(datetime)                          "003 :This server was created " + datetime
# define RPL_MYINFO(server)                             "004 " + server + " 1.0 itkol"

# define RPL_LISTSTART()                                "321 Channel :Users Name"
# define RPL_LIST(channel, clientcount, topic)          "322 " + channel + " " + clientcount + " :" + topic
# define RPL_LISTEND()                                  "323 :End of /LIST"

# define RPL_CHANNELMODEIS(channel, modes, args)        "324 " + channel + " " + modes + " " + args

# define RPL_NOTOPIC(channel)                           "331 " + channel + " :No topic is set"
# define RPL_TOPIC(channel, topic)                      "332 " + channel + " :" + topic
# define RPL_TOPICWHOTIME(channel, nick, datetime)      "333 " + channel + " " + nick + " " + datetime

# define RPL_INVITING(nick, channel)                    "341 " + nick + " " + channel
# define RPL_INVITELIST(channel)                        "346 " + channel
# define RPL_ENDOFINVITELIST()                          "347 :End of /INVITE list"

# define RPL_WHOREPLY(channel, users)                   "352 " + channel + " " + users // "<channel> <username> <host> <server> <nick> <flags> :<hopcount> <realname>"
# define RPL_ENDOFWHO(channel)                          "315 " + channel + " :End of WHO list"

# define RPL_NAMREPLY(channel, users)                   "353 = " + channel + " :" + users // "<symbol> <channel> :[prefix]<nick>"
# define RPL_ENDOFNAMES(channel)                        "366 " + channel + " :End of /NAMES list"

# define RPL_INFO(info)                                 "371 :" info
# define RPL_ENDOFINFO()                                "374 :End of /INFO list"

# define RPL_HELPSTART(subject, text)                   "704 " + subject + " :" + text  //"<client> <subject> :<first line of help section>"
# define RPL_HELPTXT(subject, text)                     "705 " + subject + " :" + text  //"<client> <subject> :<line of help text>"
# define RPL_ENDOFHELP(subject, text)                   "706 " + subject + " :" + text  //"<client> <subject> :<last line of help text>"


/* Error Responses */

# define ERR_NOSUCHNICK(nickname)                           "401 " + nickname + " :No such nick"
# define ERR_NOSUCHCHANNEL(channel)                         "403 " + channel + " :No such channel"
# define ERR_CANNOTSENDTOCHAN(channel)                      "404 " + channel + " :Cannot send to channel"
# define ERR_TOOMANYCHANNELS(channel)                       "405 " + channel + " :You have joined too many channels"
# define ERR_UNKNOWNCOMMAND(command)                        "421 " + command + " :Unknown command"
# define ERR_NONICKNAMEGIVEN()                              "431 :Nickname not given"
# define ERR_NICKNAMEINUSE(nickname)                        "433 " + nickname  + " :Nickname is already in use"
# define ERR_USERNOTINCHANNEL(nickname, channel)            "441 " + nickname + " " + channel + " :They aren't on that channel"
# define ERR_NOTONCHANNEL(channel)                          "442 " + channel + " :You're not on that channel"
# define ERR_USERONCHANNEL(user, channel)                   "443 " + user + " " + channel + " :is already on channel"
# define ERR_NOTREGISTERED()                                "451 :You have not registered"
# define ERR_NEEDMOREPARAMS(command)                        "461 " + command + " :Not enough parameters"
# define ERR_ALREADYREGISTERED()                            "462 :Unauthorized command (already registered)"
# define ERR_PASSWDMISMATCH()                               "464 :Password is incorrect"
# define ERR_CHANNELISFULL(channel)                         "471 " + channel + " :Cannot join channel (+l)"
# define ERR_UNKNOWNMODE()                                  "472 " + channel + " :is unknown mode char to me"
# define ERR_INVITEONLYCHAN(channel)                        "473 " + channel + " :Cannot join channel (+i)"
# define ERR_BANNEDFROMCHAN(channel)                        "474 " + channel + " :Cannot join channel (+b)"
# define ERR_BADCHANNELKEY(channel)                         "475 " + channel + " :Cannot join channel (+k)"
# define ERR_CHANOPRIVSNEEDED(channel)                      "482 " + channel + " :You're not channel operator"


/* Command Responses */

# define RPL_JOIN(source, channel, target)               ":" + source + " JOIN " + channel + " * :" + target
# define RPL_PART(source, channel)                       ":" + source + " PART " + channel
# define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message
# define RPL_QUIT(source, message)                       ":" + source + " QUIT " + message
# define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK " + channel + " " + target + " :" + reason
# define RPL_MODE(source, channel, modes, args)          ":" + source + " MODE " + channel + " " + modes + " " + args
# define RPL_NICK(source)                                ":" + source + " NICK is now " + source
# define RPL_NOTICE(source, target, message)             ":" + source + " PRIVMSG " + target + " :" + message
# define RPL_PING(source, token)                         ":" + source + " PONG :" + token



/* Broadcast messages */

# define MESSAGE_CLIENT_JOIN(channel, client)                    client + " joined the channel " + channel
# define MESSAGE_CLIENT_LEAVE(channel, client)                   client + " left " + client + " from channel " + channel
# define MESSAGE_CLIENT_KICK(channel, client, target, reason)    client + " kicked " + target + " from channel " + channel + " for reason: " + reason
# define MESSAGE_ADMIN_CHANGE(channel, client)                   client + " is now the admin of the channel " + channel


#endif // MACROS_HPP




/* 
On RPL_NAMREPLY <symbol> notes the status of the channel. It can be one of the following:

    ("=", 0x3D) - Public channel.

Prefixos para usuários:

    ~ para dono do canal    (+q)
    352 irc.example.com #nome_do_canal user1 203.0.113.1 user1 * @ irc.example.com 1 :John Doe

    @ para operadores do canal    (+o)
    352 irc.example.com #nome_do_canal user2 198.51.100.1 user2 * ~ irc.example.com 1 :Jane Smith

    usuários comuns não possuem symbol
    352 irc.example.com #nome_do_canal user3 203.0.113.2 user3 *   irc.example.com 1 :Carlos Silva
*/