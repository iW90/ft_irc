# Comandos

## JOIN

Syntax

```
    Command: JOIN
    Parameters: <channel>{,<channel>} [<key>{,<key>}]
    Alt Params: 0
```

RPL

``` 
    RPL_TOPIC (332)
    RPL_TOPICWHOTIME (333)
    RPL_NAMREPLY (353)
    RPL_ENDOFNAMES (366)
```

HexChat está solicitando o MODE também.


Command Examples:

    JOIN #foobar                    ; join channel #foobar.
    JOIN &foo fubar                 ; join channel &foo using key "fubar".

Message Examples:

    :WiZ JOIN #Twilight_zone        ; WiZ is joining the channel #Twilight_zone
    :dan-!d@localhost JOIN #test    ; dan- is joining the channel #test


## PART

Syntax

```
    Command: PART
    Parameters: <channel>{,<channel>} [<reason>]
```

RPL

``` 
    -
```

Command Examples:

    PART #twilight_zone             ; leave channel "#twilight_zone"

Message Examples:

    :dan-!d@localhost PART #test    ; dan- is leaving the channel #test


## TOPIC

Syntax

```
    Command: TOPIC
    Parameters: <channel> [<topic>]
```

RPL

```
    RPL_NOTOPIC (331)
    RPL_TOPIC (332)
    RPL_TOPICWHOTIME (333) 
```

Command Examples:

    TOPIC #test :New topic          ; Setting the topic on "#test" to "New topic".
    TOPIC #test :                   ; Clearing the topic on "#test"
    TOPIC #test                     ; Checking the topic for "#test"


## PRIVMSG

Syntax

```
    Command: PRIVMSG
    Parameters: <target>{,<target>} <text to be sent>
```

RPL

``` 
    RPL_AWAY (301)    #desnecessário, pois não implementei away
```

Command Examples:

    PRIVMSG Angel :yes I'm receiving it !
                                    ; Command to send a message to Angel.

    PRIVMSG %#bunny :Hi! I have a problem!
                                    ; Command to send a message to halfops
                                    and chanops on #bunny.

    PRIVMSG @%#bunny :Hi! I have a problem!
                                    ; Command to send a message to halfops
                                    and chanops on #bunny. This command is
                                    functionally identical to the above
                                    command.

Message Examples:

    :Angel PRIVMSG Wiz :Hello are you receiving this message ?
                                    ; Message from Angel to Wiz.

    :dan!~h@localhost PRIVMSG #coolpeople :Hi everyone!
                                    ; Message from dan to the channel
                                    #coolpeople



## NOTICE

Syntax

```
    Command: NOTICE
    Parameters: <target>{,<target>} <text to be sent>
```

RPL

``` 

```

> The NOTICE command is used to send notices between users, as well as to send notices to channels. <target> is interpreted the same way as it is for the PRIVMSG command.


## HELP

Syntax

```
    Command: HELP
    Parameters: [<subject>]
```

RPL

``` 
    RPL_HELPSTART (704)
    RPL_HELPTXT (705)
    RPL_ENDOFHELP (706) 
```

Command Examples:

    HELP                                                     ; request generic help
    :server 704 val * :** Help System **                     ; first line
    :server 705 val * :
    :server 705 val * :Try /HELP <command> for specific help,
    :server 705 val * :/HELP USERCMDS to list available
    :server 706 val * :commands, or join the #help channel   ; last line

    HELP PRIVMSG                                             ; request help on PRIVMSG
    :server 704 val PRIVMSG :** The PRIVMSG command **
    :server 705 val PRIVMSG :
    :server 705 val PRIVMSG :The /PRIVMSG command is the main way
    :server 706 val PRIVMSG :to send messages to other users.

    HELP :unknown subject                                    ; request help on "unknown subject"
    :server 524 val * :I do not know anything about this

    HELP :unknown subject
    :server 704 val * :** Help System **
    :server 705 val * :
    :server 705 val * :I do not know anything about this.
    :server 705 val * :
    :server 705 val * :Try /HELP USERCMDS to list available
    :server 706 val * :commands, or join the #help channel


## INFO

Syntax

```
    Command: INFO
    Parameters: None
```

RPL

```
    RPL_INFO (371)
    RPL_ENDOFINFO (374)
```

