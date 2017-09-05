open Game;

let test1 () => {
  Js.log "Should match X diagonally";
  let rows = ((Cross, Empty, Empty), (Empty, Cross, Empty), (Empty, Empty, Cross));
  let ret = winOrDraw rows CrossPlayer;
  assert (ret == Win CrossPlayer)
};

test1 ();
