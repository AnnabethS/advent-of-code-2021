use std::{collections::HashMap, cmp::Ordering};

#[derive(Debug)]
struct Room {
    name: String,
    sector_id: u16,
    checksum: String,
}

impl Room {
    fn new(raw: &str) -> Room {
        let split:Vec<&str> = raw.split("[").collect();
        if split.len() != 2 {
            panic!("cant parse input: {}", raw);
        }
        let mut checksum = split[1].to_string();
        checksum.truncate(5);

        let splits:Vec<&str> = raw.split("-").collect();
        let mut code = splits.last().expect(format!("failed splitting raw: {}", raw).as_str()).to_string();
        code.truncate(3);
        let sector_id = code.parse().expect(format!("failed parsing id: {}", &code).as_str());

        Room {
            name: split[0].split_at(split[0].rfind("-").expect("couldnt split name")).0.to_string(),
            sector_id,
            checksum,
        }
    }

    fn is_real(&self) -> bool {
        let mut letterhash:HashMap<char, u32> = HashMap::new();
        for c in self.name.chars() {
            if c == '-' {
                continue;
            }
            if letterhash.contains_key(&c) {
                letterhash.insert(c, 1 + (*letterhash.get(&c).unwrap()));
            } else {
                letterhash.insert(c, 1);
            }
        }
        let mut tuples: Vec<(&char, &u32)> = letterhash.iter().collect();
        tuples.sort_by(srt);

        let mut valid_checksum = String::new();

        for i in 0..5 {
            valid_checksum.push(*tuples[i].0);
        }

        valid_checksum == self.checksum
    }

    fn decrypt(&mut self) {
        self.name = self.name.chars().map(|c| shift(c, self.sector_id)).collect();
    }
}
fn srt(a: &(&char, &u32), b: &(&char, &u32)) -> Ordering {
    let valcmp = b.1.cmp(a.1);
    if valcmp == Ordering::Equal {
        return a.0.cmp(b.0);
    }
    return valcmp;
}

fn shift(c: char, shift: u16) -> char {
    if c == '-' || c == ' ' {
        return ' '
    }
    let alphabet = "abcdefghijklmnopqrstuvwxyz";
    let initial_pos = alphabet.find(c).unwrap();
    let new_pos = (initial_pos + shift as usize) % 26;
    alphabet.as_bytes()[new_pos] as char
}

fn main() {
    // let input = include_str!("example.txt").trim();
    let input = include_str!("input.txt").trim();
    let mut rooms:Vec<Room> = input.lines().map(|line| Room::new(line)).collect();
    let mut total:u64 = 0;
    rooms = rooms.into_iter().filter(Room::is_real).collect();
    for rm in rooms.iter() {
        total += rm.sector_id as u64;
    }
    println!("part 1: {}", total);
    for rm in rooms.iter_mut() {
        rm.decrypt();
        if rm.name.contains("north") {
            println!("{:?}", rm);
        }
    }

}
