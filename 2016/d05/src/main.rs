use md5::{Digest, Md5};

fn get_hexstring(input: &String, iter: u64) -> String {
    let x = format!("{}{}", input, iter);
    Md5::digest(x.as_bytes()).iter()
        .map(|i| format!("{:#04x}", i).split_at(2).1.to_string())
        .collect::<Vec<String>>()
        .concat()
}

// fn next_hash(inp: String, iter: u64) {
//     let mut hasher = Md5::new();
//     let mut output = [0; 16];
//     hasher.chain_update(inp.as_bytes()).update(iter.to_string().as_bytes());
//     hasher.finalize_into_reset(&mut output);
// }

fn part_1(input: String) -> String {
    let mut found = 0;
    let mut iter = 0;
    let mut output = String::new();
    while found < 8 {
        let hstr = get_hexstring(&input, iter);
        if &hstr[0..5] == "00000" {
            println!("found char {}", found+1);
            output.push(hstr.chars().nth(5).unwrap());
            found += 1;
        }
        iter += 1;
    }

    output
}

fn part_2(input: String) -> String {
    let mut found = 0;
    let mut iter = 0;
    // let mut output = String::new();
    let mut output:Vec<Option<char>> = vec!(None, None, None, None, None, None, None, None);
    while found < 8 {
        if iter % 100000 == 0 {
            println!("iter {}", iter);
        }
        let hstr = get_hexstring(&input, iter);
        if &hstr[0..5] == "00000" {
            let c = hstr.chars().nth(5).unwrap();
            if "01234567".contains(c) {
                println!("foooooo");
                output[c.to_digit(10).unwrap() as usize] = Some(hstr.chars().nth(6).unwrap());
                found += 1;
            }
        }
        iter += 1;
    }

    output.iter().map(|x| x.unwrap()).collect()
}

fn main() {
    let input = "abc".to_string();
    // let input = "reyedfim".to_string();

    // this solution is pretty inefficient, just gen the part you want to see

    // let p1:String = part_1(input);
    // println!("part 1: {}", p1);

    let p2:String = part_2(input);
    println!("part 2: {}", p2);
}
