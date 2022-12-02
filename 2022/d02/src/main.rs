fn main() {
    let input = include_str!("input.txt");
    // let input = include_str!("example.txt");


    let mut part_1 = 0;

    for line in input.lines() {
        part_1 += get_line_score(line);
    }

    println!("part 1: {}", part_1);


    let mut part_2 = 0;

    for line in input.lines() {
        let moves = match line.chars().nth(2).unwrap() {
            'X' => {
                match line.chars().nth(0).unwrap() {
                    'A' => "A Z",
                    'B' => "B X",
                    'C' => "C Y",
                    _ => unreachable!()
                }
            },
            'Y' => {
                match line.chars().nth(0).unwrap() {
                    'A' => "A X",
                    'B' => "B Y",
                    'C' => "C Z",
                    _ => unreachable!()
                }
            } ,
            'Z' =>  {
                match line.chars().nth(0).unwrap() {
                    'A' => "A Y",
                    'B' => "B Z",
                    'C' => "C X",
                    _ => unreachable!()
                }
            },
            _ => unreachable!()
        };
        part_2 += get_line_score(moves);
    }

    println!("part 2: {}", part_2);
}

fn get_shape_score(s: &str) -> u32 {
    if s.chars().nth(2).unwrap() == 'X' {
        return 1
    }
    else if s.chars().nth(2).unwrap() == 'Y' {
        return 2
    }
    else if s.chars().nth(2).unwrap() == 'Z' {
        return 3
    }
    unreachable!()
}

fn get_line_score(s: &str) -> u32 {
    let win_states = vec!("A Y", "B Z", "C X");
    let draw_states = vec!("A X", "B Y", "C Z");
    let loss_states = vec!("A Z", "B X", "C Y");

    let mut score = 0;
    if win_states.contains(&s) {
        score += 6;
    }
    else if draw_states.contains(&s) {
        score += 3;
    }
    else if ! loss_states.contains(&s) {
        unreachable!("illegal input: {}", s);
    }
    score += get_shape_score(s);
    score
}

