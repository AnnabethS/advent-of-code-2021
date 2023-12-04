use std::collections::{HashSet, HashMap};

fn part_2(input: &str) -> u64 {
    let mut cards: HashMap<usize, u64> = HashMap::new();
    let total_cards = input.lines().count();
    for (i, line) in input.lines().enumerate() {
        let (winning, have) = line.split_once(':').unwrap().1.split_once('|').unwrap();
        let win_nums:HashSet<u64>  = winning
            .split(' ')
            .filter(|s| !s.is_empty())
            .map(|s| s.parse().expect("parse fail"))
            .collect();
        let have_nums:HashSet<u64>  = have
            .split(' ')
            .filter(|s| !s.is_empty())
            .map(|s| s.parse().expect("parse fail"))
            .collect();

        let copies = cards.get(&i).unwrap_or(&1).to_owned(); // how many copies of this card
        cards.insert(i, copies);
        let matches = have_nums.intersection(&win_nums).count() as u64;
        if matches == 0 {
            continue
        }
        else {
            for j in 1..=matches {
                let idx = i + (j as usize);
                if idx > total_cards {
                    break;
                }
                let new_copies = cards.get(&idx).unwrap_or(&1) + copies;
                cards.insert(idx, new_copies);
            }
        }
    }
    return cards.iter().fold(0, |acc, (_, v)| acc+v);
}

fn part_1(input: &str) -> u64 {
    let mut total = 0;
    for line in input.lines() {
        let (winning, have) = line.split_once(':').unwrap().1.split_once('|').unwrap();
        let win_nums:HashSet<u64>  = winning
            .split(' ')
            .filter(|s| !s.is_empty())
            .map(|s| s.parse().expect("parse fail"))
            .collect();
        let have_nums:HashSet<u64>  = have
            .split(' ')
            .filter(|s| !s.is_empty())
            .map(|s| s.parse().expect("parse fail"))
            .collect();

        let matches = have_nums.intersection(&win_nums).count() as u64;
        if matches <= 1 {
            total += matches;
        }
        else {
            total += 2_u64.pow((matches-1) as u32);
        }
    }
    return total;
}

fn main() {
    // let input = include_str!("example.txt");
    let input = include_str!("input.txt");
    let started = std::time::Instant::now();
    println!("part 1: {}", part_1(input));
    println!("part 1 took {:?}", started.elapsed());
    let started = std::time::Instant::now();
    println!("part 2: {}", part_2(input));
    println!("part 2 took {:?}", started.elapsed());
}
