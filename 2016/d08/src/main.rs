const SCREEN_WIDTH:usize = 50;
const SCREEN_HEIGHT:usize = 6;

trait Instruction: std::fmt::Debug {
    fn exec(&self, screen: &mut Screen);
}

#[derive(Debug)]
struct RectI {
    x: usize,
    y: usize,
}

impl Instruction for RectI {
    fn exec(&self, screen: &mut Screen) {
        for y in 0..self.y {
            for x in 0..self.x {
                screen.data[(SCREEN_WIDTH * y) + x] = true;
            }
        }
    }
}

#[derive(Debug)]
struct RotateRowI {
    row: u32,
    amount: u32,
}

impl Instruction for RotateRowI {
    fn exec(&self, screen: &mut Screen) {
        let old_row = screen.data[
            (idx(0, self.row as usize))..=(idx(SCREEN_WIDTH-1, self.row as usize))].to_vec();
        let (v1, v2) = old_row.split_at(SCREEN_WIDTH - (self.amount as usize % SCREEN_WIDTH));
        let new_row = [v2, v1].concat();
        for (row_i, screen_i) in ((idx(0, self.row as usize))..=(idx(SCREEN_WIDTH-1, self.row as usize))).enumerate() {
            screen.data[screen_i] = new_row[row_i];
        }
    }
}

#[derive(Debug)]
struct RotateColI {
    column: u32,
    amount: u32,
}

impl Instruction for RotateColI {
    fn exec(&self, screen: &mut Screen) {
        let mut old_col = [false; SCREEN_HEIGHT];
        for row in 0..SCREEN_HEIGHT {
            old_col[row] = screen.data[idx(self.column as usize, row)];
        }
        let (v1, v2) = old_col.split_at(SCREEN_HEIGHT - (self.amount as usize % SCREEN_HEIGHT));
        let new_col = [v2, v1].concat();
        for i in 0..SCREEN_HEIGHT {
            screen.data[idx(self.column as usize, i)] = new_col[i];
        }
    }
}

struct Screen {
    data: [bool; SCREEN_WIDTH*SCREEN_HEIGHT],
}

impl std::fmt::Display for Screen {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let mut out = String::new();
        for y in 0..SCREEN_HEIGHT {
            for x in 0..SCREEN_WIDTH {
                if self.data[y*SCREEN_WIDTH + x] {
                    out.push('#');
                }
                else {
                    out.push('.')
                }
            }
            out.push('\n');
        }
        f.write_str(out.as_str())
    }
}

impl Screen {
    fn blank() -> Screen {
        Screen {
            data: [false; SCREEN_WIDTH * SCREEN_HEIGHT]
        }
    }

    fn count_lit(&self) -> usize {
        self.data.iter().filter(|x| **x).count()
    }
}

fn idx(x: usize, y: usize) -> usize {
    x + (y * SCREEN_WIDTH)
}

fn parse_line(s: &str) -> Box<dyn Instruction> {
    let words:Vec<&str> = s.split_whitespace().collect();

    return match words[0] {
        "rect" => {
            let coords:Vec<_> = words[1].split('x').collect();
            let x:usize = coords[0].parse().unwrap();
            let y:usize = coords[1].parse().unwrap();
            Box::new(RectI { x, y })
        },
        "rotate" => {
            let idx:u32 = words[2][2..].parse().unwrap();
            let amount:u32 = words[4].parse().unwrap();
            match words[1] {
                "column" => Box::new(RotateColI{column: idx, amount}),
                "row" => Box::new(RotateRowI{row: idx, amount}),
                _ => unreachable!("unknown rotate instruction: {}", s),
            }
        },
        _ => unreachable!("unknown instruction: {}", s),
    }
}

fn main() {
    // let input = include_str!("example.txt").trim();
    let input = include_str!("input.txt").trim();

    let instructions:Vec<_> = input.lines().map(parse_line).collect();

    let mut screen = Screen::blank();

    for ins in instructions.iter() {
        ins.exec(&mut screen);
        println!("screen after instruction:\n{}", screen);
    }

    println!("lit pixels: {}", screen.count_lit());
}
