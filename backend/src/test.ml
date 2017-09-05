open State

let stateToString state = ""

let emptyRow = (Empty, Empty, Empty)

let state = {
  board = (emptyRow, emptyRow, emptyRow);
  game = Turn X
}

let _ =
  (* print_endline (State_j.string_of_state state) *)
  print_endline (Yojson.to_string (State.json_of_state state))


