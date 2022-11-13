use crypto::{md5::Md5, digest::Digest};

fn next_hash(inp: &String, iter: &mut u64) -> String {
    let mut hasher = Md5::new();
    let mut output = [0 as u8; 16];
    let binp = inp.as_bytes();
    loop {
        hasher.input(binp);
        hasher.input(iter.to_string().as_bytes());

        hasher.result(&mut output);

        // let test_str:String = output.iter().map(|x| format!("{:#04x}", x).split_at(2).1.to_string()).collect();

        let bitmask = 0xf0u8;

        let cond = output[0] == 0 && output[1] == 0 && (output[2] & bitmask) == 0;

        if cond {
            return output.iter().map(|x| format!("{:#04x}", x).split_at(2).1.to_string()).collect();
        }

        hasher.reset();

        *iter += 1;
    }
}

fn part_1(input: &String) -> String {
    let mut iter = 0;
    let mut output = String::new();
    for _i in 0..8 {
        let hstr = next_hash(&input, &mut iter);
        iter += 1;
        println!("found working hash with iter: {}", iter);
        output.push(hstr.chars().nth(5).unwrap());
    }

    output
}


fn part_2(input: &String) -> String {
    let mut iter = 0;
    let mut o = ['\0'; 8];
    let mut found = 0;
    while found < 8{
        let hstr = next_hash(&input, &mut iter);
        iter += 1;
        println!("found working hash with iter: {}", iter);
        let pos_char = hstr.chars().nth(5).unwrap();
        if "01234567".contains(pos_char) {
            println!("valid pos char: {}", pos_char);
            if o[pos_char.to_digit(10).unwrap() as usize] != '\0' {
                println!("found empty pos, inserting new.")

            }
        }
    }

    todo!()
}


fn main() {
    // let input = "abc".to_string();
    let input = "reyedfim".to_string();

    let p1 = part_1(&input);
    println!("part 1: {}", p1);

    // let p2:String = part_2(input);
    // println!("part 2: {}", p2);
}
