mod intcodevm_builder;
pub mod grid;

use std::collections::{HashMap, VecDeque};

use intcodevm_builder::IntCodeVMBuilder;

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
enum ParameterMode {
    Position,
    Immediate
}

impl From<char> for ParameterMode {
    fn from(value: char) -> Self {
        match value {
            '0' => Self::Position,
            '1' => Self::Immediate,
            _ => unimplemented!()
        }
    }
}

#[derive(Debug, PartialEq, Eq)]
struct Instruction {
    arg_modes: Vec<ParameterMode>,
    instruction: i64,
}

impl From<&str> for Instruction {
    fn from(value: &str) -> Self {
        let padded_instruction: Vec<char> = format!("{:05}", value.parse::<i64>().expect(&format!("failed parsing instruction: {}", value))).chars().collect();
        let arg_modes = padded_instruction[0..=2].iter().map(|c| (*c).into()).collect();

        let instruction = padded_instruction[3..].iter().collect::<String>().parse::<i64>().unwrap();

        return Instruction {
            arg_modes,
            instruction,
        };
    }
}

impl From<i64> for Instruction {
    fn from(value: i64) -> Self {
        let padded_instruction: Vec<char> = format!("{:05}", value).chars().collect();
        let arg_modes = padded_instruction[0..=2].iter().map(|c| (*c).into()).collect();

        let instruction = padded_instruction[3..].iter().collect::<String>().parse::<i64>().unwrap();

        return Instruction {
            arg_modes,
            instruction,
        };
    }
}

pub struct IntCodeVM {
    memory: HashMap<i64, i64>,
    pc: i64,
    input_queue: VecDeque<i64>,
    output_queue: VecDeque<i64>,
}

impl IntCodeVM {
    pub fn builder(raw_code: &str) -> IntCodeVMBuilder {
        return IntCodeVMBuilder::new_from_raw(raw_code);
    }

    pub fn execute(&mut self) {
        while self.step() {}
    }

    pub fn step(&mut self) -> bool {
        let instruction: Instruction = self.get_head_int().into();
        match instruction.instruction {
            1 => self.add(&instruction.arg_modes),
            2 => self.mult(&instruction.arg_modes),
            3 => self.input(&instruction.arg_modes),
            4 => self.output(&instruction.arg_modes),
            99 => return false,
            _ => unimplemented!()
        }
        return true;
    }

    pub fn get_head_int(&self) -> i64 {
        return self.get_int_at(self.pc);
    }

    pub fn get_int_at(&self, pos: i64) -> i64 {
        return *(self.memory.get(&pos).unwrap_or(&0));
    }

    fn set_int_at(&mut self, pos: i64, val: i64) {
        self.memory.insert(pos, val);
    }

    fn add(&mut self, arg_modes: &Vec<ParameterMode>) {
        let (from1, from2, to) = self.take_3_args();
        let arg1 = self.get_int_for_param(from1, arg_modes[2]);
        let arg2 = self.get_int_for_param(from2, arg_modes[1]);

        self.set_int_at(to, arg1 + arg2);
    }

    fn mult(&mut self, arg_modes: &Vec<ParameterMode>) {
        let (from1, from2, to) = self.take_3_args();
        let arg1 = self.get_int_for_param(from1, arg_modes[2]);
        let arg2 = self.get_int_for_param(from2, arg_modes[1]);

        self.set_int_at(to, arg1 * arg2);
    }

    fn input(&mut self, _arg_modes: &Vec<ParameterMode>) {
        let to = self.take_1_arg();
        let input_num = self.input_queue.pop_front().unwrap_or_default();
        self.set_int_at(to, input_num);
    }

    fn output(&mut self, arg_modes: &Vec<ParameterMode>) {
        let from = self.take_1_arg();
        let num = self.get_int_for_param(from, arg_modes[2]);
        self.output_queue.push_back(num);
    }

    fn take_3_args(&mut self) -> (i64, i64, i64) {
        let arg1 = self.get_int_at(self.pc+1);
        let arg2 = self.get_int_at(self.pc+2);
        let arg3 = self.get_int_at(self.pc+3);
        self.pc += 4;
        return (arg1, arg2, arg3);
    }

