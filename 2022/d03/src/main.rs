use std::collections::HashMap;

#[derive(Debug)]
struct Backpack {
    c1: Vec<char>,
    c2: Vec<char>,
}

impl Backpack {
    fn new(line: &str) -> Self {
        let c_size = line.len() / 2;
        let (c1, c2) = line.split_at(c_size);
        if c1.len() != c2.len() {
            panic!("compartments not of equal length with line: {}", line)
        }
        let c1vec:Vec<char> = c1.chars().collect();
        let c2vec:Vec<char> = c2.chars().collect();
        Backpack { c1: c1vec, c2: c2vec }
    }

    fn shared(&self) -> Vec<char> {
        let mut output = Vec::new();
        for c in self.c1.iter() {
            if self.c2.contains(c) && ! output.contains(c) {
                output.push(*c);
            }
        }
        output
    }
}

fn part1(input: &str, prio: &HashMap<char, usize>) {
    let backpacks:Vec<Backpack> = input.split('\n').map(Backpack::new).collect();

    let shared:Vec<_> = backpacks.iter().map(Backpack::shared).collect();
    let part1: usize = shared.iter().flatten().map(|c| prio.get(c).unwrap()).sum();

    println!("part 1: {}", part1);
}

fn part2(input: &str, prio: &HashMap<char, usize>) {
    let lines:Vec<_> = input.split('\n').collect();
    let grps:Vec<_> = lines.chunks(3).collect();

    let mut badges = Vec::new();

    for grp in grps.iter() {
        for c in grp[0].chars() {
            if grp[1].contains(c) && grp[2].contains(c) {
                badges.push(c);
                break;
            }
        }
    }

    let score:usize = badges.iter().map(|b| prio.get(b).unwrap()).sum();

    println!("part 2: {}", score)
}


fn main() {
    // let input = include_str!("example.txt").trim();
    let input = include_str!("input.txt").trim();

    let mut prio = HashMap::new();
    for (i, v) in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".chars().enumerate() {
        prio.insert(v, i+1);
    }

    part1(input, &prio);

    part2(input, &prio);
}
