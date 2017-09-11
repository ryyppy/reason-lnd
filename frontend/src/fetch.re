open Game;

exception MalformedData string;

type remoteData =
  | NotAsked
  | Loading
  | Error string
  | Success Game.ticTacToeState;

type data = {
  board: array (array string),
  progress: array string
};

let string_to_token str =>
  switch str {
  | "x" => Cross
  | "o" => Circle
  | _ => Empty
  };

let parseRow row =>
  switch row {
  | [|c1, c2, c3|] => (string_to_token c1, string_to_token c2, string_to_token c3)
  | _ => (Empty, Empty, Empty)
  };

let parseBoard board =>
  switch board {
  | [|r1, r2, r3|] => (parseRow r1, parseRow r2, parseRow r3)
  | _ => ((Empty, Empty, Empty), (Empty, Empty, Empty), (Empty, Empty, Empty))
  };

let parsePlayer p =>
  switch p {
  | "o" => CirclePlayer
  | "x" => CrossPlayer
  | _ => CirclePlayer
  };

/* mock this for now */
let parseProgress arr =>
  switch arr {
  | [||] => raise (MalformedData "Progress doesn't contain any data")
  | [|"Draw"|] => Draw
  | [|"Turn", p|] => Turn (parsePlayer p)
  | [|"Win", p|] => Win (parsePlayer p)
  | rest =>
    raise (
      MalformedData ("Could not parse progress: [" ^ String.concat "," (Array.to_list rest) ^ "]")
    )
  };

let convertData {board, progress} :ticTacToeState => {
  board: parseBoard board,
  progress: parseProgress progress
};

let parseGameJsonExn body =>
  Js.Json.parseExn body |> (
    fun json =>
      Json.Decode.{
        board: field "board" (array (array string)) json,
        progress: field "progress" (array string) json
      }
  ) |> convertData;

let handleFailure =
  (
    fun
    | MalformedData str => str
  )
  [@bs.open];

let mockBody = {js|
      {
        "board": [
          ["x", "o", "empty"],
          ["x", "o", "empty"],
          ["x", "empty", "o"]
        ],
        "progress": ["Turn", "x"]
      }
   |js};

let fetchData _ =>
  Js.Promise.(
    make (
      fun ::resolve ::reject =>
        try (parseGameJsonExn mockBody |> (fun data => resolve data [@bs])) {
        | ex => reject ex [@bs]
        }
    )
  );
