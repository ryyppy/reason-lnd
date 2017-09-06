open Fetch;

let se = ReasonReact.stringToElement;

type state
  = Nothing
  | Loading
  | Error string
  | Success convertedData;

type action =
  | Load
  | Finished convertedData;

let component = ReasonReact.reducerComponent "Loader";

let make _ => {
  ...component,
  initialState: fun () => Nothing,
  didMount: fun _self => {
    Fetch.fetchData ()
      |> (fun data => {
        ReasonReact.Update (Success data)
      });
  },
  reducer: fun action _state => {
    switch action {
      | Load => ReasonReact.Update Loading
      | Finished a => ReasonReact.Update (Success a)
    };
  },
  render: fun {state} => {
    switch state {
      | Nothing => <div>(se "Load Data")</div>
      | Loading => <div>(se "Loading")</div>
      | Error errorMsg => <div>(se errorMsg)</div>
      | Success {rows, player} => <Tictactoe rows player />
    };
  }
};
