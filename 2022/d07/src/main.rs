use petgraph::stable_graph::StableGraph;
use petgraph::dot::{Dot, Config};

#[derive(Debug, PartialEq, Eq)]
enum FSItemType {
    DIRECTORY,
    FILE,
}

#[derive(Debug)]
struct FSItem {
    fs_type: FSItemType,
    name: String,
    size: u32
}

impl std::fmt::Display for FSItem {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self.fs_type {
            FSItemType::DIRECTORY => f.write_str(&format!("DIR {}: size {}", self.name, self.size)),
            FSItemType::FILE => f.write_str(&format!("FILE {}: size {}", self.name, self.size)),
        }
    }
}

impl FSItem {
    fn new(fs_type: FSItemType, name: String, size: u32) -> Self {
        Self { fs_type, name, size }
    }
}

fn main() {
    // let input = include_str!("example.txt").trim();
    let input = include_str!("input.txt").trim();

    let mut g:StableGraph<FSItem, u8> = StableGraph::new();
    let root_idx = g.add_node(FSItem::new(FSItemType::DIRECTORY, "/".to_string(), 0));

    let instructions:Vec<_> = input.split("\n$").skip(1).map(|s| s.trim()).collect();

    let mut current_node_idx = root_idx;

    for ins in instructions {
        if &ins.trim()[0..2] == "ls"{
            for fsi in ins.lines().skip(1) {
                println!("{}", fsi);
                let (info, name) = fsi.split_once(' ').unwrap();
                if info.trim() == "dir" {
                    let idx = g.add_node(FSItem::new(FSItemType::DIRECTORY, name.trim().to_string(), 0));
                    g.add_edge(current_node_idx, idx, 0);
                } else {
                    let idx = g.add_node(FSItem::new(FSItemType::FILE, name.trim().to_string(), info.trim().parse().unwrap()));
                    g.add_edge(current_node_idx, idx, 0);
                }
            }
        }
        else {
            println!("cd");
            let goal_dir = ins.split_once(' ').unwrap().1.trim();
            if goal_dir == ".." {
                // 0 size to represent not yet calculated
                current_node_idx = g.neighbors_directed(current_node_idx, petgraph::Direction::Incoming).nth(0).unwrap();
            } else {
                let mut children = g.neighbors_directed(current_node_idx, petgraph::Direction::Outgoing);
                current_node_idx = children.find(|x| &g[*x].name == goal_dir).unwrap();
            }
        }
    }

    current_node_idx = root_idx;

    while g[root_idx].size == 0 {
        let children:Vec<_> = g
            .neighbors_directed(current_node_idx, petgraph::Direction::Outgoing)
            .collect();

        let subdirs:Vec<_> = children.iter()
            .filter(|idx| g[**idx].fs_type == FSItemType::DIRECTORY)
            .collect();
        if subdirs.iter().all(|idx| g[**idx].size != 0) {
            // all subdirectories are calculated, we can calcuate du of this one
            g[current_node_idx].size = children.iter().fold(0, |a, b| a + g[*b].size);
            if g[current_node_idx].name == "/" {
                break;
            }
            current_node_idx = g.neighbors_directed(current_node_idx, petgraph::Direction::Incoming).nth(0).unwrap();
        } else {
            current_node_idx = **subdirs.iter().find(|idx| g[***idx].size == 0).unwrap();
        }
    }

    // tree is now walked and calculated

    println!("{}", Dot::with_config(&g, &[Config::EdgeNoLabel]));
    std::fs::write("file_structure.dot", format!("{}", Dot::with_config(&g, &[Config::EdgeNoLabel]))).expect("aaah");

    // walk all directories, throw out any with > 100000 size, sum the rest
    let part1 = g.node_weights()
        .filter(|node| node.fs_type == FSItemType::DIRECTORY && node.size < 100000)
        .fold(0, |total, node| total + node.size);

    println!("part 1: {}", part1);

    let disk_space = 70000000;
    let free_space_required = 30000000;
    let current_used = g[root_idx].size;
    let current_unused = disk_space - current_used;
    let delete_amount = free_space_required - current_unused;

    println!("current used: {}", current_used);
    println!("current unused: {}", current_unused);
    println!("deletion required: {}", delete_amount);

    let part2 = g.node_weights()
        .filter(|node| node.fs_type == FSItemType::DIRECTORY && node.size > delete_amount)
        .min_by(|a, b| a.size.cmp(&b.size)).unwrap().size;

    println!("part 2: {}", part2);

}
