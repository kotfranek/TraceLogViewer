# TraceLogViewer
Command Line Interface [TraceLog][11] viewer

## Features
- [TraceLog][11] compatible
- display the TraceLog .log files
- display the TraceLog UDP backend output

## Building project
### Dependencies
- Requires the [ESys][10] framework installed.
For details refer to ESys instructions.
- Requires the [CMake][20] installed. Minimum version required is 3.0.0.

### Building

In the project root directory execute the shell script configure.sh with root
privileges, if you intend to install the binary output and headers:
```
sudo ./configure.sh
```
This script will create a new output directory, named *build*,
to enable an _out-of-place_ build.

If you choose to install the project, then the binaries will
be copied to default directory, which, on Linux systems is normally _/usr/local/_.

## Usage
```
-f <file>       : list log file content
-u <server_ip> [<client_port>]  : connect to UDP Trace Backend
```

### Examples
#### Open file with TraceLog content
```sh
tlview -f ~/logs/log_7457.log
```
#### Listen and output the remote TraceLog server
Server IP: 10.0.2.15<BR>
Server Port: 55555

```sh
tlview -u 10.0.2.15 55555
```

## Todo
- implement the LogOutput to handle raw LogEntry objects

Copyright &copy; 2016 [Przemysław Podwapiński][98].<br>
Distributed under the [Simplified BSD License][99].

[10]:https://github.com/kotfranek/ESys
[11]:https://github.com/kotfranek/TraceLog
[20]:https://cmake.org/
[98]:mailto:p.podwapinski@gmail.com
[99]:https://www.freebsd.org/copyright/freebsd-license.html
