use year_2019::grid::GridPoint;

#[derive(Debug)]
struct Wire {
    points: Vec<GridPoint>
}

impl From<&str> for Wire {
    fn from(value: &str) -> Self {
        let mut x = 0;
        let mut y = 0;
        let mut points = vec![GridPoint::new(x, y)];
        for token in value.split(',') {
            match token.chars().nth(0).unwrap() {
                'U' => y += token[1..].parse::<i64>().expect(&format!("Could not parse ({}) as i64", &token[1..])),
                'D' => y -= token[1..].parse::<i64>().expect(&format!("Could not parse ({}) as i64", &token[1..])),
                'L' => x -= token[1..].parse::<i64>().expect(&format!("Could not parse ({}) as i64", &token[1..])),
                'R' => x += token[1..].parse::<i64>().expect(&format!("Could not parse ({}) as i64", &token[1..])),
                _ => panic!("unexpected token during parse! ({})", token)
            }
            points.push(GridPoint::new(x, y));
        }
        return Wire { points };
    }
}

fn get_section_crosses(w1p1: &GridPoint, w1p2: &GridPoint, w2p1: &GridPoint, w2p2: &GridPoint) -> Option<Vec<GridPoint>> {
    if w1p1.x == w1p2.x {
        // w1 vertical wire
        if w2p1.x == w2p2.x {
            // w2 vertical wire
        } else if w2p1.y == w2p2.y {
            // w2 horizontal wire
        } else {
            unreachable!()
        }
    }
    else if w1p1.y == w1p2.y {
        // w1 horizontal wire
        if w2p1.x == w2p2.x {
            // w2 vertical wire
        } else if w2p1.y == w2p2.y {
            // w2 horizontal wire
        } else {
            unreachable!()
        }
    }
    else {
        unreachable!()
    }

    todo!()
}

fn main() {
    todo!();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn wire_from_string() {
        let wire:Wire = "R8,U5,L5,D3".into();

        assert_eq!(wire.points,
            vec![
                GridPoint::new(0, 0),
                GridPoint::new(8, 0),
                GridPoint::new(8, 5),
                GridPoint::new(3, 5),
                GridPoint::new(3, 2),
            ])
    }
}
