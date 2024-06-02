# minihex

![minihex showcase](https://ibb.co/bQMF6cF)

A minimalist, single-file hexadecimal editor written in less than 100 lines of C with no dependencies (except the standard library). The program tries to be as simple as possible.
Other features might be added in the future. Boredom made me code it in one day.

## Usage

```
make
./minihex <file>
```

To get help with the commands, do not provide any filename. File editing is done one byte at a time. Colors are present so that you can see things better. You can also use minihex only to see files as hex. Please take notice that there is no option to safe modified buffer when quitting with the `q` command.
