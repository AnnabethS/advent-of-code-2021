fn proc_line(l: &str) -> u64 {
    let valid_slices = vec!["1", "2", "3", "4", "5", "6", "7", "8", "9",
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
    let mut leftmost = l.len();
    let mut leftmost_val:u64 = 0;
    let mut rightmost = 0;
    let mut rightmost_val:u64 = 0;
    for (i, slice) in valid_slices.iter().enumerate() {
        if let Some(idx) = l.find(slice) {
            if idx <= leftmost {
                leftmost = idx;
                leftmost_val = ((i as u64) % 9) + 1;
            }
        }
        if let Some(idx) = l.rfind(slice) {
            if idx >= rightmost {
                rightmost = idx;
                rightmost_val = ((i as u64) % 9) + 1;
            }
        }
    }
    return leftmost_val*10 + rightmost_val;
}

fn main() {
    let input = include_str!("input.txt");
    // let input = include_str!("example.txt");

    let total: u64 = input.lines().map(proc_line).sum();
    println!("total: {}", total);
}
