use year_2019::IntCodeVM;

fn part1(raw: &str) -> i64 {
    let mut vm = IntCodeVM::builder(raw)
        .set_mem_pos(1, 12)
        .set_mem_pos(2, 2)
        .build();
    vm.execute();
    return vm.get_int_at(0);
}

fn part2(raw: &str) -> i64 {
    for noun in 0..=99 {
        for verb in 0..=99 {
            let mut vm = IntCodeVM::builder(raw)
                .set_mem_pos(1, noun)
                .set_mem_pos(2, verb)
                .build();
            vm.execute();
            if vm.get_int_at(0) == 19690720 {
                return (100 * noun) + verb;
            }
        }
    }
    panic!("value not found.");
}

fn main() -> Result<(), std::io::Error> {
    let raw_input = std::fs::read_to_string("data/d02.txt")?;
    let part_1 = part1(&raw_input);
    println!("part 1: {}", part_1);

    let part_2 = part2(&raw_input);
    println!("part 2: {}", part_2);

    return Ok(());
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part1_functional() {
        let raw_input = std::fs::read_to_string("data/d02.txt").unwrap();
        assert_eq!(3224742, part1(&raw_input));
    }

    #[test]
    fn part2_functional() {
        let raw_input = std::fs::read_to_string("data/d02.txt").unwrap();
        assert_eq!(7960, part2(&raw_input));
    }
}
