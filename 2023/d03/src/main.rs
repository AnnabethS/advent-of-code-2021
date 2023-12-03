use std::fmt::{Display, Write};
use std::collections::HashSet;

#[derive(Clone, Copy)]
enum Cell{
    Digit(u32),
    Dot,
    Symbol(char),
    Gear,
}

impl Display for Cell {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Cell::Digit(d) => f.write_str(&format!("{}", d)),
            Cell::Dot => f.write_char('.'),
            Cell::Gear => f.write_char('*'),
            Cell::Symbol(s) => f.write_char(*s),
        }
    }
}

impl TryFrom<char> for Cell {
    type Error = String;

    fn try_from(value: char) -> Result<Self, Self::Error> {
        return match value {
            n@('0'..='9') => Ok(Self::Digit(n.to_digit(10).unwrap())),
            '.' => Ok(Self::Dot),
            '*' => Ok(Self::Gear),
            c => Ok(Self::Symbol(c)),
        }
    }

}

fn get_digit(data: &Vec<Vec<Cell>>, x: usize, y: usize) -> Option<u32> {
    if let Some(line) = data.get(y) {
        if let Some(c) = line.get(x) {
            if let Cell::Digit(x) = c{
                return Some(*x);
            }
        }
    }
    return None;
}

fn is_symbol(data: &Vec<Vec<Cell>>, x: usize, y: usize) -> bool {
    if let Some(line) = data.get(y) {
        if let Some(c) = line.get(x) {
            match c {
                Cell::Symbol(_) | Cell::Gear => return true,
                _ => return false
            }
        }
    }
    return false
}

fn is_gear(data: &Vec<Vec<Cell>>, x: usize, y: usize) -> bool {
    if let Some(line) = data.get(y) {
        if let Some(c) = line.get(x) {
            match c {
                Cell::Gear => return true,
                _ => return false
            }
        }
    }
    return false
}

fn get_neighbours(data: &Vec<Vec<Cell>>, x: usize, y: usize) -> HashSet<(usize, usize)> {
    let height = data.iter().count() as i32;
    let width = data.iter().nth(0).unwrap().len() as i32;
    let mut neighbours = HashSet::new();
    let valid_neighbours: Vec<(i32, i32)> = vec![
        (-1, -1), (-1, 0), (-1, 1),
        (0, -1), (0, 1),
        (1, -1), (1, 0), (1, 1),
    ];

    for (i, j) in valid_neighbours.iter() {
        let newx = i + x as i32;
        let newy = y as i32 + j;
        if newx >= 0 && newx < width {
            if newy >= 0 && newy < height {
                neighbours.insert((newx as usize, newy as usize));
            }
        }
    }
    return neighbours;
}

fn get_num(data: &Vec<Vec<Cell>>, x: usize, y: usize, visited: &mut HashSet<(usize, usize)>) -> u32 {
    let mut xi = x;
    while xi > 0 && get_digit(data, xi-1, y).is_some() {
        xi -= 1;
    }

    let mut digits = Vec::new();
    let mut ndigit = get_digit(data, xi, y);
    while ndigit.is_some() && !visited.contains(&(xi, y)) {
        visited.insert((xi, y));
        digits.push(ndigit.unwrap());
        xi += 1;
        ndigit = get_digit(data, xi, y);
    }

    return digits.into_iter().fold(0, |acc, n| acc*10 + n);
}

fn part_1(data: &Vec<Vec<Cell>>) -> u32 {
    let mut total = 0;
    let mut visited = HashSet::new();
    for (y, _) in data.iter().enumerate() {
        for (x, _) in data.iter().enumerate() {
            if get_digit(data, x, y).is_some() && ! visited.contains(&(x,y)) {
                visited.insert((x,y));
                let mut digits = vec![get_digit(data, x, y).unwrap()];
                let mut num_coords = HashSet::new();
                num_coords.insert((x, y));
                let mut x_i = x + 1;
                let mut next_digit = get_digit(data, x_i, y);
                while next_digit.is_some() {
                    visited.insert((x_i,y));
                    digits.push(next_digit.unwrap());
                    num_coords.insert((x_i, y));
                    x_i += 1;
                    next_digit = get_digit(data, x_i, y);
                }
                let has_symbol_neighbour = num_coords.iter()
                    .flat_map(|&(x, y)| get_neighbours(data, x, y))
                    .any(|(x, y)| is_symbol(data, x, y));
                if has_symbol_neighbour {
                    total += digits.into_iter().fold(0, |acc, n| acc*10 + n);
                }
            }
        }
    }

    return total;
}

fn part_2(data: &Vec<Vec<Cell>>) -> u32 {
    let mut total = 0;
    for y in 0..data.len() {
        for x in 0..data.iter().nth(0).unwrap().len() {
            if is_gear(data, x, y) {
                let neighbours = get_neighbours(data, x, y);
                let mut visited = HashSet::new();
                let mut num_neighbours = Vec::new();
                for (nx, ny) in neighbours.iter() {
                    if get_digit(data, *nx, *ny).is_some() && !visited.contains(&(*nx, *ny)) {
                        num_neighbours.push(get_num(data, *nx, *ny, &mut visited));
                    }
                }
                if num_neighbours.len() == 2 {
                    total += num_neighbours.iter().product::<u32>();
                }
            }
        }
    }
    return total;
}

fn main() {
    // let input = include_str!("example.txt");
    let input = include_str!("input.txt");
    let mut data: Vec<Vec<Cell>> = Vec::new();
    for line in input.lines() {
        let mut line_vec = Vec::new();
        for c in line.chars() {
            line_vec.push(Cell::try_from(c).expect("parse failure"));
        }
        data.push(line_vec);
    }
    println!("part 1: {}", part_1(&data));
    println!("part 2: {}", part_2(&data));
    // for line in data.iter() {
    //     for c in line.iter() {
    //         print!("{}", c);
    //     }
    //     print!("\n");
    // }
}
