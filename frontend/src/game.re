type token =
  | Circle
  | Cross
  | Empty;

type player =
  | CirclePlayer
  | CrossPlayer;

type progress =
  | Turn player
  | Win player
  | Draw;

type colId =
  | C1
  | C2
  | C3;

type rowId =
  | R1
  | R2
  | R3;

type row = (token, token, token);

type selection = (rowId, colId);

type ticTacToeState = {
  board: (row, row, row),
  progress
};

let initialState () => {
  board: ((Empty, Empty, Empty), (Empty, Empty, Empty), (Empty, Empty, Empty)),
  progress: Turn CirclePlayer
};

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

let switchPlayer (current: player) =>
  switch current {
  | CirclePlayer => CrossPlayer
  | CrossPlayer => CirclePlayer
  };

let isEmptyToken (square: token) =>
  switch square {
  | Empty => true
  | _ => false
  };

let updateColumn rid cid value => {
  let (t1, t2, t3) = rid;
  switch cid {
  | C1 => isEmptyToken t1 ? (value, t2, t3) : rid
  | C2 => isEmptyToken t2 ? (t1, value, t3) : rid
  | C3 => isEmptyToken t3 ? (t1, t2, value) : rid
  }
};

let updateRow board rid cid value => {
  let (r1, r2, r3) = board;
  switch rid {
  | R1 =>
    let r = updateColumn r1 cid value;
    (r, r2, r3)
  | R2 =>
    let r = updateColumn r2 cid value;
    (r1, r, r3)
  | R3 =>
    let r = updateColumn r3 cid value;
    (r1, r2, r)
  }
};

let getToken board rid cid => {
  let (r1, r2, r3) = board;
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

let isCellEmpty board rid cid => getToken board rid cid == Empty;

let isDraw board => {
  let ((t1, t2, t3), (t4, t5, t6), (t7, t8, t9)) = board;
  List.for_all (fun t => t != Empty) [t1, t2, t3, t4, t5, t6, t7, t8, t9]
};

let processTurn (state: ticTacToeState) (select: selection) player => {
  let (rid, cid) = select;

  if (isCellEmpty state.board rid cid) {
    let board = updateRow state.board rid cid (playerToken player);
    let progress = {
      let playerToken = playerToken player;
      let isFull (t1, t2, t3) => t1 == playerToken && t2 == playerToken && t3 == playerToken;
      let (r1, r2, r3) = board;
      let ((t1, t2, t3), (t4, t5, t6), (t7, t8, t9)) = board;
      let horizontal () => isFull r1 || isFull r2 || isFull r3;
      let vertical () => isFull (t1, t4, t7) || isFull (t2, t5, t8) || isFull (t3, t6, t9);
      let diagonal () => isFull (t1, t5, t9) || isFull (t3, t5, t7);
      if (horizontal () || vertical () || diagonal ()) {
        Win player
      } else if (isDraw board) {
        Draw
      } else {
        Turn (switchPlayer player)
      }
    };
    {board, progress}
  } else {
    state
  }
};

let playTurn state select =>
  switch state.progress {
  | Turn player => processTurn state select player
  | _ => state
  };
