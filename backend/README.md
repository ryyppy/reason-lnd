# Check your current Github Pull requests

This project structure was relentlessly copied from https://github.com/mads-hartmann/random/blob/master/gh/README.md.

```sh
opam switch install 4.04.0
opam install jbuilder core yojson ssl tls cohttp async cohttp-lwt cohttp-lwt-unix lwt_ssl
make run
```
## Installing

```sh
opam pin add tictactoe-server .
```

## Uninstalling

```sh
opam uninstall tictactoe-server
opam pin remove tictactoe-server 
```
