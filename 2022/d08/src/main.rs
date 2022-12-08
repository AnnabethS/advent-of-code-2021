use std::collections::HashSet;

#[derive(PartialEq, Eq)]
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
}

fn vertical_slice(trees: &Vec<Vec<u32>>, column: usize) -> Vec<u32> {
    let mut v = Vec::new();
    for row in trees.iter() {
        v.push(row[column]);
    }
    v
}

fn do_line(hs: &mut HashSet<(usize, usize)>, trees: &Vec<Vec<u32>>, start: (usize, usize), mv_dir: Direction) {
    let slice = match mv_dir {
        Direction::UP => {
            let mut v = vertical_slice(trees, start.0);
            v.reverse();
            v
        },
        Direction::DOWN => vertical_slice(trees, start.0),
        Direction::LEFT => {
            let mut v = trees[start.1].clone();
            v.reverse();
            v
        },
        Direction::RIGHT => trees[start.1].clone(),
    };

    let len = trees.len();

    // its a square grid so it doesnt matter which axis we get length on
    let first = match mv_dir {
        Direction::UP => (start.0, (len-1)),
        Direction::DOWN => (start.0, 0),
        Direction::LEFT => ((len-1), start.1),
        Direction::RIGHT => (0, start.1),
    };
    let mut highest = slice[0];
    hs.insert(first);
    for (i, v) in slice.iter().enumerate() {
        if i==0 {
            continue;
        }
        if *v > highest {
            let pos = match mv_dir {
                Direction::UP => (start.0, (len-1) - i),
                Direction::DOWN => (start.0, i),
                Direction::LEFT => ((len-1) - i, start.1),
                Direction::RIGHT => (i, start.1),
            };
            hs.insert(pos);
            highest = *v;
        }
    }
}

fn part_1(trees: &Vec<Vec<u32>>) {
    let mut hs:HashSet<(usize, usize)> = HashSet::new();

    let size = trees.len();

    for i in 0..size {
        do_line(&mut hs, &trees, (i,0), Direction::DOWN);
        do_line(&mut hs, &trees, (i,0), Direction::UP);
        do_line(&mut hs, &trees, (0,i), Direction::LEFT);
        do_line(&mut hs, &trees, (0,i), Direction::RIGHT);
    }

    println!("part 1: {}", hs.len());

}

fn get_scenic_score(trees: &Vec<Vec<u32>>, pos: (usize, usize)) -> u32 {
    // left
    let mut highest = trees[pos.1][pos.0];
    let mut lscore = 0;
    for x in (0..pos.0).rev() {
        if trees[pos.1][x] < highest {
            // highest = trees[pos.1][x];
            lscore += 1;
        }
        else {
            lscore += 1;
            break;
        }
    }
    highest = trees[pos.1][pos.0];
    let mut rscore = 0;
    for x in (pos.0+1)..trees.len() {
        // dbg!(trees[pos.1][x]);
        if trees[pos.1][x] < highest {
            // highest = trees[pos.1][x];
            rscore += 1;
        }
        else {
            rscore += 1;
            break;
        }
    }

    let mut uscore = 0;
    highest = trees[pos.1][pos.0];
    for y in (0..pos.1).rev() {
        if trees[y][pos.0] < highest {
            // highest = trees[y][pos.0];
            uscore += 1;
        } else {
            uscore += 1;
            break;
        }
    }

    let mut dscore = 0;
    highest = trees[pos.1][pos.0];
    for y in (pos.1+1)..trees.len() {
        if trees[y][pos.0] < highest {
            // highest = trees[y][pos.0];
            dscore += 1;
        } else {
            dscore += 1;
            break;
        }
    }

    // dbg!(lscore);
    // dbg!(rscore);
    // dbg!(dscore);
    // dbg!(uscore);

    lscore * rscore * dscore * uscore
}

fn part_2(trees: &Vec<Vec<u32>>) {
    let mut highest = 0;
    for (y, line) in trees.iter().enumerate() {
        for (x, _) in line.iter().enumerate() {
            let scenic = get_scenic_score(trees, (x,y));
            highest = scenic.max(highest);
        }
    }
    println!("part 2: {}", highest)
}

fn main() {
    // let input = include_str!("example.txt").trim();
    let input = include_str!("input.txt").trim();

    let trees:Vec<Vec<_>> = input.lines().map(|line| line.chars().map(|x| x.to_digit(10).unwrap()).collect()).collect();

    part_1(&trees);
    part_2(&trees);
    // dbg!(get_scenic_score(&trees, (2, 3)));
}
