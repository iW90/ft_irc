#pragma once

#ifndef MACROS_HPP
# define MACROS_HPP


/* General Responses */

# define RPL_WELCOME(source, client)                     "001 " + source + " :Welcome " + client + " to the ft_irc network"
# define RPL_YOURHOST(source)                            "002 " + source + " :Your host is ft_irc, running version 1.0"
# define RPL_CREATED(source, datetime)                   "003 " + source + " :This server was created " + datetime
# define RPL_MYINFO(source)                              "004 " + source + " ft_irc 1.0 itkol"
# define RPL_ISUPPORT(source)                            "005 " + source + " MAXCHANNELS=1 MAXNICKLEN=30 CHANLIMIT=1"
# define RPL_LIST(source, channel, clientcount, topic)   "322 " + source + " #" + channel + " " + clientcount + " :" + topic
# define RPL_LISTEND(source)                             "323 " + source + " :End of /LIST"
# define RPL_NAMREPLY(source, channel, users)            "353 " + source + " = #" + channel + " :" + users
# define RPL_ENDOFNAMES(source, channel)                 "366 " + source + " #" + channel + " :End of /NAMES list."
# define RPL_INFO(source, info)                          "371 " + source + " :" info
# define RPL_ENDOFINFO(source)                           "374 " + source + " :End of INFO list"


/* Error Responses */

# define ERR_NOSUCHNICK(source, nickname)                "401 " + source + " " + nickname + " :No such nick"
# define ERR_NOSUCHCHANNEL(source, channel)              "403 " + source + " #" + channel + " :No such channel"
# define ERR_CANNOTSENDTOCHAN(source, channel)           "404 " + source + " #" + channel + " :Cannot send to channel"
# define ERR_TOOMANYCHANNELS(source, channel)            "405 " + source + " #" + channel + " :You have joined too many channels"
# define ERR_UNKNOWNCOMMAND(source, command)             "421 " + source + " " + command + " :Unknown command"
# define ERR_NONICKNAMEGIVEN(source)                     "431 " + source + " :Nickname not given"
# define ERR_NICKNAMEINUSE(source)                       "433 " + source + " " + source  + " :Nickname is already in use"
# define ERR_USERNOTINCHANNEL(source, nickname, channel) "441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"
# define ERR_NOTONCHANNEL(source, channel)               "442 " + source + " #" + channel + " :You're not on that channel"
# define ERR_NOTREGISTERED(source)                       "451 " + source + " :You have not registered"
# define ERR_NEEDMOREPARAMS(source, command)             "461 " + source + " " + command + " :Not enough parameters"
# define ERR_ALREADYREGISTERED(source)                   "462 " + source + " :You may not register"
# define ERR_PASSWDMISMATCH(source)                      "464 " + source + " :Password is incorrect"
# define ERR_CHANNELISFULL(source, channel)              "471 " + source + " #" + channel + " :Cannot join channel (+l)"
# define ERR_UNKNOWNMODE(source)                         "472 " + source + " #" + channel + " :is unknown mode char to me"
# define ERR_INVITEONLYCHAN(source, channel)             "473 " + source + " #" + channel + " :Cannot join channel (+i)"
# define ERR_BANNEDFROMCHAN(source, channel)             "474 " + source + " #" + channel + " :Cannot join channel (+b)"
# define ERR_BADCHANNELKEY(source, channel)              "475 " + source + " #" + channel + " :Cannot join channel (+k)"
# define ERR_NOPRIVILEGES(source)                        "481 " + source + " :Permission Denied- You're not an IRC operator"
# define ERR_CHANOPRIVSNEEDED(source, channel)           "482 " + source + " #" + channel + " :You're not channel operator"


/* Command Responses */

# define RPL_JOIN(source, channel)                       ":" + source + " JOIN :#" + channel
# define RPL_PART(source, channel)                       ":" + source + " PART :#" + channel
# define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message
# define RPL_QUIT(source, message)                       ":" + source + " QUIT :Quit: " + message
# define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK #" + channel + " " + target + " :" + reason
# define RPL_MODE(source, channel, modes, args)          ":" + source + " MODE #" + channel + " " + modes + " " + args
# define RPL_TOPIC(source, channel, topic)               ":" + source + " TOPIC #" + channel + " :" + topic
# define RPL_INVITE(source, target, channel)             ":" + source + " INVITE " + target + " to #" + channel
# define RPL_NICK(source)                                ":" + source + " NICK: is now " + source
# define RPL_NOTICE(source, target, message)             ":" + source + " PRIVMSG " + target + " :" + message
# define RPL_PING(source, token)                         ":" + source + " PONG :" + token



/* Broadcast messages */

# define MESSAGE_CLIENT_JOIN(channel, client)                    client + " joined the channel " + channel
# define MESSAGE_CLIENT_LEAVE(channel, client)                   client + " left " + client + " from channel " + channel
# define MESSAGE_CLIENT_KICK(channel, client, target, reason)    client + " kicked " + target + " from channel " + channel + " for reason: " + reason
# define MESSAGE_ADMIN_CHANGE(channel, client)                   client + " is now the admin of the channel " + channel


#endif // MACROS_HPP
