/* let namespace = "reason-react-tictactoe"; */
open Game;

type action =
  | PlayTurn selection
  | Restart;

type state = ticTacToeState;

let component = ReasonReact.reducerComponent "TicTacToe";

/*

 <MyDialog
         onClick=(self.reduce (fun _event => Click))
         onSubmit=(self.reduce (fun _event => Toggle)) />
 */
let se = ReasonReact.stringToElement;

let initialState () => {
  board: ((Empty, Empty, Empty), (Empty, Empty, Empty), (Empty, Empty, Empty)),
  progress: Turn CirclePlayer
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
  <div className="game-player"> (se ("Player: " ^ player_to_string player)) </div>;

let make _ => {
  ...component,
  initialState,
  reducer: fun action state =>
    switch action {
    | PlayTurn s => ReasonReact.Update (playTurn state s)
    | Restart => ReasonReact.Update (initialState ())
    },
  render: fun {state, reduce} =>
    <div className="game">
      <div className="game-board">
        <Board rows=state.board handleSquareClick=(reduce (fun selection => PlayTurn selection)) />
      </div>
      (
        switch state.progress {
        | Turn p => renderCurrentPlayer p
        | Win p => renderWin p (reduce (fun _evt => Restart))
        | Draw => renderDraw (reduce (fun _evt => Restart))
        }
      )
    </div>
};
