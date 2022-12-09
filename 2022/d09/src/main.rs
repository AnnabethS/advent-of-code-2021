use std::collections::HashSet;

#[derive(Clone, Copy, PartialEq, Eq)]
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
}

#[derive(Debug, Hash, PartialEq, Eq, Clone, Copy)]
struct Vec2 {
    x: i32,
    y: i32,
}

impl Vec2 {
    fn new(x: i32, y: i32) -> Self {
        Self { x, y }
    }

    fn mv(&mut self, dir: &Direction) {
        match dir {
            Direction::UP    => self.y += 1,
            Direction::DOWN  => self.y -= 1,
            Direction::LEFT  => self.x -= 1,
            Direction::RIGHT => self.x += 1,
        }
    }

    fn toward(&mut self, head: &Vec2) {
        if self.x.abs_diff(head.x) <= 1 && self.y.abs_diff(head.y) <= 1 {
            return
        }
        self.x += (head.x - self.x).signum();
        self.y += (head.y - self.y).signum();
    }
}

fn main() {
    let input = include_str!("input.txt").trim();
    // let input = include_str!("example.txt").trim();

    let mut moves:Vec<Direction> = Vec::new();

    for line in input.lines() {
        let (dir, amnt) = line.split_once(' ').unwrap();
        let dir = match dir {
            "U" => Direction::UP,
            "D" => Direction::DOWN,
            "R" => Direction::RIGHT,
            "L" => Direction::LEFT,
            _   => unreachable!()
        };
        for _ in 0..amnt.parse().unwrap() {
            moves.push(dir);
        }
    }

    let mut head = Vec2::new(0,0);
    let mut tail = Vec2::new(0,0);

    let mut visited: HashSet<Vec2> = HashSet::new();

    for mv in moves.iter() {
        head.mv(&mv);
        tail.toward(&head);
        visited.insert(tail);
    }

    println!("part 1: {}", visited.len());

    // part 2

    let mut knots: Vec<Vec2> = Vec::new();
    for _ in 0..10 {
        knots.push(Vec2::new(0,0));
    }

    let mut visited_2: HashSet<Vec2> = HashSet::new();

    for mv in moves {
        knots[0].mv(&mv);
        for i in 1..knots.len() {
            let prev = knots[i-1];
            knots[i].toward(&prev);
        }
        visited_2.insert(knots[knots.len() - 1]);
    }

    println!("part 2: {}", visited_2.len());

}
