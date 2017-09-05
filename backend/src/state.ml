type token =
  | O
  | X
  | Empty

type row = (token * token * token)

type board = (row * row * row)

type player =
  | O
  | X

type game =
  | Turn of player
  | Win of player
  | Draw

type state = {
  board: board;
  game: game;
}

let json_of_token (token: token) =
  match token with
  | O -> `String "o"
  | X -> `String "x"
  | Empty -> `String "empty"

let json_of_row row =
  let (t1, t2, t3) = row in
  `List [
    json_of_token t1;
    json_of_token t2;
    json_of_token t3
  ]

let json_of_board board =
  let (r1, r2, r3) = board in
  `List [
    json_of_row r1;
    json_of_row r2;
    json_of_row r3
  ]

let json_of_player player =
  match player with
  | O -> `String "o"
  | X -> `String "x"

let json_of_game game =
  match game with
  | Turn player -> `List [ `String "Turn"; json_of_player player ]
  | Win player -> `List [ `String "Win"; json_of_player player ]
  | Draw -> `List [ `String "Draw" ]


let json_of_state state =
  `Assoc [
    ("board", (json_of_board state.board));
    ("game", (json_of_game state.game))
  ]
