#[allow(non_camel_case_types)] // i like capitalised enums

use std::collections::HashMap;
use std::collections::HashSet;

#[derive(Debug, PartialEq, Eq)]
enum Square {
    SENSOR,
    BEACON,
    UNKNOWN,
    NOT_BEACON,
}

fn parse_line(s: &str) -> ((i32, i32), (i32, i32)) {
    let words:Vec<_> = s.split(' ').collect();
    let sensor_x:i32 = words[2][2..(words[2].len())-1].parse().unwrap();
    let sensor_y:i32 = words[3][2..(words[3].len())-1].parse().unwrap();

    let beacon_x:i32 = words[8][2..(words[8].len())-1].parse().unwrap();
    let beacon_y:i32 = words[9][2..].trim().parse().unwrap();

    return ((sensor_x, sensor_y), (beacon_x, beacon_y));
}

fn get_dist(src: (i32, i32), other: (i32, i32)) -> u32 {
    return src.0.abs_diff(other.0) + src.1.abs_diff(other.1);
}

fn point_within_dist(src: (i32, i32), other: (i32, i32), dist: u32) -> bool {
    return get_dist(src, other) < dist;
}

fn main() {
    // let input = include_str!("example.txt").trim();
    let input = include_str!("input.txt").trim();

    let mut grid: HashMap<(i32, i32), Square> = HashMap::new();

    let mut pairs:Vec<_> = input.lines().map(parse_line).collect();

    for line in input.lines() {
        let (sensor, beacon) = parse_line(line);
    }

    let low_x = pairs
        .iter()
        .min_by(|(_, (x1,_)), (_, (x2,_))| x1.cmp(x2))
        .unwrap().1.0;
    let high_x = pairs
        .iter()
        .max_by(|(_, (x1,_)), (_, (x2,_))| x1.cmp(x2))
        .unwrap().1.0;

    let mut part_1 = 0;

    for x in low_x..=high_x {
        let mut is_unknwn = false;
        let mut is_not_beacon = false;
        for (sensor, beacon) in pairs.iter() {
            let point = (x, 2000000);
            if point == *sensor {
                is_not_beacon = true;
                break;
            }
            if point_within_dist(*sensor, point, get_dist(*sensor, *beacon)) {
                is_unknwn = true;
                break;
            }
        }
        if is_unknwn || is_not_beacon {
            part_1 += 1;
        }
    }

    println!("{}", part_1);
    // 4668615 too low
}
