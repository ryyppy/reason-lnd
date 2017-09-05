open Lwt
open Cohttp
open Cohttp_lwt_unix

let getPort =
  try
    int_of_string (Sys.getenv "PORT")
  with
  | Failure _ | Not_found -> 8000

(* Retrieves the last portion of a path e.g. some:8000/user -> user *)
let retrievePath req =
  let path = req
             |> Request.uri
             |> Uri.path
             |> String.split_on_char '/'
             |> List.tl in
  match path with
    | [name] -> Some name
    | _ -> None

let handleGet req =
  match retrievePath req with
  | Some p -> (match p with
    | "load" -> Routes.loadRoute
    | _ -> Server.respond_not_found ())
  | _ -> Server.respond_not_found ()

let handlePost req =
  match retrievePath req with
  | Some p -> (match p with
    | "save" -> Routes.saveRoute
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

