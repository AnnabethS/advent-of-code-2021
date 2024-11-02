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
            5 => self.jump_if_true(&instruction.arg_modes),
            6 => self.jump_if_false(&instruction.arg_modes),
            7 => self.less_than(&instruction.arg_modes),
            8 => self.equals(&instruction.arg_modes),
            99 => return false,
            _ => {
                println!("Reached An Unknown Instruction ({})!", instruction.instruction);
                self.dump_state();
                unimplemented!();
            }
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

    fn jump_if_true(&mut self, arg_modes: &Vec<ParameterMode>) {
        let (arg, arg2) = self.peek_2_args();
        let cmp_num = self.get_int_for_param(arg, arg_modes[2]);
        let to_num = self.get_int_for_param(arg2, arg_modes[1]);
        if cmp_num != 0 {
            self.pc = to_num;
        } else {
            self.pc += 3;
        }
    }

    fn jump_if_false(&mut self, arg_modes: &Vec<ParameterMode>) {
        let (arg, arg2) = self.peek_2_args();
        let cmp_num = self.get_int_for_param(arg, arg_modes[2]);
        let to_num = self.get_int_for_param(arg2, arg_modes[1]);
        if cmp_num == 0 {
            self.pc = to_num;
        } else {
            self.pc += 3;
        }
    }

    fn less_than(&mut self, arg_modes: &Vec<ParameterMode>) {
        let (arg, arg2, arg3) = self.take_3_args();
        let cmp_1_num = self.get_int_for_param(arg, arg_modes[2]);
        let cmp_2_num = self.get_int_for_param(arg2, arg_modes[1]);
        if cmp_1_num < cmp_2_num {
            self.set_int_at(arg3, 1);
        } else {
            self.set_int_at(arg3, 0);
        }

    }

    fn equals(&mut self, arg_modes: &Vec<ParameterMode>) {
        let (arg, arg2, arg3) = self.take_3_args();
        let cmp_1_num = self.get_int_for_param(arg, arg_modes[2]);
        let cmp_2_num = self.get_int_for_param(arg2, arg_modes[1]);
        if cmp_1_num == cmp_2_num {
            self.set_int_at(arg3, 1);
        } else {
            self.set_int_at(arg3, 0);
        }
    }


    fn peek_3_args(&mut self) -> (i64, i64, i64) {
        let arg1 = self.get_int_at(self.pc+1);
        let arg2 = self.get_int_at(self.pc+2);
        let arg3 = self.get_int_at(self.pc+3);
        return (arg1, arg2, arg3);
    }

    fn peek_2_args(&mut self) -> (i64, i64) {
        let arg1 = self.get_int_at(self.pc+1);
        let arg2 = self.get_int_at(self.pc+2);
        return (arg1, arg2);
    }

    fn peek_1_arg(&mut self) -> i64 {
        let arg1 = self.get_int_at(self.pc+1);
        return arg1;
    }

    fn take_3_args(&mut self) -> (i64, i64, i64) {
        let arg1 = self.get_int_at(self.pc+1);
        let arg2 = self.get_int_at(self.pc+2);
        let arg3 = self.get_int_at(self.pc+3);
        self.pc += 4;
        return (arg1, arg2, arg3);
    }

    fn take_2_args(&mut self) -> (i64, i64) {
        let arg1 = self.get_int_at(self.pc+1);
        let arg2 = self.get_int_at(self.pc+2);
        self.pc += 3;
        return (arg1, arg2);
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
        let mut vec_mem: Vec<(i64, i64)> = self.memory.clone().iter()
            .map(|(i, val)| (*i, *val))
            .collect();
        vec_mem.sort_by(|a, b| (*a).0.cmp(&b.0));
        for (i, val) in vec_mem.iter() {
            if self.pc == *i as i64 {
                output.push_str(&format!("[{}]: {} <--\n", i, val))
            } else {
                output.push_str(&format!("[{}]: {}\n", i, val))
            }
        }
        println!("{}", output);
        println!("pc: {}", self.pc);
        println!("input queue: {:?}", self.input_queue);
        println!("output queue: {:?}", self.output_queue);
    }

    pub fn dump_output_queue(&self) {
        let mut queue_clone = self.output_queue.clone();
        while let Some(out) = queue_clone.pop_front() {
            println!("{}", out);
        }
    }

    pub fn get_last_output (&self) -> Option<i64> {
        return self.output_queue.back().copied();
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

    fn assert_expected_output(code: &Vec<i64>, input: Vec<i64>, expected_output: Vec<i64>) {
        let mut vm = IntCodeVMBuilder::new(IntCodeVMBuilder::mem_from_vec(code.to_vec()))
            .with_input_queue(input.into())
            .build();
        vm.execute();

        let output_queue: Vec<i64> = vm.output_queue.clone().into();

        if output_queue != expected_output {
            println!("Expected: {:?}", expected_output);
            println!("Got: {:?}", output_queue);
            println!("VM State:");
            vm.dump_state();
            panic!("Output Queue did not match expected Output Queue.");
        }
        assert_eq!(expected_output, output_queue)
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

    #[test]
    fn test_comparisons() {
       let is_equal_to_8_pos_code = vec![3,9,8,9,10,9,4,9,99,-1,8];
       let is_lt_8_pos_code = vec![3,9,7,9,10,9,4,9,99,-1,8];

       let is_equal_to_8_im_code = vec![3,3,1108,-1,8,3,4,3,99];
       let is_lt_8_im_code = vec![3,3,1107,-1,8,3,4,3,99];

       assert_expected_output(&is_equal_to_8_pos_code, vec![8], vec![1]);
       assert_expected_output(&is_equal_to_8_pos_code, vec![3], vec![0]);

       assert_expected_output(&is_lt_8_pos_code, vec![7], vec![1]);
       assert_expected_output(&is_lt_8_pos_code, vec![9], vec![0]);

       assert_expected_output(&is_equal_to_8_im_code, vec![8], vec![1]);
       assert_expected_output(&is_equal_to_8_im_code, vec![3], vec![0]);

       assert_expected_output(&is_lt_8_im_code, vec![7], vec![1]);
       assert_expected_output(&is_lt_8_im_code, vec![9], vec![0]);
    }

    #[test]
    fn test_jumps() {
        let pos_jump_code = vec![3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9];
        let im_jump_code = vec![3,3,1105,-1,9,1101,0,0,12,4,12,99,1];

        assert_expected_output(&pos_jump_code, vec![10], vec![1]);
        assert_expected_output(&im_jump_code, vec![0], vec![0]);
    }

    #[test]
    fn test_jump_comparisons() {
        let code = vec![3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,
                        1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,
                        999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99];
        assert_expected_output(&code, vec![7], vec![999]);
        assert_expected_output(&code, vec![8], vec![1000]);
        assert_expected_output(&code, vec![9], vec![1001]);
    }
}
