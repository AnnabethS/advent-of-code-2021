enum Command {
    Mul(i64, i64),
    Do,
    Dont
}

fn part1(raw_data: &str) -> i64 {
    let re = regex::Regex::new(r"mul\((\d+),(\d+)\)").expect("could not compile part 1 regex");
    return re
        .captures_iter(raw_data)
        .map(|capture| (capture[1].parse::<i64>().unwrap(), capture[2].parse::<i64>().unwrap()))
        .fold(0, |acc, (a, b)| acc + (a * b));
}

fn part2(raw_data: &str) -> i64 {
    let re = regex::Regex::new(r"(mul\((\d+),(\d+)\))|(don't\(\))|(do\(\))").expect("could not compile part 2 regex");
    let commands = re
        .captures_iter(raw_data)
        .map(|capture| {
            if capture[0].starts_with("mul") {
                Command::Mul(capture[2].parse::<i64>().unwrap(), capture[3].parse::<i64>().unwrap())
            } else if capture[0].starts_with("don't") {
                Command::Dont
            } else if capture[0].starts_with("do") {
                Command::Do
            } else {
                panic!("unrecognised match from regex");
            }});

    let mut enabled = true;
    let mut total = 0;
    for com in commands {
        match com {
            Command::Mul(a, b) => if enabled { total += a * b },
            Command::Do => enabled = true,
            Command::Dont => enabled = false,
        }
    }

    return total;
}

fn main() {
    let raw_data = std::fs::read_to_string("data/d03.txt").unwrap();
    let p1 = part1(&raw_data);
    println!("part 1: {}", p1);

    let p2 = part2(&raw_data);
    println!("part 2: {}", p2);
}
