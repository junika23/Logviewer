LogViewer

Implemented using:
Qt Creator 4.3.1
Based on Qt 5.9.1 (GCC 5.3.1 20160406 (Red Hat 5.3.1-6), 64 bit)
running on VMWare Linux guest with Windows 7 host.

Open file: LogViewer.pro
Compile and change if needed.

In original log.json file ("orig.json") there are two "wrong" or invalid data:
1) Line 1438: timestamp is one day older than the others and the height might produce a unusual peak,
2) Line 2140: Height is ilegal number (minus+space+number). Qt JSON parser will return an error while parsing.