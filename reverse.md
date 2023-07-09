# 反向代理

正常的代理服务器工作流:

- User → Proxy: 建立连接。
- User → Proxy: 帮我连一下 Server。
- Proxy → Server: 建立连接。
- Proxy → User: 好, 连上了。接下来的消息我会转给 Server。

反向代理工作流:

- User → Reverse Proxy: 建立连接。
- Reverse Proxy → Server: 建立连接。

在逻辑意义上, 正常代理代表客户端向服务器发起连接; 反向代理代表服务器从客户端接受连接。

## TCP 反向代理

直接实现 TCP 反向代理十分简单, 不计入任选实现的 credit。你需要在以下任意功能的基础上, 在支持正常代理模式的同时支持 TCP 反向代理模式:

- [TLS 劫持](tls.md)
- [HTTP 捕获/修改/重放](replay.md)
- [分流规则](rules.md)
- [多级代理](chain.md)

## HTTP 反向代理

HTTP 反代就相当于一个 HTTP 服务器, 只不过会将所有收到的请求经过修改转发给另一台服务器。HTTP 反代的一大用处是 virtual hosting, 即通过判断 HTTP 头中的 Host 信息将不同 Host 的请求转发给不同的服务器。这样就可以将多个域名指向同一 IP 地址, 而访问这些域名时会返回不同网站。(你需要实现这一功能。)

加分项: 同时支持 TLS 劫持 / HTTP 操作 / 分流规则 / 多级代理。
