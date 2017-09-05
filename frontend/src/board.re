open Game;

module Board = {
  include ReactRe.Component;
  type props = {rows: (row, row, row), handleSquareClick: (rowSelection, colSelection) => unit};
  let name = "Board";
  let renderRow row handleSquareClick rid => {
    let (c1, c2, c3) = row;
    <div key=(row_to_string rid)>
      <Square
        key=(row_to_string rid ^ "c1")
        value=c1
        handleClick=(fun _evt => handleSquareClick (rid, C1))
      />
      <Square
        key=(row_to_string rid ^ "c2")
        value=c2
        handleClick=(fun _evt => handleSquareClick (rid, C2))
      />
      <Square
        key=(row_to_string rid ^ "c3")
        value=c3
        handleClick=(fun _evt => handleSquareClick (rid, C3))
      />
    </div>
  };
  let render {props} => {
    let (r1, r2, r3) = props.rows;
    let {handleSquareClick} = props;
    <div>
      (renderRow r1 handleSquareClick R1)
      (renderRow r2 handleSquareClick R2)
      (renderRow r3 handleSquareClick R3)
    </div>
  };
};

include ReactRe.CreateComponent Board;

let createElement ::rows ::handleSquareClick => wrapProps {rows, handleSquareClick};
