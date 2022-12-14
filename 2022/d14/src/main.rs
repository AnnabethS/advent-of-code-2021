use std::{collections::HashMap, str::FromStr};

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
struct Point {
    x: usize,
    y: usize,
}

impl FromStr for Point {
    type Err = ();

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let (x, y) = s.split_once(',').unwrap();
        return Ok(Point { x: x.parse().unwrap(), y: y.parse().unwrap() })
    }
}

#[derive(PartialEq, Eq)]
enum Tile {
    AIR,
    RCK,
    SND,
}

impl std::fmt::Display for Tile {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Tile::AIR => write!(f, "."),
            Tile::RCK => write!(f, "#"),
            Tile::SND => write!(f, "o"),
        }
    }
}

fn print_grid(grid: &HashMap<Point, Tile>) {
    let min_y = 0;
    let max_y = grid.keys().max_by(|x, y| x.y.cmp(&y.y)).unwrap().y + 1;

    let max_x = grid.keys().max_by(|x, y| x.x.cmp(&y.x)).unwrap().x;
    let min_x = grid.keys().min_by(|x, y| x.x.cmp(&y.x)).unwrap().x;

    // println!("{min_y}, {max_y}, {min_x}, {max_x}");

    let mut s = String::new();

    for y in min_y..=max_y {
        for x in min_x..=max_x {
            s.push_str(&format!("{}", grid.get(&Point{x, y}).unwrap_or(&Tile::AIR)));
        }
        s.push('\n');
    }

    println!("{s}");

}

fn parse_line(s: &str) -> Vec<(Point, Point)> {
    let points:Vec<_> = s.split("->").map(|s| s.trim()).collect();
    let mut pairs = Vec::new();
    for i in 0..points.len()-1 {
        pairs.push((points[i].parse().unwrap(),points[i+1].parse().unwrap()));
    }

    return pairs
}

// true if sand falls into abyss
fn drop_sand(grid: &mut HashMap<Point, Tile>) -> bool {
    let mut sand = Point { x: 500, y: 0 };
    let mut new_pos = tick_sand(&grid, sand);
    let max_y = grid.keys().max_by(|x, y| x.y.cmp(&y.y)).unwrap().y + 1;

    while new_pos.is_some() {
        if new_pos.unwrap().y > max_y {
            return true
        }

        sand = new_pos.unwrap();
        new_pos = tick_sand(&grid, sand);
    }

    grid.insert(sand, Tile::SND);

    return false
}

fn tick_sand(grid: &HashMap<Point, Tile>, pos: Point) -> Option<Point> {
    match grid.get(&Point { x: pos.x, y: pos.y+1 }).unwrap_or(&Tile::AIR) {
        Tile::AIR => return Some(Point {x: pos.x, y: pos.y+1}),
        _ => (),
    }

    match grid.get(&Point { x: pos.x-1, y: pos.y+1 }).unwrap_or(&Tile::AIR) {
        Tile::AIR => return Some(Point {x: pos.x-1, y: pos.y+1}),
        _ => (),
    }

    match grid.get(&Point { x: pos.x+1, y: pos.y+1 }).unwrap_or(&Tile::AIR) {
        Tile::AIR => return Some(Point {x: pos.x+1, y: pos.y+1}),
        _ => return None,
    }

}

fn main() {
    // let input = include_str!("example.txt");
    let input = include_str!("input.txt");

    let mut pairs = Vec::new();

    for line in input.lines() {
        pairs.append(&mut parse_line(line));
    }
    println!("{:?}", pairs);

    let mut grid: HashMap<Point, Tile> = HashMap::new();

    for pair in pairs{
        if pair.0.x == pair.1.x {
            // vertical line
            let min = pair.0.y.min(pair.1.y);
            let max = pair.0.y.max(pair.1.y);
            for y in min..=max {
                grid.insert(Point {x: pair.0.x, y}, Tile::RCK);
            }
        } else if pair.0.y == pair.1.y {
            // horizontal line
            let min = pair.0.x.min(pair.1.x);
            let max = pair.0.x.max(pair.1.x);
            for x in min..=max {
                grid.insert(Point { x, y: pair.0.y }, Tile::RCK);
            }
        } else {
            unreachable!("diagonal pair")
        }
    }

    print_grid(&grid);

    let mut part_1 = 0;

    while ! drop_sand(&mut grid) {
        part_1 += 1;
    }

    print_grid(&grid);

    println!("part 1: {}", part_1);
}
