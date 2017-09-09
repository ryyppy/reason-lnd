open Game;

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

let parseRows rows =>
  switch rows {
  | [|r1, r2, r3|] => (parseRow r1, parseRow r2, parseRow r3)
  | _ => ((Empty, Empty, Empty), (Empty, Empty, Empty), (Empty, Empty, Empty))
  };

/* let parsePlayer [|_, player|] => */
/*   switch player { */
/*     | "o" => CirclePlayer */
/*     | "x" => CrossPlayer */
/*     | _ => CirclePlayer */
/*   }; */
/* mock this for now */
let parseProgress _input => Turn CirclePlayer;

let convertData: data => ticTacToeState =
  fun {board, progress} => {board: parseRows board, progress: parseProgress progress};

let parseGameJson json =>
  Json.Decode.{
    board: field "board" (array (array string)) json,
    progress: field "progress" (array string) json
  };

let fetchData _ =>
  parseGameJson (
    Js.Json.parseExn {js|
      {
        "board": [
          ["x", "o", "empty"],
          ["x", "o", "empty"],
          ["x", "empty", "o"]
        ],
        "progress": ["Turn", "x"]
      }
    |js}
  ) |> convertData;
