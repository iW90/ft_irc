#pragma once

#ifndef MACROS_HPP
# define MACROS_HPP


/* General Responses */

# define RPL_WELCOME(source, client)                     ":ft_irc 001 " + source + " :Welcome " + client + " to the ft_irc network"
# define RPL_YOURHOST(source)                            ":ft_irc 002 " + source + " :Your host is ft_irc, running version 1.0"
# define RPL_CREATED(source, datetime)                   ":ft_irc 003 " + source + " :This server was created " + datetime
# define RPL_MYINFO(source)                              ":ft_irc 004 " + source + " ft_irc 1.0 itkol"
# define RPL_ISUPPORT(source)                            ":ft_irc 005 " + source + " CHANMODES=b,k,l,it PREFIX=(o)@ :are supported by this server"
# define RPL_ENDOFWHO(source, channel)                   ":ft_irc 315 " + source + " #" + channel + " :End of WHO list"
# define RPL_LIST(source, channel, clientcount, topic)   ":ft_irc 322 " + source + " #" + channel + " " + clientcount + " :" + topic
# define RPL_LISTEND(source)                             ":ft_irc 323 " + source + " :End of /LIST"
# define RPL_WHOREPLY(source, channel, users)            ":ft_irc 352 " + source + " #" + channel + " " + users
# define RPL_NAMREPLY(source, channel, users)            ":ft_irc 353 " + source + " = #" + channel + " :" + users
# define RPL_ENDOFNAMES(source, channel)                 ":ft_irc 366 " + source + " #" + channel + " :End of /NAMES list"
# define RPL_INFO(source, info)                          ":ft_irc 371 " + source + " :" info
# define RPL_ENDOFINFO(source)                           ":ft_irc 374 " + source + " :End of INFO list"


/* Error Responses */

# define ERR_NOSUCHNICK(source, nickname)                ":ft_irc 401 " + source + " " + nickname + " :No such nick"
# define ERR_NOSUCHCHANNEL(source, channel)              ":ft_irc 403 " + source + " #" + channel + " :No such channel"
# define ERR_CANNOTSENDTOCHAN(source, channel)           ":ft_irc 404 " + source + " #" + channel + " :Cannot send to channel"
# define ERR_TOOMANYCHANNELS(source, channel)            ":ft_irc 405 " + source + " #" + channel + " :You have joined too many channels"
# define ERR_UNKNOWNCOMMAND(source, command)             ":ft_irc 421 " + source + " " + command + " :Unknown command"
# define ERR_NONICKNAMEGIVEN(source)                     ":ft_irc 431 " + source + " :Nickname not given"
# define ERR_NICKNAMEINUSE(source)                       ":ft_irc 433 " + source + " " + source  + " :Nickname is already in use"
# define ERR_USERNOTINCHANNEL(source, nickname, channel) ":ft_irc 441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"
# define ERR_NOTONCHANNEL(source, channel)               ":ft_irc 442 " + source + " #" + channel + " :You're not on that channel"
# define ERR_NOTREGISTERED(source)                       ":ft_irc 451 " + source + " :You have not registered"
# define ERR_NEEDMOREPARAMS(source, command)             ":ft_irc 461 " + source + " " + command + " :Not enough parameters"
# define ERR_ALREADYREGISTERED(source)                   ":ft_irc 462 " + source + " :You may not register"
# define ERR_PASSWDMISMATCH(source)                      ":ft_irc 464 " + source + " :Password is incorrect"
# define ERR_CHANNELISFULL(source, channel)              ":ft_irc 471 " + source + " #" + channel + " :Cannot join channel (+l)"
# define ERR_UNKNOWNMODE(source)                         ":ft_irc 472 " + source + " #" + channel + " :is unknown mode char to me"
# define ERR_INVITEONLYCHAN(source, channel)             ":ft_irc 473 " + source + " #" + channel + " :Cannot join channel (+i)"
# define ERR_BANNEDFROMCHAN(source, channel)             ":ft_irc 474 " + source + " #" + channel + " :Cannot join channel (+b)"
# define ERR_BADCHANNELKEY(source, channel)              ":ft_irc 475 " + source + " #" + channel + " :Cannot join channel (+k)"
# define ERR_NOPRIVILEGES(source)                        ":ft_irc 481 " + source + " :Permission Denied- You're not an IRC operator"
# define ERR_CHANOPRIVSNEEDED(source, channel)           ":ft_irc 482 " + source + " #" + channel + " :You're not channel operator"


/* Command Responses */

# define RPL_JOIN(source, channel, target)               ":" + source + " JOIN #" + channel + " * :" + target
# define RPL_PART(source, channel)                       ":" + source + " PART #" + channel
# define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message
# define RPL_QUIT(source, message)                       ":" + source + " QUIT :Quit: " + message
# define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK #" + channel + " " + target + " :" + reason
# define RPL_MODE(source, channel, modes, args)          ":" + source + " MODE #" + channel + " " + modes + " " + args
# define RPL_CHANNELMODEIS(source, channel, modes, args) ":ft_irc 324 " + source + " #" + channel + " " + modes + " " + args
# define RPL_NOTOPIC(source, channel)                    ":ft_irc 331 " + source + " #" + channel + " :No topic is set"
# define RPL_TOPIC(source, channel, topic)               ":ft_irc 332 " + source + " #" + channel + " :" + topic
# define RPL_TOPICWHOTIME(source, channel, user, time)   ":ft_irc 333 " + source + " #" + channel + " " + user + " " + time
# define RPL_INVITE(source, target, channel)             ":" + source + " INVITE " + target + " to #" + channel
# define RPL_NICK(source)                                ":" + source + " NICK is now " + source
# define RPL_NOTICE(source, target, message)             ":" + source + " PRIVMSG " + target + " :" + message
# define RPL_PING(source, token)                         ":" + source + " PONG :" + token



/* Broadcast messages */

# define MESSAGE_CLIENT_JOIN(channel, client)                    client + " joined the channel " + channel
# define MESSAGE_CLIENT_LEAVE(channel, client)                   client + " left " + client + " from channel " + channel
# define MESSAGE_CLIENT_KICK(channel, client, target, reason)    client + " kicked " + target + " from channel " + channel + " for reason: " + reason
# define MESSAGE_ADMIN_CHANGE(channel, client)                   client + " is now the admin of the channel " + channel


#endif // MACROS_HPP
