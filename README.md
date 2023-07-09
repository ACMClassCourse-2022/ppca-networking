# PPCA 2023 网络项目 

## 项目介绍

了解计算机网络的基本原理，设计并实现一个网络代理。

## 项目要求

基础要求: [简单代理服务器](base.md)

任选实现:

- [透明代理](tun.md) 4’
- [代理客户端](client.md) 1’
  - [分流规则](rules.md)
    - [按 socks 地址分流](rules-ip.md) 1’
    - 按域名分流
      - [HTTP 分流](rules-http.md) 1’
      - [TLS 分流](rules-tls.md) 1’
    - [按程序分流](rules-program.md) 1’
  - [多级代理](chain.md) 2’
- [UDP 代理](udp.md) 1’
- [TLS 劫持](tls.md) 2’
- [HTTP 捕获/修改/重放](replay.md) 3’
- [反向代理](reverse.md)
  - TCP 反向代理 1’
  - HTTP 反向代理 1’
- 自选选题 (请与助教联系)

建议第一周完成基础任务，后面三周中每周完成 2’–3’ 的任务。

请务必提前规划好这些功能之间的相互作用, 并考虑这些相互作用对程序整体架构带来的影响! 建议实现之前先与助教讨论你的选题和大体实现思路。

以上的工作量仅仅是助教的估计; 如果认为此估计不合理，请及时向助教提出。

## 评分标准

ACM 班:

- 简单代理服务器 25%
- 自选功能
  - 实现共 6’ 的功能可以得到 55%
  - 实现共 9’ 的功能可以得到 65%
- Code review 20%

工科:

- 简单代理服务器 40%
- 自选功能
  - 实现共 2’ 的功能可以得到 40%
  - 实现共 3’ 的功能可以得到 50%
- Code review 20%

最多可以得到 110% 的分数。

## 参考资料

**参考书**:

- [Beej’s Guide to Network Programming](https://beej.us/guide/bgnet/)
- [High Performance Browser Networking](https://hpbn.co/)
  - 书中内容远超出此次项目的要求, 只看 Networking 101 及 HTTP 中的一部分即可
  - [中文版 pdf](https://jbox.sjtu.edu.cn/l/O1voXQ)
- [TCP/IP Tutorial and Technical Overview](https://www.redbooks.ibm.com/redbooks/pdfs/gg243376.pdf)

**协议文档**:

- [RFC 1928: SOCKS Protocol Version 5](https://www.rfc-editor.org/rfc/rfc1928)
- [RFC 9293: Transmission Control Protocol (TCP)](https://www.rfc-editor.org/rfc/rfc9293)
- [RFC 768: User Datagram Protocol](https://www.rfc-editor.org/rfc/rfc768)
- [RFC 9112: HTTP/1.1](https://www.rfc-editor.org/rfc/rfc9112.html)
- [HTTP on MDN](https://developer.mozilla.org/en-US/docs/Web/HTTP)
- [RFC 8446: The Transport Layer Security (TLS) Protocol Version 1.3](https://www.rfc-editor.org/rfc/rfc8446)

欢迎补充。

## Q&amp;A

<https://notes.sjtu.edu.cn/s/EM0Ahj4tB>

## 致谢

2019 级 ACM 班的许烨辰、周聪为本项目提供了主要思路和很多建议。
