#![allow(unused)]
use std::io::stdin;
use rand::Rng;

pub fn fahrenheit_celsius_converter(temperature: i32, f2c: bool) -> f32 {
    if f2c {
        (temperature as f32 - 32.0) * 5.0 / 9.0
    } else {
        temperature as f32 * 9.0 / 5.0 + 32.0
    }
}

pub fn dice_roll(sides: u8) -> u8 {
    use rand::Rng;
    rand::thread_rng().gen_range(1, sides + 1)
}

pub fn multi_string(s: String) -> [String; 4] {
    let mut arr = [s, String::new(), String::new(), String::new()];
    for i in 1..4 {
        arr[i] = format!("{}{}", arr[0], if i == 1 { "ONE" } else if i == 2 { "TWO" } else if i == 3 { "THREE" } else { "FOUR" });
    }
    arr
}

pub fn add_vowels(s: &mut String) {
    let mut i = 0;
    while i < s.len() {
        if s.chars().nth(i).unwrap() == 'a' || s.chars().nth(i).unwrap() == 'e' || s.chars().nth(i).unwrap() == 'i' || s.chars().nth(i).unwrap() == 'o' || s.chars().nth(i).unwrap() == 'u' {
            s.insert(i, s.chars().nth(i).unwrap());
            i += 2;
        } else if s.chars().nth(i).unwrap() == 'A' || s.chars().nth(i).unwrap() == 'E' || s.chars().nth(i).unwrap() == 'I' || s.chars().nth(i).unwrap() == 'O' || s.chars().nth(i).unwrap() == 'U' {
            s.insert(i, s.chars().nth(i).unwrap());
            i += 2;
        }
        else {
            i += 1;
        }
    }
}

pub fn echo_split(whole: String, num: u32) {
    let half = whole.len() / 2;
    let (first, second) = whole.split_at(half);
    for _ in 0..num {
        print!("{}", first);
    }
    print!(" ");
    for _ in 0..num {
        print!("{}", second);
    }
    println!();
}

pub fn input_number(high: u32) -> Option<u32> {
    let mut input = String::new();
    stdin().read_line(&mut input).unwrap();
    let num = input.trim().parse::<u32>();
    match num {
        Ok(n) => if n < high { Some(n) } else { None },
        Err(_) => None,
    }
}

// enum Card {
//     Diamond(String),
//     Club(String),
//     Heart(String),
//     Spade(String)
// }
// pub fn draw_card() -> Card {
//     let mut rng = rand::thread_rng();
//     let suit = rng.gen_range(0, 4);
//     let card = rng.gen_range(1, 14);
//     let binding = card.to_string();
//     let card = match card {
//         1 => "Ace",
//         11 => "Jack",
//         12 => "Queen",
//         13 => "King",
//         _ => &binding,
//     };
//     match suit {
//         0 => Card::Diamond(card.to_string()),
//         1 => Card::Heart(card.to_string()),
//         2 => Card::Spade(card.to_string()),
//         3 => Card::Club(card.to_string()),
//         _ => Card::Diamond(card.to_string()),
//     }
// }
/*Takes in input from the user. It takes 2 Strings from the user and parses them into u8s. Those u8s are then returned as a tuple. This Tuple represents coordinates in a square field of with sides the length of side. The coordinates of the square are from 0 – size. So if the user inputs a number equal to or greater than size it is considered out of bounds.
You must handle all errors and edge cases that might occur. If the user inputs something that is not a number or the number they input is out of bounds. The function continues until the user has successfully inputs 2 numbers or there is an error with input, in which case an invalid tuple (size, size) is passed back.*/
pub fn input_coord(size: u8) -> (u8, u8){
    let mut x = 0;
    let mut y = 0;
    let mut input = String::new();
    let mut input2 = String::new();
    let mut valid = false;
    while !valid {
        println!("enter coordinate for {} x {}:", size, size);
        stdin().read_line(&mut input).unwrap();
        let num = input.trim().parse::<u8>();
        let value = input.trim();
        match num {
            Ok(n) => if n < size { x = n; valid = true; } else { println!("{} is is out of bounds on a board of size {}", n, size); },
            Err(_) => println!("\"{}\" is not a number, error: invalid digit found in string", value),
        }
    }
    valid = false;
    while !valid {
        println!("enter coordinate for {} x {}:", size, size);
        stdin().read_line(&mut input2).unwrap();
        let num = input2.trim().parse::<u8>();
        let value = input2.trim();
        match num {
            Ok(n) => if n < size { x = n; valid = true; } else { println!("{} is is out of bounds on a board of size {}", n, size); },
            Err(_) => println!("\"{}\" is not a number, error: invalid digit found in string", value),
        }
    }
    (x, y)
}

pub fn print_board(exes:[(u8, u8);5], oes: [(u8, u8);5]) {
    let mut board = [['-'; 5]; 5];
    for i in (0..3).rev() {
        board[exes[i].0 as usize][exes[i].1 as usize] = 'X';
        board[oes[i].0 as usize][oes[i].1 as usize] = 'O';
    }
    for i in (0..3).rev() {
        for j in (0..3).rev() {
            print!("{} ", board[i][j]);
        }
        println!();
    }
}

pub fn tic_tac_toe() {
    let mut board = [['-'; 3]; 3];
    let mut turn = 0;
    let mut x = 0;
    let mut y = 0;
    let mut player = 'X';
    println!("TIC-TAC-TOE");
    println!("-----");
    for i in (0..3).rev() {
        for j in 0..3 {
            print!("{} ", board[i][j]);
        }
        println!();
    }
    println!("-----");
    while turn < 9 {
        println!("{} turn", player);
        println!("Enter y coordinate for 3 x 3:");
        y = input_number(3).unwrap();
        println!("Enter x coordinate for 3 x 3:");
        x = input_number(3).unwrap();
        if board[x as usize][y as usize] == '-' {
            board[x as usize][y as usize] = player;
            turn += 1;
            if player == 'X' {
                player = 'O';
            } else {
                player = 'X';
            }
        } else {
            println!("That spot is already taken");
        }
        println!("-----");
        for i in (0..3).rev() {
            for j in 0..3 {
                print!("{} ", board[i][j]);
            }
            println!();
        }
        println!("-----");
        for i in 0..3 {
            if board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '-' {
                println!("{} wins!", board[i][0]);
                return;
            }
            if board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '-' {
                println!("{} wins!", board[0][i]);
                return;
            }
        }
        if turn == 9 {
            println!("tie game");
        }
    }
}