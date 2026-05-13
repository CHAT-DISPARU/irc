*This project has been created as part of the 42 curriculum by gajanvie & rolavale*

# Description

## IRC

IRC (Internet Relay Chat) is a global text-based chat system. It requires an internet connection and an IRC messaging client, which sends and receives messages via IRC servers.

## Client

We chose to use HexChat, for reasons of simplicity. However, there are a plethora of other IRC clients such as Irssi, KiwiIRC, Quassel, etc.

## Commands

* `KICK` : Eject a client from the channel
* `INVITE` : Invite a client to a channel
* `TOPIC` : Change or view the channel topic
* `MODE` : Change the channel's mode:
  * `i` : Set/remove Invite-only channel
  * `t` : Set/remove the restrictions of the `TOPIC` command to channel operators
  * `k` : Set/remove the channel key (password)
  * `o` : Give/take channel operator privilege
  * `l` : Set/remove the user limit to channel
* `JOIN` : Join a channel
* `NICK` : Set a nickname
* `USER` : Set user parameters
* `PASS` : Enter the password of the server
* `PART` : Leave a channel
* `PRIVMSG` : Send a private message to a user or in a channel
* `PING` : Ping a user or a channel
* `PONG` : Pong to the server
* `WHO` : Requests a list of users matching a specified mask or channel. Particularly useful for discovering active users on the network (e.g., used by our bot to find and greet new users).
* `WHOIS` : Obtain a user's info
* `QUIT` : Quit the server

## Bot

**Usage:** `./bot <host> <port> <password> <bot_nickname> [curse database]`

**Description:** This custom IRC bot connects to the server to provide automated channel moderation, user greetings, and interactive features.

### Capabilities & Features

* **Auto-Greeting:** The bot periodically scans the server (using the `WHO *` command) to discover new users. It sends a welcoming private message to anyone new, introducing itself and its features.
* **Auto-Join:** If a user uses the `INVITE` command to invite the bot to a channel, it will automatically `JOIN` that channel and send an introductory message listing its available commands.
* **Automated Moderation (Curse Filter):** If provided with a `[curse database]` file at launch, the bot monitors messages in its channels for blacklisted words.
  * If the bot detects a curse word and has Operator status (`+o`), it will automatically `KICK` the offending user.
  * If it detects a curse word but does not have Operator status, it will send a warning to the channel noting the infraction but stating it lacks the rights to kick.
* **Graceful Exit:** Upon shutting down, the bot automatically sends `PART` commands to safely leave all active channels before closing its connection.

### Interactive Commands

Users can interact with the bot using the `PRIVMSG` command with the `!` prefix:

* `!help` : Prompts the bot to re-introduce itself and list its available commands.
* `!random` : A luck-based mini-game. The bot rolls a number between 0 and 100. The user only wins if the bot rolls exactly 42.
* `!love <target_user>` : Calculates and displays a random "love percentage" between the sender and the target user.
* `!slap <target_user>` : Sends a playful action message stating the sender violently slapped the target.
* `!answer <question>` : Acts like a Magic 8-Ball, providing a random definitive answer (e.g., "Yes", "No", "Maybe", "Wtf never") to the user's question.

# Instructions

Use `make` to compile the project.  
Then run `./ircserv <port> <password>`.

# Resources

* [IRC Modern Documentation — Commands](https://modern.ircdocs.horse/#commands)
* [IRC Modern Documentation — Numerics](https://modern.ircdocs.horse/#numerics)
* [RFC 2812 — Internet Relay Chat: Client Protocol](https://www.rfc-editor.org/rfc/rfc2812)

# AI

AI was utilized as an educational resource to better understand the internal workings, special edge cases, and expected server/client behaviors of specific IRC commands during the development process. Also used to help write this README.
