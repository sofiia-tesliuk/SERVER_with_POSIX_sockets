# Server_with_POSIX_sockets

### Server:
```
./server <ip_address>
```
If <ip_address> isn't provided, then it will take `127.0.0.1`. <br />
Maintains 10 connections.

### Client:

```
./client <server_ip_address> <d|t|h|m> [message]
```
- `d` -- request date.
- `t` -- request time.
- `h` -- request greeting message.
- `m` -- request to count number of letters in provided message.
