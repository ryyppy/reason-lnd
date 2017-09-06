open Game;

type data = {
  board: array (array string),
  game: array string
};

let string_to_token str =>
  switch str {
    | "x" => Cross
    | "o" => Circle
    | _ => Empty
  };

let parseRow row => {
  switch row {
    | [|c1, c2, c3|] => {
        (string_to_token c1, string_to_token c2, string_to_token c3);
      }
    | _ => (Empty, Empty, Empty)
  };
};

let parseRows rows => {
  switch rows {
    | [|r1, r2, r3|] => {
        (parseRow r1, parseRow r2, parseRow r3);
      }
    | _ => ((Empty, Empty, Empty), (Empty, Empty, Empty), (Empty, Empty, Empty))
  };
};

let parsePlayer [|_, player|] =>
  switch player {
    | "o" => CirclePlayer
    | "x" => CrossPlayer
    | _ => CirclePlayer
  };

type convertedData = {
  rows: (row, row, row),
  player: playerState
};

let convertData : data => convertedData = fun {board, game} =>
  { rows: parseRows board, player: parsePlayer game };

let parseGameJson json =>
  Json.Decode.{
    board: field "board" (array (array string)) json,
    game: field "game" (array string) json
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
        "game": ["Turn", "x"]
      }
    |js}
  ) |> convertData;