    fn take_1_arg(&mut self) -> i64 {
        let arg1 = self.get_int_at(self.pc+1);
        self.pc += 2;
        return arg1;
    }

    fn get_int_for_param(&self, param: i64, mode: ParameterMode) -> i64 {
        match mode {
            ParameterMode::Position => self.get_int_at(param),
            ParameterMode::Immediate => param,
        }
    }

    pub fn dump_mem(&self) {
        let mut output = String::new();
        for (_i, val) in self.memory.iter() {
            output.push_str(&format!("{}, ", *val))
        }
        println!("{}", output);
    }

    pub fn dump_state(&self) {
        let mut output = String::new();
        for (i, val) in self.memory.iter() {
            if self.pc == *i as i64 {
                output.push_str(&format!("[{}]: {} <--\n", i, val))
            } else {
                output.push_str(&format!("[{}]: {}\n", i, val))
            }
        }
        println!("{}", output);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn assert_finished_expected(start: Vec<i64>, expected: Vec<i64>) {
        let mut vm = IntCodeVMBuilder::new(IntCodeVMBuilder::mem_from_vec(start))
            .build();
        vm.execute();
        let mut expected_mem = HashMap::new();
        for (i, val) in expected.iter().enumerate() {
            expected_mem.insert(i as i64, *val);
        }
        if vm.memory != expected_mem {
            println!("Expected: {:?}", expected);
            println!("Actual:");
            vm.dump_state();
            panic!("vm memory did not match expected state.");
        }
    }

    #[test]
    fn d02_test_cases() {
        assert_finished_expected(
            vec![1,0,0,0,99],
            vec![2,0,0,0,99],
        );
        assert_finished_expected(
            vec![2,3,0,3,99],
            vec![2,3,0,6,99],
        );
        assert_finished_expected(
            vec![2,4,4,5,99,0],
            vec![2,4,4,5,99,9801],
        );
        assert_finished_expected(
            vec![1,1,1,4,99,5,6,0,99],
            vec![30,1,1,4,2,5,6,0,99],
        );
    }

    #[test]
    fn test_add() {
        assert_finished_expected(
            vec![1, 5, 6, 7, 99, 5, 10, 0],
            vec![1, 5, 6, 7, 99, 5, 10, 15],
        )
    }

    #[test]
    fn test_mult() {
        assert_finished_expected(
            vec![2, 5, 6, 7, 99, 5, 10, 0],
            vec![2, 5, 6, 7, 99, 5, 10, 50],
        )
    }

    #[test]
    fn test_immediate_param_mode() {
        assert_finished_expected(
            vec![1101, 10, 15, 5, 99],
            vec![1101, 10, 15, 5, 99, 25]);
    }

    #[test]
    fn test_input_output_queues() {
        let mut vm = IntCodeVM::builder("3,0,4,0,99")
            .with_input_queue(vec![42].into())
            .build();
        vm.execute();
        let expected: VecDeque<i64> = vec![42].into();
        assert_eq!(expected, vm.output_queue);
    }

    #[test]
    fn test_instruction_parser_from_str() {
        let cases = vec![
            ("1002", Instruction { arg_modes: vec![ParameterMode::Position, ParameterMode::Immediate, ParameterMode::Position], instruction: 2 }),
            ("1", Instruction { arg_modes: vec![ParameterMode::Position, ParameterMode::Position, ParameterMode::Position], instruction: 1 })
        ];

        for (input, expected) in cases {
            let result: Instruction = input.into();
            assert_eq!(expected, result);
        }
    }

    #[test]
    fn test_instruction_parser_from_i64() {
        let cases = vec![
            (1002, Instruction { arg_modes: vec![ParameterMode::Position, ParameterMode::Immediate, ParameterMode::Position], instruction: 2 }),
            (1, Instruction { arg_modes: vec![ParameterMode::Position, ParameterMode::Position, ParameterMode::Position], instruction: 1 })
        ];

        for (input, expected) in cases {
            let result: Instruction = input.into();
            assert_eq!(expected, result);
        }
    }

}
