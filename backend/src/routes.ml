open Cohttp
open Cohttp_lwt_unix

(* OH! what is this? Mutable global state? Gee, we all gonna die~~ *)
let currentState: (State.state option) ref = ref None;;

let serializeState state =
  Yojson.to_string (State.json_of_state state)

let saveRoute =
  Server.respond_string ~status:`OK ~body:"/save route" ()

let loadRoute =
  match !currentState with
  | Some s -> Server.respond_string ~status:`OK ~body:(serializeState s) ()
  | None -> Server.respond_error ~status:`Bad_request ~body:"Bad request" ()
