#[derive(Debug)]
struct Elf {
    low: u32,
    high: u32,
}

impl Elf {
    fn new(s: &str) -> Elf {
        let (low, high) = s.split_once('-').unwrap();
        Elf {
            low: low.parse().unwrap(),
            high: high.parse().unwrap(),
        }
    }
}

fn parseline(s: &str) -> (Elf, Elf) {
    let (s1, s2) = s.split_once(',').unwrap();
    (Elf::new(s1), Elf::new(s2))
}

fn total_overlap((e1, e2): &(Elf, Elf)) -> bool {
    (e1.low >= e2.low && e1.high <= e2.high)  ||
    (e2.low >= e1.low && e2.high <= e1.high)
}

fn overlap((e1, e2): &(Elf, Elf)) -> bool {
    between(e1.low, e2) || between(e1.high, e2) ||
    between(e2.low, e1) || between(e2.high, e1)
}

fn between(x: u32, e: &Elf) -> bool {
    x >= e.low && x <= e.high
}

fn main() {
    let input = include_str!("input.txt");
    // let input = include_str!("example.txt");

    let elf_pairs:Vec<_> = input.lines().map(parseline).collect();

    let mut total_overlaps = 0;
    let mut overlaps = 0;
    for pair in elf_pairs.iter() {
        if total_overlap(pair) {
            total_overlaps += 1;
        }
        if overlap(pair) {
            overlaps += 1;
        }
    }

    println!("part 1: {}", total_overlaps);
    println!("part 2: {}", overlaps);
}
