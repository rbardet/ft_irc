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
- `*.cpp`, `*.h`, `*.hpp`— Source files
- Optional configuration file

---

## ❗ Restrictions

- Strict C++98 only
- No external libraries (including Boost)
- Single non-blocking I/O handler (`poll()` or equivalent)
- Forking is forbidden

---


> “Code is like humor. When you have to explain it, it’s bad.”  
> — Cory House

---

Feel free to check out the code, use it, and reach out if you have questions or want to contribute!
