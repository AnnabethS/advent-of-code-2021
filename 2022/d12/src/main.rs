use std::collections::BinaryHeap;
use std::collections::HashSet;

#[derive(Clone, Copy, Debug)]
struct Node {
    x: usize,
    y: usize,
    t: Tile,
    path_cost: u32,
    h_cost: u32,
    total_cost: u32,
}

impl PartialEq for Node {
    fn eq(&self, other: &Self) -> bool {
        return self.total_cost == other.total_cost;
    }
}

impl Eq for Node {

}

impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        return Some(other.total_cost.cmp(&self.total_cost));
    }
}

impl Ord for Node {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        return other.total_cost.cmp(&self.total_cost);
    }
}

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
enum Tile {
    NORMAL(u8),
    START(u8),
    GOAL(u8),
}

impl Tile {
    fn get_val(&self) -> u8 {
        match self {
            Tile::NORMAL(x) => return *x,
            Tile::START(x) => return *x,
            Tile::GOAL(x) => return *x,
        }
    }

    fn is_goal(&self) -> bool {
        return match self {
            Tile::GOAL(_) => true,
            _             => false,
        }
    }

    fn from_char(c: char) -> Self {
        if c=='S' {
            return Tile::START(0);
        } else if c=='E' {
            return Tile::GOAL(25);
        }
        else {
            return Tile::NORMAL((c as u32 - 'a' as u32) as u8);
        }
    }
}

fn in_bounds(point: &(i32, i32), grid:&Vec<Vec<Tile>>) -> bool {
    if point.0 >= 0 && point.1 >= 0 {
        if point.0 < grid[0].len() as i32 {
            if point.1 < grid.len() as i32 {
                return true;
            }
        }
    }
    return false;
}

fn get_neighbours(current_node: &Node, grid: &Vec<Vec<Tile>>, closed: &HashSet<(usize, usize)>) -> Vec<Node> {
    let mut possible_neighbours = vec![
        ((current_node.x as i32) + 1, current_node.y as i32),
        (current_node.x as i32, (current_node.y as i32) + 1),
        ((current_node.x as i32) - 1, current_node.y as i32),
        (current_node.x as i32, (current_node.y as i32) - 1)];
    possible_neighbours = possible_neighbours
        .into_iter()
        .filter(|p| in_bounds(p, grid))
        .filter(|p| ! closed.contains(&(p.0 as usize, p.1 as usize)))
        .collect();

    // dbg!(&possible_neighbours);

    let mut goal_pos = (0,0);
    for (y, line) in grid.iter().enumerate() {
        for (x, sq) in line.iter().enumerate() {
            if sq.is_goal() {
                goal_pos = (x,y);
            }
        }
    };

    let neighbours = possible_neighbours
        .iter_mut()
        .map(|point| Node{
            x: point.0 as usize,
            y: point.1 as usize,
            t: grid[point.1 as usize][point.0 as usize],
            path_cost: current_node.path_cost+1,
            h_cost: (((point.0.abs_diff(goal_pos.0 as i32)).pow(2) + (point.1.abs_diff(goal_pos.1 as i32)).pow(2)) as f32).sqrt().floor() as u32,
            total_cost: 0})
        .filter(|node| (current_node.t.get_val() + 1) >= node.t.get_val())
        .map(|mut node| {
            node.total_cost = node.h_cost + node.path_cost;
            node
        })
        .collect();
    // dbg!(&neighbours);
    return neighbours;
}

fn shortest_to_goal(start: (usize, usize), grid: &Vec<Vec<Tile>>, best: u32) -> Option<u32> {
    let mut current_sq = Node {
        x: start.0,
        y: start.1,
        t: Tile::NORMAL(0),
        path_cost: 0,
        h_cost: 0,
        total_cost: 0};

    let mut heap:BinaryHeap<Node> = BinaryHeap::new();
    let mut closed:HashSet<(usize, usize)> = HashSet::new();
    heap.push(current_sq);

    while ! current_sq.t.is_goal()  {
        if closed.contains(&(current_sq.x, current_sq.y)) {
            if heap.is_empty() {
                return None;
            }
            current_sq = heap.pop().unwrap();
            continue;
        }
        let neighbours = get_neighbours(&current_sq, &grid, &closed);
        for n in neighbours.iter() {
            if n.path_cost < best {
                heap.push(*n);
            }
        }
        closed.insert((current_sq.x, current_sq.y));
        if heap.is_empty() {
            return None;
        }
        current_sq = heap.pop().unwrap();
    }

    return Some(current_sq.path_cost);
}

fn main() {
    let input = include_str!("input.txt").trim();
    // let input = include_str!("example.txt").trim();

    let grid:Vec<Vec<_>> = input
        .lines()
        .map(|line| line
            .chars()
            .map(Tile::from_char)
            .collect())
        .collect();

    let mut part_1_start: (usize, usize) = (0,0);

    for (y, line) in grid.iter().enumerate() {
        for (x, sq) in line.iter().enumerate() {
            match sq {
                Tile::START(v) => part_1_start = (x,y),
                _ => continue
            }
        }
    };

    let part_1 = shortest_to_goal(part_1_start, &grid, u32::MAX);


    println!("part 1: {}", part_1.unwrap_or(0));

    let mut best = Some(u32::MAX);

    for (y, line) in grid.iter().enumerate() {
        for (x, sq) in line.iter().enumerate() {
            if sq.get_val() == 0 {
                best = match shortest_to_goal((x,y), &grid, best.unwrap()) {
                    Some(new_best) => Some(new_best),
                    None => best,
                };
            }
        }
    };
    println!("part 2: {}", best.unwrap());
}
