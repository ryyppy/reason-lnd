# TicTacToe-Server

This is a small server for some async interaction in the TicTacToe frontend.

Current goal(s) of this project:

* Provide a REST endpoint to store / load the current TicTacToe state

(Note: This project structure was relentlessly copied from https://github.com/mads-hartmann/random/blob/master/gh/README.md)


# Build / Run

```sh
opam switch install 4.04.0
opam install jbuilder core yojson ssl tls cohttp async cohttp-lwt cohttp-lwt-unix lwt_ssl

# Builds the project and creates the server executable
make build

# Run the server
PORT=3000 ./_build/default/server.exe
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

# Endpoint Documentation

## GET /load

On existing TicTacToe state:

```
Status: 200
Accept: json/application

Body:
{
  "board": [
    ["x", "o", "empty"],
    ["x", "o", "empty"],
    ["x", "o", "empty"],
  ],

  // case 1
  "game": ["Turn", "x"]

  // case 2
  "game": ["Turn", "o"]

  // case 3
  "game": ["Win", "o"]

  // case 4
  "game": ["Draw"]
}
```

On non-existing TicTacToe state:

```
Status: 404
Body: Not found
```

## POST /save

Will receive and parse a TicTacToe state and store it for the next `load` call.

On success:

```
Status: 200
Body: OK
```

On failure:

```
Status: 400
Body: <Error message>
```
