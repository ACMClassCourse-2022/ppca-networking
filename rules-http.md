# 按 HTTP 域名分流

有些程序 (比如 curl) 会在本地解析 ip 地址; 此外, 在透明代理模式下, 代理服务器无法直接从连接头获得域名的信息。因此, 我们可以解析流量的 7 层协议, 从中提取域名信息。

这是一个典型的 HTTP 协议会话:

```
> GET / HTTP/1.1
> Host: localhost:8080
> User-Agent: curl/8.1.2
> Accept: */*
> 
< HTTP/1.1 200 OK
< Content-Type: text/html
< 
< <!doctype html>
< <html>
<   <head>
<     <meta charset="utf-8">
...
```

`>` 表示客户端向服务器发送的字节, `<` 表示服务器向客户端发送的字节。连接的前 4 行以及 6–7 行称为 HTTP 头 (HTTP headers), 前者是请求头 (request headers), 后者是响应头 (response headers)。在请求头中, Host 项就记录了连接的域名。

仅支持 HTTP/1.1 即可。无需考虑 HTTP 的其他版本 (HTTP/0.9, HTTP/1.0, HTTP/2, HTTP/3)。

不考虑 HTTPS 连接; [HTTPS 连接可以通过 TLS 头完成分流](rules-tls.md)。

## 参考资料

[RFC 9112: HTTP/1.1](https://www.rfc-editor.org/rfc/rfc9112.html)
