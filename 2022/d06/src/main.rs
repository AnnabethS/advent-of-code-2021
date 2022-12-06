use std::collections::HashSet;

fn main() {
    let input = include_str!("input.txt");
    // let input = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw";
    //
    // 2033 < p2 < 2415

    let char_arr:Vec<_> = input.chars().collect();

    let mut part_1 = 0;
    for i in 3..char_arr.len() {
        // 1,2 1,3 1,4 2,3 2,4 3,4
        if ! (char_arr[i-3] == char_arr[i-2] ||
              char_arr[i-3] == char_arr[i-1] ||
              char_arr[i-3] == char_arr[i] ||
              char_arr[i-2] == char_arr[i-1] ||
              char_arr[i-2] == char_arr[i] ||
              char_arr[i-1] == char_arr[i]) {
            part_1 = i+1;
            break;
        }
    }

    let mut part_2 = 0;
    for i in 13..char_arr.len() {
        let mut hs:HashSet<char> = HashSet::new();
        let v = &char_arr[i-13..=i];
        let mut found = false;
        for c in v.iter() {
            if hs.contains(c) {
                found = true;
                break;
            }
            else {
                hs.insert(*c);
            }
        }
        if ! found {
            part_2 = i+1;
            break
        }
    }

    println!("part 1: {}", part_1);
    println!("part 2: {}", part_2);
}
