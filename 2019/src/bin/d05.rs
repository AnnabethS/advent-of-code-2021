use year_2019::IntCodeVM;

fn part_1(raw_code: &str) -> Option<i64> {
    let mut vm = IntCodeVM::builder(raw_code)
        .with_input_queue(vec![1].into())
        .build();
    vm.execute();
    return vm.get_last_output();
}

fn part_2(raw_code: &str) -> Option<i64> {
    let mut vm = IntCodeVM::builder(raw_code)
        .with_input_queue(vec![5].into())
        .build();
    vm.execute();
    return vm.get_last_output();
}

fn main() {
    let raw_code = std::fs::read_to_string("data/d05.txt").unwrap();
    let p1 = part_1(&raw_code).unwrap_or(-1);
    println!("part 1: {}", p1);

    let p2 = part_2(&raw_code).unwrap_or(-1);
    println!("part 2: {}", p2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part_1_functional() {
        let raw_code = std::fs::read_to_string("data/d05.txt").unwrap();
        assert_eq!(9938601, part_1(&raw_code).unwrap_or(-1));
    }

    #[test]
    fn part_2_functional() {
        let raw_code = std::fs::read_to_string("data/d05.txt").unwrap();
        assert_eq!(4283952, part_2(&raw_code).unwrap_or(-1));
    }
}
