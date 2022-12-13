use std::cmp::Ordering;

#[derive(Debug, Clone)]
enum Item {
    LST(Vec<Item>),
    VAL(u32)
}

impl Item {
    fn get_val(&self) -> u32 {
        match self {
            Item::LST(x) => panic!("get_val called on LST, contents: {:?}", x),
            Item::VAL(x) => return *x,
        }
    }
}

impl PartialEq for Item {
    fn eq(&self, other: &Self) -> bool {
        let x = self.cmp(other);
        match x {
            Ordering::Equal => true,
            _ => false,
        }
        // match self {
        //     Item::LST(x) => match other {
        //         Item::LST(y) => x==y,
        //         Item::VAL(y) => {
        //             if x.len() > 0 {
        //                 return x[0].get_val() == *y;
        //             } else {
        //                 return false
        //             }
        //         },
        //     },
        //     Item::VAL(x) => match other {
        //         Item::LST(y) => {
        //             if y.len() > 0 {
        //                 return y[0].get_val() == *x;
        //             } else {
        //                 return false
        //             }
        //         },
        //         Item::VAL(y) => x==y,
        //     },
        // }
    }
}

impl PartialOrd for Item {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        return Some(self.cmp(other));
    }
}

// tell the compiler that my PartialEq is reflexitive, symmetric & transitive
impl Eq for Item {}

impl Ord for Item {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        // println!("comparing {:?} and {:?}", self, other);
        match self {
            Item::LST(x) => match other {
                Item::LST(y) => {
                    let iters = x.len().min(y.len());
                    for i in 0..iters {
                        match x[i].cmp(&y[i]) {
                            Ordering::Equal => continue,
                            Ordering::Less => return Ordering::Less,
                            Ordering::Greater => return Ordering::Greater,
                        }
                    }
                    return x.len().cmp(&y.len());
                },
                Item::VAL(y) => Item::LST(x.clone()).cmp(&Item::LST(vec![Item::VAL(*y)])),
            },
            Item::VAL(x) => match other {
                Item::LST(y) => Item::LST(vec![Item::VAL(*x)]).cmp(&Item::LST(y.clone())),
                Item::VAL(y) => x.cmp(y),
            },
        }
    }
}

fn find_closing_bracket(s: &str) -> usize {
    let mut brackets = 0;
    for (i, c) in s.chars().enumerate() {
        if c=='[' {
            brackets += 1;
        }
        else if c==']' {
            brackets -= 1;
            if brackets == 0 {
                return i;
            }
        }
    }
    unreachable!();
}

fn parse_item(s: &str) -> Item {
    let s = match s.chars().nth(0).unwrap() {
        ',' => &s[1..],
        _ => s
    };
    match s.parse::<u32>() { // should parse single items
        Ok(x) => return Item::VAL(x),
        Err(_) => (),
    };
    if s.len() == 2 { // must be []
        return Item::LST(Vec::new());
    }
    let s = &s[1..s.len()-1]; // trim the remaining []

    let mut nesteds = Vec::new();

    for i in 0..s.len() {
        if s.chars().nth(i).unwrap() == '[' {
            let end = find_closing_bracket(&s[i..]);
            nesteds.push(i..=i+end);
        }
    }

    let mut commas:Vec<usize> = s.match_indices(',').filter(|(i, _)| ! nesteds.iter().any(|range| range.contains(i))).map(|(i, _)| i).collect();
    commas.insert(0, 0);
    commas.push(s.len());

    let mut item_strs = Vec::new();

    for i in 0..(commas.len()-1) {
        item_strs.push(&s[commas[i]..commas[i+1]]);
    }

    let mut items:Vec<Item> = Vec::new();
    for istr in item_strs.iter() {
        items.push(parse_item(istr));
    }

    return Item::LST(items);
}

fn main() {
    // let input = include_str!("example.txt");
    let input = include_str!("input.txt");

    let pairs:Vec<_> = input
        .split("\n\n")
        .map(|pair| pair.split_once('\n').unwrap())
        .map(|(l1, l2)| (parse_item(l1), parse_item(l2)))
        .collect();

    // pairs[2].0 < pairs[2].1;

    let mut part_1 = 0;
    for (i, pair) in pairs.iter().enumerate() {
        // println!("{}: {:?}",i+1 ,pair.0 < pair.1);
        if pair.0 < pair.1 {
            part_1 += i+1;
        }
    }

    println!("part 1: {}", part_1);

    let mut items:Vec<_> = input.lines().filter(|s| ! s.is_empty()).map(parse_item).collect();

    let div1 = Item::LST(vec![Item::LST(vec![Item::VAL(2)])]);
    let div2 = Item::LST(vec![Item::LST(vec![Item::VAL(6)])]);
    items.push(div1.clone());
    items.push(div2.clone());
    items.sort();

    let d1_loc = items.iter().enumerate().find(|(_, x)| **x==div1).map(|(i, _)| i).unwrap() + 1;
    let d2_loc = items.iter().enumerate().find(|(_, x)| **x==div2).map(|(i, _)| i).unwrap() + 1;

    let part_2 = d1_loc * d2_loc;
    println!("part 2: {}", part_2);
}
