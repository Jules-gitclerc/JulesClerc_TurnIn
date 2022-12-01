// main.rs
mod ex0;
use ex0::*;

fn main() {
   //tic_tac_toe();
   print_board(
      [(0, 0), (1, 1), (2, 1), (4, 4), (4, 4)],
      [(1, 0), (2, 2), (4, 4), (4, 4), (4, 4)],
   );
}