# ft_irc – Internet Relay Chat Server (C++98)

Welcome to **ft_irc**, my implementation of an IRC (Internet Relay Chat) server written entirely in C++98, as part of the 42 curriculum. This project is designed to respect strict coding standards, robust error handling, and close adherence to the official IRC protocol specification.

---

## 🚀 Features

- **Compliant with C++98** (compiles with `-std=c++98`)
- **Multi-client support:** Handles multiple simultaneous connections using a single `poll()` (or equivalent) call, ensuring non-blocking I/O without forking.
- **TCP/IP communication** (IPv4/IPv6)
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
- **Authentication:** Clients authenticate with a password and can set nicknames and usernames.
- **Real-time message broadcasting:** Messages in channels are instantly relayed to all joined clients.
- **Clean, robust code:** Every error is handled gracefully; the server will not crash even under memory pressure or unexpected input.
- **Makefile included:** Standard rules (`all`, `clean`, `fclean`, `re`) and no unnecessary relinking.
- **No external libraries:** Only standard C++ and permitted OS/socket functions.

---

## 🌟 Bonus Features

- **File transfer support:** Send files between users directly within the IRC server.
- **Integrated bot:** Enhance your channels with automated responses and fun interactions.

(*Note: Bonus features are only considered if the mandatory part is flawless, as per project guidelines.*)

---

## ⚙️ Usage

### Build

```bash
make
```
- Compiles all sources with `-Wall -Wextra -Werror -std=c++98`
- Produces the `ircserv` executable

### Run

```bash
./ircserv <port> <password>
```
- `<port>`: Port number for incoming connections
- `<password>`: Password required for client authentication

### Example

```bash
./ircserv 6667 mysecretpass
```

---

## 💡 How it Works

- Connect with any IRC client (use your reference client for evaluation).
- Authenticate using the provided password.
- Set your nickname and username, join channels, and start chatting!
- Operators can manage channels and users using IRC commands.

---

## 🧪 Testing

- Handles partial data, low bandwidth, and fragmented packets.
- Example with `nc` (netcat):

```bash
nc 127.0.0.1 6667
```
Type input in parts, send with `Ctrl+D` to simulate partial packet reception.

---

## 📁 Project Structure

- `Makefile` — Build automation
- `*.cpp`, `*.h`, `*.hpp`, `*.tpp`, `*.ipp` — Source files
- Optional configuration file

---

## ❗ Restrictions

- Strict C++98 only
- No external libraries (including Boost)
- Single non-blocking I/O handler (`poll()` or equivalent)
- Forking is forbidden

---

## 👤 Author

**Robin Bardet**  
Student @ 42 Paris  
[GitHub Profile](https://github.com/rbardet)  
Email: robin.bardet.tomczak@gmail.com

---

## 📜 License

This project is released for educational purposes as part of the 42 curriculum.

---

> “Code is like humor. When you have to explain it, it’s bad.”  
> — Cory House

---

Feel free to check out the code, use it, and reach out if you have questions or want to contribute!
