use regex::Regex;

#[derive(Debug)]
struct IP {
    outers: Vec<String>,
    inners: Vec<String>,
}

impl IP {
    fn new(line: &str) -> IP {
        let outer_re = Regex::new(r"\[[^\]]+\]").unwrap();
        let inner_re = Regex::new(r"\[([^\]]+)\]").unwrap();

        IP {
            outers: outer_re.split(line).map(|s| s.to_string()).collect(),
            inners: inner_re.captures_iter(line).map(|s| s[1].to_string()).collect(),
        }
    }

    fn supports_tls(&self) -> bool {
        let alphabet = "abcdefghijklmnopqrstuvwxyz".to_string();
        for a in alphabet.chars() {
            for b in alphabet.chars() {
                if a==b {
                    continue
                }
                let pattern = format!("{}{}{}{}", a, b, b, a);
                let in_outers = self.outers.iter().any(|s| s.contains(&pattern));
                if in_outers {
                    for c in alphabet.chars() {
                        for d in alphabet.chars() {
                            if c==d {
                                continue
                            }
                            let pattern = format!("{}{}{}{}", c, d, d, c);
                            if self.inners.iter().any(|s| s.contains(&pattern)) {
                                return false
                            }
                        }
                    }
                    return true;
                }
            }
        }

        return false
    }

    fn supports_ssl(&self) -> bool {
        let alphabet = "abcdefghijklmnopqrstuvwxyz".to_string();
        for a in alphabet.chars() {
            for b in alphabet.chars() {
                if a==b {
                    continue
                }
                let outer_pattern = format!("{}{}{}", a, b, a);
                let inner_pattern = format!("{}{}{}", b, a, b);
                let in_outers = self.outers.iter().any(|s| s.contains(&outer_pattern));
                let in_inners = self.inners.iter().any(|s| s.contains(&inner_pattern));
                if in_inners && in_outers {
                    return true
                }
            }
        }

        return false
    }
}

fn main() {
    // let input = include_str!("example.txt").trim();
    let input = include_str!("input.txt").trim();

    let ips:Vec<IP> = input.lines().map(IP::new).collect();

    let mut tls_count = 0;
    for ip in ips.iter() {
        if ip.supports_tls() {
            tls_count += 1;
        }
    }

    let mut ssl_count = 0;
    for ip in ips.iter() {
        if ip.supports_ssl() {
            ssl_count += 1;
        }
    }

    println!("part1: {}", tls_count);
    println!("part2: {}", ssl_count);
}
