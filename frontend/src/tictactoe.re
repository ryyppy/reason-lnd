let namespace = "reason-react-tictactoe";

open Game;

module Top = {
  module TicTacToe = {
    include ReactRe.Component.Stateful;
    let name = "TicTacToe";
    type props = unit;
    type state = {rows: (row, row, row), player: playerState, game: gameState};
    let getInitialState _ => {
      rows: ((Empty, Empty, Empty), (Empty, Empty, Empty), (Empty, Empty, Empty)),
      player: CirclePlayer,
      game: Running
    };
    let restart _ _ => Some (getInitialState ());
    let playTurn {state} (selection: (rowSelection, colSelection)) => {
      let {rows, player, game} = state;
      let (row, column) = selection;
      if (game == Running && isValidTurn rows row column) {
        let newRows = updateRow rows row column (playerToken player);
        Some {rows: newRows, player: switchPlayer player, game: updateGame game newRows player}
      } else {
        Some state
      }
    };
    let renderWin player restartClick =>
      <div>
        <div> (ReactRe.stringToElement (player_to_string player ^ " won!")) </div>
        <button onClick=restartClick> (ReactRe.stringToElement "Restart") </button>
      </div>;
    let renderDraw restartClick =>
      <div>
        <div> (ReactRe.stringToElement "It's a draw!") </div>
        <button onClick=restartClick> (ReactRe.stringToElement "Restart") </button>
      </div>;
    let renderCurrentPlayer player =>
      <div className="game-player">
        (ReactRe.stringToElement ("Player: " ^ player_to_string player))
      </div>;
    let render {state, updater} =>
      <div className="game">
        <div className="game-board">
          <Board rows=state.rows handleSquareClick=(updater playTurn) />
        </div>
        (
          switch state.game {
          | Running => renderCurrentPlayer state.player
          | Win p => renderWin p (updater restart)
          | Draw => renderDraw (updater restart)
          }
        )
      </div>;
  };
  include ReactRe.CreateComponent TicTacToe;
  let createElement = wrapProps ();
};

ReactDOMRe.renderToElementWithClassName <Top /> "tictactoe";
