open Fetch;

let se = ReasonReact.stringToElement;

type state = Fetch.remoteData;

type action =
  | Load
  | Failed string
  | Finished Game.ticTacToeState;

let component = ReasonReact.reducerComponent "Loader";

let make _ => {
  ...component,
  initialState: fun () => NotAsked,
  didMount: fun self => {
    Js.Promise.(
      Fetch.fetchData () |>
      then_ (fun data => (self.reduce (fun () => Finished data)) () |> resolve) |>
      catch (
        fun err =>
          switch (Fetch.handleFailure err) {
          | Some msg =>
            self.reduce (fun () => Failed msg) ();
            resolve ()
          | None =>
            self.reduce (fun () => Failed "Unhandled Exception occurred!") ();
            resolve ()
          }
      )
    ) |> ignore;
    ReasonReact.NoUpdate
  },
  reducer: fun action _state =>
    switch action {
    | Load => ReasonReact.Update Loading
    | Failed msg => ReasonReact.Update (Error msg)
    | Finished data => ReasonReact.Update (Success data)
    },
  render: fun {state} =>
    switch state {
    | NotAsked => <div> (se "Starting Application") </div>
    | Loading => <div> (se "Loading Game...") </div>
    | Error errorMsg => <div> (se errorMsg) </div>
    | Success {board, progress} => <Tictactoe board progress />
    }
};
