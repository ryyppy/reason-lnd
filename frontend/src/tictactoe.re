open Game;

type status = {rows: (row, row, row), player: playerState, game: gameState};

type action =
  | PlayTurn (rowSelection, colSelection)
  | Restart;

type state = {
  rows: (row, row, row),
  player: playerState,
  game: gameState
};

let component = ReasonReact.reducerComponent "TicTacToe";

let se = ReasonReact.stringToElement;

let initialState () => {
  rows: ((Empty, Empty, Empty), (Empty, Empty, Empty), (Empty, Empty, Empty)),
  player: CirclePlayer,
  game: Running
};

let playTurn state (selection: (rowSelection, colSelection)) => {
  let {rows, player, game} = state;
  let (row, column) = selection;
  if (game == Running && isValidTurn rows row column) {
    let newRows = updateRow rows row column (playerToken player);
    {rows: newRows, player: switchPlayer player, game: updateGame game newRows player}
  } else {
    state
  }
};
let renderWin player restartClick =>
  <div>
    <div> (se (player_to_string player ^ " won!")) </div>
    <button onClick=restartClick> (se "Restart") </button>
  </div>;
let renderDraw restartClick =>
  <div>
    <div> (ReasonReact.stringToElement "It's a draw!") </div>
    <button onClick=restartClick> (se "Restart") </button>
  </div>;
let renderCurrentPlayer player =>
  <div className="game-player">
    (se ("Player: " ^ player_to_string player))
  </div>;

let make ::rows=? ::player=? _children => {
  ...component,
  initialState: fun () => {
    let init = initialState ();
    switch (rows, player) {
      | (Some rows, Some player) => {...init, rows, player}
      | (Some rows, None)  => {...init, rows}
      | (None, Some player)  => {...init, player}
      | (None, None) => init
    };
  },
  reducer: fun action state => {
    switch action {
      | PlayTurn s => ReasonReact.Update (playTurn state s)
      | Restart => ReasonReact.Update (initialState ())
    };
  },
  render: fun {state, reduce} => <div className="game">
    <div className="game-board">
      <Board rows=state.rows handleSquareClick=(reduce (fun selection => PlayTurn selection)) />
    </div>
    (
      switch state.game {
      | Running => renderCurrentPlayer state.player
      | Win p => renderWin p (reduce (fun _evt => Restart))
      | Draw => renderDraw (reduce (fun _evt => Restart))
      }
    )
  </div>
};
