open Cohttp
open Cohttp_lwt_unix
open State

(* OH! what is this? Mutable global state? Gee, we all gonna die~~ *)
let currentState: (state option) ref = ref None;;

let saveRoute =
  Server.respond_string ~status:`OK ~body:"/save route" ()

let loadRoute =
  match !currentState with
  | Some s -> Server.respond_string ~status:`OK ~body:(Convert.stateToString s) ()
  | None -> Server.respond_error ~status:`Bad_request ~body:"Bad request" ()
