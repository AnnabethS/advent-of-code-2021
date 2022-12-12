use core::str::FromStr;

#[derive(Debug)]
enum Instruction {
    NOOP(),
    ADDX(i32),
}
impl FromStr for Instruction {
    type Err = ();

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        if s == "noop" {
            return Ok(Self::NOOP());
        } else {
            let (_, amnt) = s.split_once(' ').unwrap();
            return Ok(Self::ADDX(amnt.parse().unwrap()));
        }
    }
}

fn main() {
    // let input = include_str!("example.txt").trim();
    let input = include_str!("input.txt").trim();

    let instructions:Vec<Instruction> = input.lines().map(|line| line.parse().unwrap()).collect();

    let mut acc = 1;
    let mut cycle_values:Vec<i32> = Vec::new();

    for ins in instructions.iter() {
        match ins {
            Instruction::NOOP() => cycle_values.push(acc),
            Instruction::ADDX(x) => {
                cycle_values.push(acc);
                cycle_values.push(acc);
                acc += x;
            },
        }
    }

    let check_cycles = vec![20, 60, 100, 140, 180, 220];
    let part_1:i32 = check_cycles.iter()
        .map(|i| (i, cycle_values.get(*i - 1).unwrap()))
        .map(|(cycle, acc)| (*cycle as i32) * *acc)
        .sum();

    println!("part 1: {}", part_1);


    let mut crt = String::new();
    for (i, v) in cycle_values.iter().enumerate() {
        let xpos = (i % 40) as i32;
        if xpos.abs_diff(*v) <= 1 {
            crt.push('\u{2588}');
        } else {
            crt.push(' ');
        }

        if i != 0 && (i + 1) % 40 == 0 {
            crt.push('\n');
        }
    }

    println!("part 2:\n{crt}");
}
