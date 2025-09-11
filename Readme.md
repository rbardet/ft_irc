# ft_irc – Internet Relay Chat Server (C++98)

Welcome to **ft_irc**, my implementation of an IRC (Internet Relay Chat) server written entirely in C++98, as part of the 42 curriculum. This project is designed to respect the official IRC protocol specification.

---

## 🚀 Features

- **Multi-client support:** Handles multiple simultaneous connections epoll and fcntl, ensuring non-blocking I/O without forking.
- **Channel management:** Users can join channels, send/receive messages, and operators can manage channel settings.
- **Operator commands:**  
  - `KICK` — Eject a client from a channel  
  - `INVITE` — Invite a client to a channel  
  - `TOPIC` — Change or display the channel topic  
  - `MODE` — Manage channel modes:  
    - `i` — Invite-only  
    - `t` — Restrict TOPIC command to operators  
    - `k` — Set/remove channel password  
    - `o` — Grant/remove operator status  
    - `l` — Set/remove user limit  
- **Real-time message broadcasting:** Messages in channels are instantly relayed to all joined clients.
- **No external libraries:** Only standard C++ and permitted OS/socket functions.

---

## 🌟 Bonus Features

- **File transfer support:** Send files between users directly within the IRC server.
- **Integrated bot:** Welcome user upon joining channel.

---

## 🗂️ Project Structure Overview

```plaintext
ft_irc/
├── Makefile
├── README.md
├── bot/
│   ├── includes/
│   │   ├── Channel.hpp
│   │   ├── Server.hpp
│   │   ├── User.hpp
│   │   └── Utils.hpp
│   ├── Makefile
│   └── srcs/
│       ├── Channel.cpp
│       ├── main.cpp
│       ├── Server.cpp
│       ├── User.cpp
│       └── Utils.cpp
```

---

## 📁 Top-Level Files

- **Makefile**: Compiles the IRC server with standard rules (`all`, `clean`, `fclean`, `re`).
- **README.md**: Project documentation, usage instructions, and architecture overview.
- **bot/**: Contains a separate program from the server. For more about IRC bots, see [Wikipedia: IRC bot](https://en.wikipedia.org/wiki/IRC_bot).

---

### includes/
Header files defining core classes and utilities:

- **Channel.hpp**: Channel management, users, modes, and operator commands.
- **Server.hpp**: Server logic, networking, client handling, and main loop.
- **User.hpp**: User authentication, attributes (nickname, username, permissions).
- **Utils.hpp**: Utility functions and helpers (string manipulation, error handling).

### srcs/
Source files implementing the logic defined in headers:

- **Channel.cpp**: Channel-related operations.
- **main.cpp**: Entry point, argument parsing, server initialization.
- **Server/**: Implementation of IRC server, socket management, event loop and command management.
- **User.cpp**: User management.
- **Utils.cpp**: Utilities shared between modules.

### Makefile
Build automation for the bot, with the same standards as the main Makefile.

---

## ⚙️ Usage

### Build

```bash
make
```

### Run

```bash
./ircserv <port> <password>
```
- `<port>`: Port number for incoming connections
- `<password>`: Password required for client authentication (can be empty)

### Example

```bash
./ircserv 5959 "password"
```

---

## 💡 How it Works

- Connect with any IRC client (we used irssi for the project).
- You can connect the server with the following command :
```bash
irssi -c "ip of the server" -n "your nickname" -w "server password" -p "server port"
```
- Authenticate using the provided password.
- Set your nickname and username, join channels, and start chatting!
- Operators can manage channels and users using IRC commands.

---

## 🧪 Testing

- Handles partial data and fragmented packets.
- Example with `nc` (netcat):

```bash
nc 127.0.0.1 5959
```
Type input in parts, send with `Ctrl+D` to simulate partial packet reception.

---

## 📁 Project Structure

- `Makefile` — Build automation
- `*.cpp`, `*.hpp`— Source files
- Optional configuration file

---

## ❗ Restrictions

- Strict C++98 only
- No external libraries (including Boost)
- Single non-blocking I/O handler (`poll()` or equivalent)
- Forking is forbidden
