use std::str::FromStr;
use std::collections::VecDeque;

#[derive(Debug, Clone, Copy)]
enum Operation {
    Sqr(),
    Dbl(),
    Add(u32),
    Mul(u32),
}

#[derive(Debug, Clone)]
struct Monkey
{
    items: VecDeque<u64>,
    op: Operation,
    test: u32,
    true_monkey: usize,
    false_monkey: usize,
    inspects: u32,
}

impl FromStr for Monkey
{
    type Err = ();
    fn from_str(s: &str) -> Result<Self, ()> {
        let lines:Vec<&str> = s.lines().collect();
        let (_, items) = lines[1].split_once(':').unwrap();
        let items = items.trim().split(',').map(|x| x.trim().parse().unwrap()).collect();

        let (_, op) = lines[2].split_once('=').unwrap();

        let op:Vec<&str> = op.trim().split(' ').collect();

        let op = if op[1] == "*" {
            if op[2] == "old" {
                Operation::Sqr()
            } else {
                Operation::Mul(op[2].parse().unwrap())
            }
        } else if op[1] == "+" {
            if op[2] == "old" {
                Operation::Dbl()
            } else {
                Operation::Add(op[2].parse().unwrap())
            }
        } else {
            unreachable!()
        };

        let test = lines[3].split(' ').last().unwrap().parse().unwrap();
        let true_monkey = lines[4].split(' ').last().unwrap().parse().unwrap();
        let false_monkey = lines[5].split(' ').last().unwrap().parse().unwrap();

        return Ok(Monkey { items, op, test, true_monkey, false_monkey, inspects: 0 });
    }

}

fn do_round(monkeys: &mut Vec<Monkey>) {
    for i in 0..monkeys.len() {
        while ! monkeys[i].items.is_empty() {
            monkeys[i].inspects += 1;
            let mut item = monkeys[i].items.pop_front().unwrap();
            item = match monkeys[i].op {
                Operation::Sqr() => item*item,
                Operation::Dbl() => item+item,
                Operation::Add(x) => item+x as u64,
                Operation::Mul(x) => item*x as u64,
            };
            item /= 3;
            let monkey_idx = if (item % monkeys[i].test as u64) == 0 {
                monkeys[i].true_monkey
            } else {
                monkeys[i].false_monkey
            };

            monkeys[monkey_idx].items.push_back(item);
        }
    }
}

fn do_round_2(monkeys: &mut Vec<Monkey>) {
    let m:u64 = monkeys.iter().map(|m| m.test).product::<u32>() as u64;
    for i in 0..monkeys.len() {
        while ! monkeys[i].items.is_empty() {
            monkeys[i].inspects += 1;
            let mut item = monkeys[i].items.pop_front().unwrap();
            item = match monkeys[i].op {
                Operation::Sqr() => item*item,
                Operation::Dbl() => item+item,
                Operation::Add(x) => item+x as u64,
                Operation::Mul(x) => item*x as u64,
            };
            item = item % m;
            let monkey_idx = if (item % monkeys[i].test as u64) == 0 {
                monkeys[i].true_monkey
            } else {
                monkeys[i].false_monkey
            };

            monkeys[monkey_idx].items.push_back(item);
        }
    }
}

fn main() {
    // let input = include_str!("example.txt");
    let input = include_str!("input.txt");

    let mut monkeys_1:Vec<Monkey> = input.split("\n\n").map(|x| x.parse().unwrap()).collect();
    let mut monkeys_2 = monkeys_1.clone();

    for _ in 0..20 {
        do_round(&mut monkeys_1);
    }

    monkeys_1.sort_by(|m1, m2| m2.inspects.cmp(&m1.inspects));

    let part_1 = monkeys_1[0].inspects * monkeys_1[1].inspects;

    println!("part 1: {}", part_1);

    for _ in 0..10000 {
        do_round_2(&mut monkeys_2);
    }

    monkeys_2.sort_by(|m1, m2| m2.inspects.cmp(&m1.inspects));
    let part_2 = monkeys_2[0].inspects as u128 * monkeys_2[1].inspects as u128;

    println!("part 2: {}", part_2);
}
