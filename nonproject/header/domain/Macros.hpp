#pragma once

#ifndef MACROS_HPP
# define MACROS_HPP


/* General Responses */

# define RPL_WELCOME(source, client)                     "001 " + source + " :Welcome " + client + " to the ft_irc network"
# define RPL_YOURHOST(source)                            "002 " + source + " :Your host is ft_irc, running version 1.0"
# define RPL_CREATED(source, datetime)                   "003 " + source + " :This server was created " + datetime
# define RPL_MYINFO(source)                              "004 " + source + " ft_irc 1.0 itkol"

//# define RPL_LIST(source, channel, clientcount, topic)   "322 " + source + " #" + channel + " " + clientcount + " :" + topic
//# define RPL_LISTEND(source)                             "323 " + source + " :End of /LIST"
//# define RPL_NAMREPLY(source, channel, users)            "353 " + source + " = #" + channel + " :" + users
//# define RPL_ENDOFNAMES(source, channel)                 "366 " + source + " #" + channel + " :End of /NAMES list"

# define RPL_ISUPPORT(source)                            "005 " + source + " MAXCHANNELS=1 MAXNICKLEN=30 CHANLIMIT=1 CHANMODES=b,k,l,it PREFIX=(o)@ :are supported by this server"
//# define RPL_ENDOFWHO(source, mask)                      "315 " + source + mask + " :End of WHO list" // <mask> MUST be the same <mask> parameter sent by the client in its WHO message, but MAY be casefolded.
# define RPL_ENDOFWHO(source, channel)                   "315 " + source + " #" + channel + " :End of WHO list"
# define RPL_LISTSTART(source)                           "321 " + source + " Channel :Users Name" // Sent as a reply to the LIST command, this numeric marks the start of a channel list. As noted in the command description, this numeric MAY be skipped by the server so clients MUST NOT depend on receiving it.
# define RPL_LIST(source, channel, clientcount, topic)   "322 " + source + " " + channel + " " + clientcount + " :" + topic
# define RPL_LISTEND(source)                             "323 " + source + " :End of /LIST"
//# define RPL_NOTOPIC(source, channel)                    "331 " + source + " #" + channel + " :No topic is set"
# define RPL_NOTOPIC(source, channel)                    "331 " + source + channel + " :No topic is set" // Sent to a client when joining a channel to inform them that the channel with the name <channel> does not have any topic set.
//# define RPL_TOPIC(source, channel, topic)               "332 " + source + channel + " :" + topic
# define RPL_TOPIC(source, channel, topic)               "332 " + source + " #" + channel + " :" + topic
# define RPL_TOPICWHOTIME(source, channel, user, time)   "333 " + source + " #" + channel + " " + user + " " + time
//# define RPL_TOPICWHOTIME(source, channel, nick, setat)  "333 " + source + channel + nick + " :" + topic // <setat> is a unix timestamp, e <nick> é de quem escreveu o tópico
# define RPL_INVITELIST(source, channel)                 "336 " + source + channel
# define RPL_ENDOFINVITELIST(source)                     "337 " + source + " :End of /INVITE list"
# define RPL_INVITING(client, nick, channel)             "341 " + source + nick + channel
//# define RPL_WHOREPLY                                    "352 " + source + " :" // "<client> <channel> <username> <host> <server> <nick> <flags> :<hopcount> <realname>"
# define RPL_WHOREPLY(source, channel, users)            "352 " + source + " #" + channel + " " + users
# define RPL_NAMREPLY(source, channel, users)            "353 " + source + " #" + channel + " :" + users // "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
# define RPL_ENDOFNAMES(source, channel)                 "366 " + source + " #" + channel + " :End of /NAMES list."
# define RPL_INFO(source, info)                          "371 " + source + " :" info
# define RPL_ENDOFINFO(source)                           "374 " + source + " :End of INFO list"
# define RPL_HELPSTART(source, subject, text)            "704 " + source + subject + " :" + text  //"<client> <subject> :<first line of help section>"
# define RPL_HELPTXT(source, subject, text)              "705 " + source + subject + " :" + text  //"<client> <subject> :<line of help text>"
# define RPL_ENDOFHELP(source, subject, text)            "706 " + source + subject + " :" + text  //"<client> <subject> :<last line of help text>"

/* 
On RPL_NAMREPLY <symbol> notes the status of the channel. It can be one of the following:

    ("=", 0x3D) - Public channel.
    ("@", 0x40) - Secret channel (secret channel mode "+s").
    ("*", 0x2A) - Private channel (was "+p", no longer widely used today).

Prefixos para usuários:

    ~ para dono do canal    (+q)
    352 irc.example.com #nome_do_canal user1 203.0.113.1 user1 * @ irc.example.com 1 :John Doe

    @ para operadores do canal    (+o)
    352 irc.example.com #nome_do_canal user2 198.51.100.1 user2 * ~ irc.example.com 1 :Jane Smith

    usuários comuns não possuem symbol
    352 irc.example.com #nome_do_canal user3 203.0.113.2 user3 *   irc.example.com 1 :Carlos Silva
*/

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

# define RPL_JOIN(source, channel, target)               ":" + source + " JOIN #" + channel + " * :" + target
# define RPL_PART(source, channel)                       ":" + source + " PART #" + channel
# define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message
# define RPL_QUIT(source, message)                       ":" + source + " QUIT :Quit: " + message
# define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK #" + channel + " " + target + " :" + reason
# define RPL_MODE(source, channel, modes, args)          ":" + source + " MODE #" + channel + " " + modes + " " + args
# define RPL_CHANNELMODEIS(source, channel, modes, args) "324 " + source + " #" + channel + " " + modes + " " + args
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
