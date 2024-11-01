use std::collections::{HashMap, VecDeque};

use crate::IntCodeVM;

pub struct IntCodeVMBuilder {
    memory: HashMap<i64, i64>,
    pc: Option<i64>,
    input_queue: Option<VecDeque<i64>>
}

impl IntCodeVMBuilder {
    pub fn new_from_raw(raw: &str) -> IntCodeVMBuilder {
        Self::new(Self::parse_mem(raw))
    }

    pub fn new(memory: HashMap<i64, i64>) -> IntCodeVMBuilder {
        IntCodeVMBuilder {
            memory,
            pc: None,
            input_queue: None
        }
    }

    pub fn set_pc(mut self, pc: i64) -> Self {
        self.pc = Some(pc);
        return self;
    }

    pub fn set_mem_pos(mut self, pos: i64, value: i64) -> Self {
        self.memory.insert(pos, value);
        return self;
    }

    pub fn with_input_queue(mut self, queue: VecDeque<i64>) -> Self {
        self.input_queue = Some(queue);
        return self;
    }

    fn parse_mem(raw: &str) -> HashMap<i64, i64> {
        let memory = raw
            .split(',')
            .map(|num| num.trim().parse::<i64>().expect(&format!("failed parsing {:?}", num)))
            .collect();
        return Self::mem_from_vec(memory);
    }

    pub fn build(self) -> IntCodeVM {
        IntCodeVM {
            memory: self.memory,
            pc: self.pc.unwrap_or(0),
            input_queue: self.input_queue.unwrap_or_default(),
            output_queue: VecDeque::default()
        }
    }

    pub fn mem_from_vec(mem_vec: Vec<i64>) -> HashMap<i64, i64> {
        mem_vec.iter()
            .enumerate()
            .map(|(i, val)| (i as i64, *val))
            .collect()
    }
}
