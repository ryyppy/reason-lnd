open Lwt
open Cohttp
open Cohttp_lwt_unix

let getPort =
  try
    int_of_string (Sys.getenv "PORT")
  with
  | Failure _ | Not_found -> 8000

let saveRoute =
  Server.respond_string ~status:`OK ~body:"/save route" ()

let loadRoute =
  Server.respond_string ~status:`OK ~body:"/load route" ()

let handleGet req =
  let path = req |> Request.uri |> Uri.path |> String.split_on_char '/' |> List.tl in
  match path with
  | [""] -> Server.respond_not_found ()
  | [name] -> (match name with
    | "save" -> saveRoute
    | "load" -> loadRoute
    | _ -> Server.respond_not_found ())
  | _ -> Server.respond_not_found ()

let server port =
  let callback _conn req body =
    let meth = (req |> Request.meth) in
    match meth with
    | `GET -> req |> handleGet
    | _ -> Server.respond_error ~status:`Method_not_allowed ~body:(Code.string_of_method meth) ()
   in
   Server.create ~mode:(`TCP (`Port port)) (Server.make ~callback ())

let () = ignore (Lwt_main.run (server getPort))

