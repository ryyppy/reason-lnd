open Opium.Std

let getPort =
  try int_of_string (Sys.getenv "PORT") with | Failure _ | Not_found -> 8000

let headers =
  Cohttp.Header.init_with "Content-Type" "application/json"

let status_route =
  get "/status"
  (fun req -> `String "Hi, I am up and running!" |> respond')

let load_route =
  get "/load"
  (fun req -> `String (State.serializeState !State.currentState) |> respond' ~headers)

let staticPublic =
  Middleware.static
    ~local_path:"../frontend/public"
    ~uri_prefix:"/public"

let staticJsAssets =
  Middleware.static
    ~local_path:"../frontend/bundledOutputs"
    ~uri_prefix:"/public"

let _ =
  let port = getPort in
  let app = App.empty
  |> App.port port
  |> middleware staticPublic
  |> middleware staticJsAssets
  |> status_route
  |> load_route
  |> App.run_command' in
  match app with
  | `Ok a ->
      print_endline ("Server is running on port " ^ (string_of_int port));
      Lwt_main.run a
  | `Error ->
      print_endline "Server could not be started";
      exit 1
  | `Not_running -> exit 0

