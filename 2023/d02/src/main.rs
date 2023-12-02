const RED_LIMIT:u32 = 12;
const GREEN_LIMIT:u32 = 13;
const BLUE_LIMIT:u32 = 14;

fn part_1(input: &str) -> u32 {
    let mut possible_games = 0;
    'game: for (game_id, line) in input.lines().enumerate() {
        let data = line.split_once(':').unwrap().1;
        let sets = data.split(';');
        let mut max_red = 0;
        let mut max_green = 0;
        let mut max_blue = 0;
        for set in sets {
            for reveal in set.split(',') {
                let (num, col) = reveal[1..].split_once(' ').unwrap();
                let num:u32 = num.parse().unwrap();
                match col.chars().nth(0).unwrap() {
                    'r' => max_red = num.max(max_red),
                    'b' => max_blue = num.max(max_blue),
                    'g' => max_green = num.max(max_green),
                    _ => unreachable!()
                }
                if max_red > RED_LIMIT  || max_green > GREEN_LIMIT || max_blue > BLUE_LIMIT {
                    continue 'game;
                }
            }
        }
        possible_games += (game_id as u32) + 1;
    }
    return possible_games;
}

fn part_2(input: &str) -> u32 {
    let mut power_sum = 0;
    for line in input.lines() {
        let data = line.split_once(':').unwrap().1;
        let sets = data.split(';');
        let mut max_red = 0;
        let mut max_green = 0;
        let mut max_blue = 0;
        for set in sets {
            for reveal in set.split(',') {
                let (num, col) = reveal[1..].split_once(' ').unwrap();
                let num:u32 = num.parse().unwrap();
                match col.chars().nth(0).unwrap() {
                    'r' => max_red = num.max(max_red),
                    'b' => max_blue = num.max(max_blue),
                    'g' => max_green = num.max(max_green),
                    _ => unreachable!()
                }
            }
        }
        power_sum += max_red * max_blue * max_green;
    }
    return power_sum;
}

fn main() {
    // let input = include_str!("example.txt");
    let input = include_str!("input.txt");
    let repeats = 50;
    println!("part 1: {}", part_1(input));
    let start = std::time::Instant::now();
    for _i in 0..repeats {
        part_1(input);
    }
    println!("Done in {:?}", start.elapsed() / repeats);

    println!("part 2: {}", part_2(input));
    let start = std::time::Instant::now();
    for _i in 0..(repeats-1) {
        part_2(input);
    }
    println!("Done in {:?}", start.elapsed() / repeats);
}
