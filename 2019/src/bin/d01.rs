fn fuel_for_module_p1(mass: u64) -> u64 {
    return (mass / 3) - 2;
}

fn fuel_for_module_p2(mass: i64) -> i64 {
    let module_mass = (mass / 3) - 2;
    if module_mass <= 0 {
        return 0;
    }
    return module_mass + fuel_for_module_p2(module_mass);
}

fn parse_input(raw: String) -> Vec<u64> {
    return raw
        .lines()
        .map(|x| x.parse().unwrap())
        .collect();
}

fn part_1(modules: &Vec<u64>) -> u64 {
    return modules
        .iter()
        .map(|mass| fuel_for_module_p1(*mass))
        .sum();
}

fn part_2(modules: &Vec<u64>) -> u64 {
    return modules
        .iter()
        .map(|mass| fuel_for_module_p2(*mass as i64) as u64)
        .sum();
}

fn main() -> Result<(), std::io::Error> {
    let raw_input = std::fs::read_to_string("data/d01.txt")?;
    let parsed_input = parse_input(raw_input);

    let part_1_answer = part_1(&parsed_input);
    println!("part 1: {}", part_1_answer);

    let part_2_answer = part_2(&parsed_input);
    println!("part 2: {}", part_2_answer);

    return Ok(());
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn fuel_for_module_1_test() {
        assert_eq!(2, fuel_for_module_p1(12));
        assert_eq!(2, fuel_for_module_p1(14));
        assert_eq!(654, fuel_for_module_p1(1969));
        assert_eq!(33583, fuel_for_module_p1(100756));
    }

    #[test]
    fn fuel_for_module_2_test() {
        assert_eq!(2, fuel_for_module_p2(14));
        assert_eq!(966, fuel_for_module_p2(1969));
        assert_eq!(50346, fuel_for_module_p2(100756));
    }
}
