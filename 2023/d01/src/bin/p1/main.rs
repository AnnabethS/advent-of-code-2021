use std::char;

fn proc_line(l: &str) -> u32 {
    let left_idx = l.find(|c:char| c.is_digit(10)).unwrap();
    let left = l.chars().nth(left_idx).unwrap().to_digit(10).unwrap();
    let right_idx = l.rfind(|c:char| c.is_digit(10)).unwrap();
    let right = l.chars().nth(right_idx).unwrap().to_digit(10).unwrap();
    return left*10 + right
}

fn main() {
    let input = include_str!("input.txt");
    // let input = include_str!("example.txt");
    let mut total = 0;
    for line in input.lines() {
        total += proc_line(line);
    }
    println!("total: {}", total);
}
