fn is_report_safe(report: &Vec<i64>) -> bool {
    let mut all_inc = true;
    let mut all_dec = true;
    for i in 0..report.len()-1 {
        if report[i] > report[i+1] {
            all_dec = false;
        }
        else if report [i] < report[i+1] {
            all_inc = false;
        } else {
            return false;
        }
        if report[i].abs_diff(report[i+1]) > 3 {
            return false;
        }
    }
    return all_inc || all_dec;
}

fn part1(reports: &Vec<Vec<i64>>) -> i64 {
    return reports.iter()
        .filter(|report| is_report_safe(&report))
        .count() as i64;
}

fn part2(reports: &Vec<Vec<i64>>) -> i64 {
    let mut count = 0;
    for report in reports {
        if is_report_safe(report) {
            count += 1;
            continue;
        }
        for i in 0..report.len() {
            let mut report_with_removal = report.clone();
            report_with_removal.remove(i);
            if is_report_safe(&report_with_removal) {
                count += 1;
                break;
            }
        }
    }

    return count;
}

fn main() {
    let raw_data = std::fs::read_to_string("data/d02.txt").unwrap();
    let reports: Vec<Vec<i64>> = raw_data.lines().map(|line| line.split_whitespace().map(|num| num.parse::<i64>().unwrap()).collect()).collect();
    let p1 = part1(&reports);
    println!("part 1 {}", p1);
    let p2 = part2(&reports);
    println!("part 2 {}", p2);
}
