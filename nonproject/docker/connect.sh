#!/bin/bash
docker run -it --rm irc-client weechat -r "/server add bestserver $(ip -4 addr show docker0 | grep -oP '(?<=inet\s)\d+(\.\d+){3}')/6667 -password=123456 -notls; /set irc.server.bestserver.username $1"

