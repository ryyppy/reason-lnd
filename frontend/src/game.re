type token =
  | Circle
  | Cross
  | Empty;

type playerState =
  | CirclePlayer
  | CrossPlayer;

type gameState =
  | Running
  | Win playerState
  | Draw;

type colSelection =
  | C1
  | C2
  | C3;

type rowSelection =
  | R1
  | R2
  | R3;

type row = (token, token, token);

let row_to_string rid =>
  switch rid {
  | R1 => "r1"
  | R2 => "r2"
  | R3 => "r3"
  };

let player_to_string player =>
  switch player {
  | CirclePlayer => "O"
  | CrossPlayer => "X"
  };

let playerToken player =>
  switch player {
  | CirclePlayer => Circle
  | CrossPlayer => Cross
  };

let switchPlayer (current: playerState) =>
  switch current {
  | CirclePlayer => CrossPlayer
  | CrossPlayer => CirclePlayer
  };

let isEmptyToken (square: token) =>
  switch square {
  | Empty => true
  | _ => false
  };

let updateColumn row column value => {
  let (t1, t2, t3) = row;
  switch column {
  | C1 => isEmptyToken t1 ? (value, t2, t3) : row
  | C2 => isEmptyToken t2 ? (t1, value, t3) : row
  | C3 => isEmptyToken t3 ? (t1, t2, value) : row
  }
};

let updateRow rows row column value => {
  let (r1, r2, r3) = rows;
  switch row {
  | R1 =>
    let r = updateColumn r1 column value;
    (r, r2, r3)
  | R2 =>
    let r = updateColumn r2 column value;
    (r1, r, r3)
  | R3 =>
    let r = updateColumn r3 column value;
    (r1, r2, r)
  }
};

let getToken rows rid cid => {
  let (r1, r2, r3) = rows;
  let fromRow (t1, t2, t3) cid =>
    switch cid {
    | C1 => t1
    | C2 => t2
    | C3 => t3
    };
  switch rid {
  | R1 => fromRow r1 cid
  | R2 => fromRow r2 cid
  | R3 => fromRow r3 cid
  }
};

let isValidTurn rows rid cid => getToken rows rid cid == Empty;

let isDraw rows => {
  let ((t1, t2, t3), (t4, t5, t6), (t7, t8, t9)) = rows;
  List.for_all (fun t => t != Empty) [t1, t2, t3, t4, t5, t6, t7, t8, t9]
};

let winOrDraw rows player => {
  let playerToken = playerToken player;
  let isFull (t1, t2, t3) => t1 == playerToken && t2 == playerToken && t3 == playerToken;
  let (r1, r2, r3) = rows;
  let ((t1, t2, t3), (t4, t5, t6), (t7, t8, t9)) = rows;
  let horizontal () => isFull r1 || isFull r2 || isFull r3;
  Js.log (isFull (t1, t5, t7));
  let vertical () => isFull (t1, t4, t7) || isFull (t2, t5, t8) || isFull (t3, t6, t9);
  let diagonal () => isFull (t1, t5, t9) || isFull (t3, t5, t7);
  if (horizontal () || vertical () || diagonal ()) {
    Win player
  } else if (isDraw rows) {
    Draw
  } else {
    Running
  }
};

let updateGame game rows player =>
  switch game {
  | Running => winOrDraw rows player
  | _ => game
  };
