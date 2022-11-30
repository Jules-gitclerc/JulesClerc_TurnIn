#![allow(unused)]
use std::io::stdin;

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