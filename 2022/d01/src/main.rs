fn main() {
    let input = include_str!("input.txt");
    // let input = include_str!("example.txt");

    let lines:Vec<_> = input.split('\n').collect();

    let elves:Vec<_> = lines
        .split(|s| s.is_empty())
        .map(|s|s
            .iter()
            .map(|x| x.parse::<u64>().unwrap())
            .collect::<Vec<u64>>())
        .collect();

    let mut elf_totals:Vec<_> = elves.clone().iter().map(|elf| elf.iter().fold(0, |a, b| a + b)).collect();

    let mut max_cal = 0;
    for e in elf_totals.iter() {
        if  *e > max_cal {
            max_cal = *e;
        }
    }

    println!("part 1: {}", max_cal);

    elf_totals.sort();
    elf_totals.reverse();

    let top3:u64 = elf_totals[0..=2].iter().sum();

    println!("part 2: {}", top3);
}
