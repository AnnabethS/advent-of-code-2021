#[derive(Debug, PartialEq, Eq)]
enum Instruction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SELECT,
}

struct Keypad {
    max_dimensions: i32,
    position: (i32, i32),
    grid: Vec<Vec<i32>>,
}

impl Keypad {
    fn mv(&mut self, dir: &Instruction) {
        let newpos = (self.position.0 + match dir { // X
            Instruction::UP => 0,
            Instruction::DOWN => 0,
            Instruction::LEFT => -1,
            Instruction::RIGHT => 1,
            Instruction::SELECT => unreachable!("trying to move on a SELECT action"),
        },
        self.position.1 + match dir { // Y
            Instruction::UP => -1,
            Instruction::DOWN => 1,
            Instruction::LEFT => 0,
            Instruction::RIGHT => 0,
            Instruction::SELECT => unreachable!("trying to move on a SELECT action"),
        });

        if self.is_inbounds(newpos) {
            self.position = newpos;
        };
    }

    fn current_number(&self) -> i32 {
        let y = self.position.0 as usize;
        let x = self.position.1 as usize;
        self.grid.get(x).unwrap().get(y).unwrap().to_owned()
    }

    fn fmt_current_num(&self) -> String {
        fmt_code_num(self.current_number())
    }

    fn is_inbounds(&self, pos: (i32, i32)) -> bool {
        if pos.0 >= 0 && pos.0 < self.max_dimensions &&
           pos.1 >= 0 && pos.1 < self.max_dimensions {
            let y = pos.0 as usize;
            let x = pos.1 as usize;
            return self.grid.get(x).unwrap().get(y).unwrap().to_owned() != -1
        } else {
            return false
        }
    }
}

fn fmt_code_num(num: i32) -> String {
    if num == 10 {
        return "A".to_string();
    } else if num == 11 {
        return "B".to_string();
    } else if num == 12 {
        return "C".to_string();
    } else if num == 13 {
        return "D".to_string();
    } else {
        return num.to_string()
    }

}

fn parse_input(input_string: &String) -> Vec<Instruction> {
    let mut ins = Vec::new();
    for c in input_string.chars() {
        ins.push(match c {
            'U' => Instruction::UP,
            'D' => Instruction::DOWN,
            'L' => Instruction::LEFT,
            'R' => Instruction::RIGHT,
            '\n' => Instruction::SELECT,
            c => panic!("unknown char input -> {}", c)
        })
    }
    ins.push(Instruction::SELECT);
    ins
}

fn fmt_code(code: Vec<i32>) -> String {
    let mut outstr = String::new();
    for c in code.iter() {
        outstr.push_str(&fmt_code_num(*c));
    }
    outstr
}

fn main() {
    // let input = include_str!("example.txt");
    let input = include_str!("input.txt").trim();
    println!("puzzle input:\n{input}");

    let mut keypad_1 = Keypad {
        max_dimensions: 3,
        position: (1, 1),
        grid: vec!(vec!(1, 2, 3), vec!(4, 5, 6), vec!(7, 8, 9))
    };

    let instructions = parse_input(&input.to_string());
    // println!("{:?}", instructions);

    let mut code_1 = Vec::new();

    for ins in instructions.iter() {
        if *ins == Instruction::SELECT {
            code_1.push(keypad_1.current_number())
        } else {
            keypad_1.mv(ins);
        };
    }

    let mut code_2 = Vec::new();
    let mut keypad_2 = Keypad {
        max_dimensions: 5,
        position: (0, 2),
        grid: vec!(
            vec!(-1, -1,  1, -1, -1),
            vec!(-1,  2,  3,  4, -1),
            vec!( 5,  6,  7,  8,  9),
            vec!(-1, 10, 11, 12, -1),
            vec!(-1, -1, 13, -1, -1),

        )
    };

    for ins in instructions.iter() {
        if *ins == Instruction::SELECT {
            code_2.push(keypad_2.current_number());
            println!("selected: {}", keypad_2.fmt_current_num());
        } else {
            keypad_2.mv(ins);
            println!("post mv num: {}", keypad_2.fmt_current_num());
        };
    }

    println!("part 1 code: {:?}", fmt_code(code_1));
    println!("part 2 code: {:?}", fmt_code(code_2));
}