Command Examples:

    INFO                            ; request info from the server


## LIST

Syntax

```
    Command: LIST
    Parameters: [<channel>{,<channel>}] [<elistcond>{,<elistcond>}]
```

RPL

```
    RPL_LISTSTART (321)
    RPL_LIST (322)
    RPL_LISTEND (323)
```

Command Examples:

    LIST                            ; Command to list all channels


## NAMES

Syntax

```
    Command: NAMES
    Parameters: <channel>{,<channel>}
```

RPL

```
    RPL_NAMREPLY (353)
    RPL_ENDOFNAMES (366)
```

Command Examples:

    NAMES #twilight_zone,#42        ; List all visible users on "#twilight_zone" and "#42".

## WHO

Syntax

```
    Command: WHO
    Parameters: <mask>
```

RPL

```
    RPL_WHOREPLY (352)
    RPL_ENDOFWHO (315)
```

Command Examples:

    WHO emersion        ; request information on user "emersion"
    WHO #ircv3          ; list users in the "#ircv3" channel

Reply Examples:

    :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion calcium.libera.chat emersion H :1 Simon Ser
    :calcium.libera.chat 315 dan emersion :End of WHO list
                                    ; Reply to WHO emersion

    :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion calcium.libera.chat emersion H :1 Simon Ser
    :calcium.libera.chat 352 dan #ircv3 ~val limnoria/val calcium.libera.chat val H :1 Val
    :calcium.libera.chat 315 dan #ircv3 :End of WHO list
                                    ; Reply to WHO #ircv3


## INVITE

Syntax

```
    Command: INVITE
    Parameters: <nickname> <channel>
```

RPL

```
    RPL_INVITING (341)
    RPL_INVITELIST (336)
    RPL_ENDOFINVITELIST (337)
```

> Some rare implementations use numerics 346/347 instead of 336/337 as `RPL_INVITELIST`/`RPL_ENDOFINVITELIST`. You should check the server you are using implements them as expected. 346/347 now generally stands for `RPL_INVEXLIST`/`RPL_ENDOFINVEXLIST`, used for invite-exception list.

Command Examples:

    INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar

Message Examples:

    :dan-!d@localhost INVITE Wiz #test    ; dan- has invited Wiz to the channel #test


## KICK

Syntax

```
    Command: KICK
    Parameters: <channel> <user> *( "," <user> ) [<comment>]
```

RPL

``` 
    -
```

Examples:

   KICK #Finnish Matthew           ; Command to kick Matthew from #Finnish
   KICK #Finnish John :Speaking English
                                   ; Command to kick John from #Finnish
                                   using "Speaking English" as the
                                   reason (comment).
   :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
                                   ; KICK message on channel #Finnish
                                   from WiZ to remove John from channel


## MODE

Syntax

```
    Command: MODE
    Parameters: <target> [<modestring> [<mode arguments>...]]
```

RPL

``` 

```

Command Examples:

    MODE dan +i                     ; Setting the "invisible" user mode on dan.

    MODE #foobar +mb *@127.0.0.1    ; Setting the "moderated" channel mode and
                                    adding the "*@127.0.0.1" mask to the ban
                                    list of the #foobar channel.

Message Examples:

    :dan!~h@localhost MODE #foobar -bl+i *@192.168.0.1
                                    ; dan unbanned the "*@192.168.0.1" mask,
                                    removed the client limit from, and set the
                                    #foobar channel to invite-only.

    :irc.example.com MODE #foobar +o bunny
                                    ; The irc.example.com server gave channel
                                    operator privileges to bunny on #foobar.

Getting modes for a channel (and channel creation time):

    :irc.example.com 324 dan #foobar +nrt
    :irc.example.com 329 dan #foobar 1620807422




# Comandos para acessar o server

Já funcionais:

## NICK

- `:WiZ NICK Kilroy                 ; WiZ changed his nickname to Kilroy.`
- `:dan-!d@localhost NICK Mamoped   ; dan- changed his nickname to Mamoped.`

## USER

- `USER guest 0 * :Ronnie Reagan`

## QUIT

- `:dan-!d@localhost QUIT :Quit: Bye for now!`

## PASS

## CAP

## PING

## PONG