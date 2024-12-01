fn part1(l_list: &Vec<i64>, r_list: &Vec<i64>) -> i64 {
    let mut l_list_sorted = l_list.clone();
    l_list_sorted.sort();
    let mut r_list_sorted = r_list.clone();
    r_list_sorted.sort();

    return l_list_sorted.iter().zip(r_list_sorted.iter())
        .map(|(l, r)| l.abs_diff(*r) as i64)
        .sum();
}

fn part2(l_list: &Vec<i64>, r_list: &Vec<i64>) -> i64 {
    return l_list.iter()
        .map(|l| l * r_list.iter().filter(|r| l == *r).count() as i64)
        .sum();
}

fn main() {
    let raw_data = std::fs::read_to_string("data/d01.txt").expect("could not read d01.txt from data directory");
    let (l_list, r_list): (Vec<i64>, Vec<i64>) = raw_data.lines()
        .map(|line| line.split_whitespace().collect::<Vec<_>>())
        .map(|vec| (vec[0].parse::<i64>().unwrap(), vec[1].parse::<i64>().unwrap()))
        .unzip();
    let p1 = part1(&l_list, &r_list);
    println!("part 1: {}", p1);

    let p2 = part2(&l_list, &r_list);
    println!("part 2: {}", p2);
}
