struct Race {
    time: u64,
    distance: u64,
}

impl Race {
    fn win_counts(&self) -> u64 {
        let mut total = 0;
        for i in 1..self.time {
            if i * (self.time - i) > self.distance {
                total += 1;
            }
        }

        return total;
    }
}

fn part_1(input: &str) -> u64 {
    let (times, distances) = input.split_once('\n').unwrap();

    let times = times.split_once(':').unwrap().1.split_whitespace().map(|s| s.parse::<u64>().unwrap());
    let distances = distances.split_once(':').unwrap().1.split_whitespace().map(|s| s.parse::<u64>().unwrap());
    return times.zip(distances).map(|(time, distance)| Race {time, distance} ).map(|r| r.win_counts()).product();
}

fn part_2(input: &str) -> u64 {
    let (times, distances) = input.split_once('\n').unwrap();
    let time:u64 = times.split_once(':').unwrap().1.trim().replace(" ", "").parse().unwrap();
    let distance:u64 = distances.split_once(':').unwrap().1.trim().replace(" ", "").parse().unwrap();
    let race = Race { time, distance };
    return race.win_counts();
}

fn main() {
    let input = include_str!("input.txt");
    // let input = include_str!("example.txt");

    let time = std::time::Instant::now();
    println!("part 1: {}", part_1(input));
    println!("took {:?}", time.elapsed());
    let time = std::time::Instant::now();
    println!("part 2: {}", part_2(input));
    println!("took {:?}", time.elapsed());
}
