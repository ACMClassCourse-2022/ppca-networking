# UDP 代理

我们的简单代理服务器只能处理 TCP CONNECT 请求。可以实现 UDP ASSOCIATE 请求来实现 UDP 代理。

TCP 协议是基于连接的; 一般来说, 客户端会随意选择自己一方的端口号, 这个端口号是一次性的。因此, 我们可以很容易地在一个 TCP 连接中代理另一个 TCP 连接, 在连接中止后即可释放所使用的端口号。但是，UDP 协议中没有连接的概念。UDP 服务器与客户端之间通常依靠上层协议维护客户端端口号的分配。例如, 在 DNS 协议中, 查询请求是一个 UDP 报文, 查询结果报文的 destination port 会是查询请求的 source port, 而此后这一临时端口就不再使用了, 却没有任何 UDP 协议层的通知 (TCP 有 FIN/RST)。而在同样基于 UDP 的 HTTP/3 协议中, 客户端的端口号会在 HTTP 连接的过程中一直使用, 直到 HTTP/3 连接断开。断开时同样没有任何 UDP 协议层的通知。

因此, 我们需要引入一种机制来让客户端将 UDP “连接” 的情况告知服务器。这一机制在 socks5 中就是 UDP ASSOCIATE 请求。临时端口号在请求开始时建立, 在请求对应的 TCP 连接终止时结束。

在接到请求时, 代理服务器会在一个临时的 UDP 端口 (reply 中的 BND.PORT) 上监听用户发来的报文。当代理客户端希望向一个服务器发送 UDP 包时, 它会向这个代理服务器的 BND.PORT 上发送 UDP 包 (带有 socks 头; 包头中指明了这个报文希望发送给的服务器地址 DST.ADDR 与 DST.PORT)。代理服务器收到 UDP 包时, 会分配一个端口用于与 DST.ADDR 通信, 然后用这个端口发送 UDP 包。当这个端口收到 UDP 包时, 会以 BND.PORT 为发送端口向代理客户端的对应端口转发加上 socks 头的报文。

你无需支持 fragmentation。

## 测试

很多 socks 客户端都不支持 UDP 代理。可以使用 dante 中的 socksify 命令来测试你的 UDP 代理, 参考 [1]。(注意这种方法无法代理 Go 语言编译出的二进制文件。) 在 Ubuntu 中, 可以使用 `apt install dante-client` 安装所需要的工具。Arch Linux 中的包名为 `dante`。

[1]: https://unix.stackexchange.com/a/744773
