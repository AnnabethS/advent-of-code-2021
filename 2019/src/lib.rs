use intcodevm_builder::IntCodeVMBuilder;

mod intcodevm_builder;

pub struct IntCodeVM {
    memory: Vec<i64>,
    pc: usize,
}

impl IntCodeVM {
    pub fn builder(raw_code: &str) -> IntCodeVMBuilder {
        return IntCodeVMBuilder::new_from_raw(raw_code);
    }

    pub fn execute(&mut self) {
        while self.step() {}
    }

    pub fn step(&mut self) -> bool {
        let opcode = self.get_head_int();
        match opcode {
            1 => self.add(),
            2 => self.mult(),
            99 => return false,
            _ => unimplemented!()
        }
        return true;
    }

    pub fn get_head_int(&self) -> i64 {
        return self.get_int_at(self.pc);
    }

    pub fn get_int_at(&self, pos: usize) -> i64 {
        return *(self.memory.get(pos).unwrap_or(&0));
    }

    fn set_int_at(&mut self, pos: usize, val: i64) {
        let len = self.memory.len();
        if len < pos {
            for _i in len..=pos {
                self.memory.push(0);
            }
        }
        self.memory[pos] = val;
    }

    fn add(&mut self) {
        let (from1, from2, to) = self.take_3_args();
        let int1 = self.get_int_at(from1 as usize);
        let int2 = self.get_int_at(from2 as usize);

        self.set_int_at(to as usize, int1 + int2);
    }

    fn mult(&mut self) {
        let (from1, from2, to) = self.take_3_args();
        let int1 = self.get_int_at(from1 as usize);
        let int2 = self.get_int_at(from2 as usize);

        self.set_int_at(to as usize, int1 * int2);
    }

    fn take_3_args(&mut self) -> (i64, i64, i64) {
        let arg1 = self.get_int_at(self.pc+1);
        let arg2 = self.get_int_at(self.pc+2);
        let arg3 = self.get_int_at(self.pc+3);
        self.pc += 4;
        return (arg1, arg2, arg3);
    }

    pub fn dump_mem(&self) {
        let mut output = String::new();
        for i in self.memory.iter() {
            output.push_str(&format!("{}, ", *i as usize))
        }
        println!("{}", output);
    }

    pub fn dump_state(&self) {
        let mut output = String::new();
        for (i, val) in self.memory.iter().enumerate() {
            if self.pc == i {
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
        let mut vm = IntCodeVMBuilder::new(start)
            .build();
        vm.execute();
        if vm.memory != expected {
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

}
