# 调试与测试

为了方便进行可重现的测试, 同时尽可能降低配环境的开销, 我们利用 Linux 的 network namespaces 功能创建出若干个虚拟的网络域 (相当于若干台物理主机) 组成一个局域网, 并在这个局域网中跑测试。创建 network namespaces 的工具由助教提供, 位于 [nsutils/](nsutils) 目录下。本文档对这些工具做一简要介绍。

本文档所有指令默认当前工作目录为 nsutils/ 目录。

## 进入测试环境

```sh
./nsstart
```

进入测试环境后, 在正常的 shell prompt 之前应该可以看到 `(net default)` 字样, 表示当前网络域为默认网络域。需要注意的是, 测试环境中不能连接到国际互联网。可以通过 `ip a` 指令查看当前 ip 地址及网络连接状态。如果你的操作系统是 Linux 或者可以使用 WSLg, 还可以使用 `wireshark` 命令直接在测试环境中打开 Wireshark。

## 退出测试环境

测试环境是一个子进程中的 shell; 正常退出 shell (Ctrl+D 或 exit) 即可退出测试环境。

## 加载网络拓扑

进入测试环境时使用

```sh
./nsstart topo/sample.ns
```

即可生成 [topo/sample.ns](topo/sample.ns) 中描述的网络拓扑。

## 测试环境中的新增命令

测试环境中提供了一些命令。这些命令大多为 shell function, 无法由其他程序调用, 只能在 shell 中直接输入。

- `pns`: 打印当前 namespace 名称。
- `lsns`: 列出所有 namespace。(此命令与系统的 `lsns` 命令重名, 但功能不同。)
- `setns nsname`: 进入 `nsname` 所指定的 namespace。
- `nsexec nsname [cmd [args...]]`: 在 `nsname` 这一 namespace 中执行程序。若 `cmd` 为空, 则会执行 shell。

## 测试环境中的服务

在测试环境的每个 namespace 中均会在 20080 端口上启动一个 TCP 服务。连接到该服务器后，服务器会返回连接者的 IP 地址并直接退出。

使用例子:

```sh
./nsstart topo/sample.ns
nc net1.ns1.test 20080 < /dev/null
nc net1.v6.ns1.test 20080 < /dev/null
```

## 进行测试

进行测试之前, 需要先修改 start-proxy 文件中的内容, 使得执行这个文件能够在 PORT 环境变量所指定的端口上打开一个你的代理服务器。

可以通过

```sh
./nstest tests/base/simple.test
```

执行测试。
