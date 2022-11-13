use std::collections::HashMap;

fn proc_line(word: &str, hashes: &mut Vec<HashMap<char, u32>>) {
    for (i,c) in word.chars().enumerate() {
        let occurances:u32 = match hashes.get(i).unwrap().get(&c) {
            Some(x) => x+1,
            None => 0,
        };
        hashes[i].insert(c, occurances);
    }
}

fn most_common(hashes: &Vec<HashMap<char, u32>>) -> String {
    let mut output = String::new();

    for v in hashes.iter() {
        output.push(*v.iter().max_by(|x, y| x.1.cmp(y.1)).unwrap().0);
    }

    output
}

fn least_common(hashes: &Vec<HashMap<char, u32>>) -> String {
    let mut output = String::new();

    for v in hashes.iter() {
        output.push(*v.iter().min_by(|x, y| x.1.cmp(y.1)).unwrap().0);
    }

    output
}

fn main() {
    // let input = include_str!("example.txt");
    let input = include_str!("input.txt");

    let wordlen = input.find('\n').unwrap();
    println!("word length: {}", wordlen);

    let mut hashes:Vec<HashMap<char, u32>> = Vec::new();

    for _i in 0..wordlen {
        hashes.push(HashMap::new());
    }

    for word in input.lines() {
        proc_line(word, &mut hashes);
    }

    let part1 = most_common(&hashes);
    let part2 = least_common(&hashes);

    println!("part1: {}", part1);
    println!("part2: {}", part2);
}
