type action =
  | Click;

type state = {count: int};

let component = ReasonReact.reducerComponent "Page";

let make _children => {
  ...component,
  initialState: fun () => {count: 0},
  reducer: fun action state =>
    switch action {
    | Click => ReasonReact.Update {count: state.count + 1}
    },
  render: fun self =>
    <div onClick=(self.reduce (fun _event => Click))>
      (ReasonReact.stringToElement ("Hello World " ^ string_of_int self.state.count))
    </div>
};
