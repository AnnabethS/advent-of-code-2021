#[derive(Debug)]
struct Instruction {
    from_idx: usize,
    to_idx: usize,
    amount: usize,
}

impl Instruction {
    fn new(s: &str) -> Self {
        let splits:Vec<_> = s.split(' ').collect();
        Self {
            from_idx: splits[3].parse::<usize>().unwrap() - 1,
            to_idx: splits[5].parse::<usize>().unwrap() - 1,
            amount: splits[1].parse().unwrap()
        }
    }
}

fn main() {
    let mut crates = [
        vec!('B', 'G', 'S', 'C'),
        vec!('T', 'M', 'W', 'H', 'J', 'N', 'V', 'G'),
        vec!('M', 'Q', 'S'),
        vec!('B', 'S', 'L', 'T', 'W', 'N', 'M'),
        vec!('J', 'Z', 'F', 'T', 'V', 'G', 'W', 'P'),
        vec!('C', 'T', 'B', 'G', 'Q', 'H', 'S'),
        vec!('T', 'J', 'P', 'B', 'W'),
        vec!('G', 'D', 'C', 'Z', 'F', 'T', 'Q', 'M'),
        vec!('N', 'S', 'H', 'B', 'P', 'F')
    ];

    // let mut crates = [
    //     vec!('Z', 'N'),
    //     vec!('M', 'C', 'D'),
    //     vec!('P')
    // ];
    // let input = include_str!("example.txt").trim();
    let mut crates2 = crates.clone();

    let input = include_str!("input.txt").trim();
    let instructions:Vec<_> = input.lines().map(Instruction::new).collect();

    for ins in instructions.iter() {
        for i in 0..ins.amount {
            if crates[ins.from_idx].len() > 0 {
                let c = crates[ins.from_idx].pop().unwrap();
                crates[ins.to_idx].push(c);
            }
            else {
                unreachable!("tried to move a crate that isnt there");
            }
        }
    }

    for ins in instructions.iter() {
        let mut stack = crates2[ins.from_idx].split_off(crates2[ins.from_idx].len() - ins.amount);
        crates2[ins.to_idx].append(&mut stack);
    }

    println!("{:#?}", crates2);

    let mut part_1 = String::new();
    let mut part_2 = String::new();

    for i in crates.iter() {
        part_1.push(*i.last().unwrap());
    }

    for i in crates2.iter() {
        part_2.push(*i.last().unwrap());
    }
    println!("part 1: {}", part_1);
    println!("part 2: {}", part_2);
}
