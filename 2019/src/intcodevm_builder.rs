use crate::IntCodeVM;

pub struct IntCodeVMBuilder {
    memory: Vec<i64>,
    pc: Option<usize>,
}

impl IntCodeVMBuilder {
    pub fn new_from_raw(raw: &str) -> IntCodeVMBuilder {
        Self::new(Self::parse_mem(raw))
    }

    pub fn new(memory: Vec<i64>) -> IntCodeVMBuilder {
        IntCodeVMBuilder {
            memory,
            pc: None
        }
    }

    pub fn set_pc(mut self, pc: usize) -> Self {
        self.pc = Some(pc);
        return self;
    }

    pub fn set_mem_pos(mut self, pos: usize, value: i64) -> Self {
        let len = self.memory.len();
        if len < pos {
            for _i in len..=pos {
                self.memory.push(0);
            }
        }
        self.memory[pos] = value;
        return self;
    }

    fn parse_mem(raw: &str) -> Vec<i64> {
        let memory = raw
            .split(',')
            .map(|num| num.trim().parse().expect(&format!("failed parsing {:?}", num)))
            .collect();
        return memory;
    }

    pub fn build(self) -> IntCodeVM {
        IntCodeVM {
            memory: self.memory,
            pc: self.pc.unwrap_or(0),
        }
    }
}
