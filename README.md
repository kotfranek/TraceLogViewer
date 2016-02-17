# TraceLogViewer
CLI [TraceLog][11] viewer

## Features
- [TraceLog][11] compatible
- display the TraceLog .log files
- display the TraceLog UDP backend output

## Changelog
### 0.1.0
- enable the log file reading
- major fixes for the UDP Client
- adaptions to modified ESys API

### 0.0.2
- implement the UDP Client side State Machine

### 0.0.1
- moved code from TraceLog examples

## Building TraceLogViewer
Requires the [ESys][10] framework pre-built and `ESYS_HOME` environment variable
set to directory containing [ESys][10].

Example:

	$ ESYS_HOME="${HOME}/ESys" make

## Todo
- implement the LogOutput to handle raw LogEntry objects

Copyright &copy; 2016 [Przemysław Podwapiński][98].<br>
Distributed under the [Simplified BSD License][99].

[10]:https://github.com/kotfranek/ESys
[11]:https://github.com/kotfranek/TraceLog
[98]:mailto:p.podwapinski@gmail.com
[99]:https://www.freebsd.org/copyright/freebsd-license.html
