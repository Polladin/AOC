import copy


class CommandInfo:

    def __init__(self, cmd_name, regs):

        self.name = cmd_name
        self.regs = regs

    def __str__(self):

        # str_to_print = '-' * 20 + '\n'
        str_to_print = self.name + ' ' + str(self.regs)

        return str_to_print


class CommandProcessor:

    OP_CODE = 0
    REG_A = 0
    REG_B = 1
    REG_C = 2

    ALL_COMMANDS = ['addr', 'addi', 'mulr', 'muli', 'banr', 'bani', 'borr', 'bori', 'setr', 'seti',
                    'gtir', 'gtri', 'gtrr', 'eqir', 'eqri', 'eqrr']

    @staticmethod
    def is_registers(regs):
        return any([_reg >= 4 for _reg in regs])

    @staticmethod
    def check_registers_value(command_name, cmd):

        registers = [CommandProcessor.REG_A, CommandProcessor.REG_B, CommandProcessor.REG_C] \
                    if command_name[-1] == 'r' else [CommandProcessor.REG_A, CommandProcessor.REG_C]

        for _reg in registers:
            if cmd[_reg] >= 6:
                return False

        return True

    @staticmethod
    def cmd_result(command_name, mem_info, reg_a, reg_b):

        # ADD
        if command_name == 'addr':
            return mem_info[reg_a] + mem_info[reg_b]
        if command_name == 'addi':
            return mem_info[reg_a] + reg_b
        # MUL
        if command_name == 'mulr':
            return mem_info[reg_a] * mem_info[reg_b]
        if command_name == 'muli':
            return mem_info[reg_a] * reg_b

        # BAND
        if command_name == 'banr':
            return mem_info[reg_a] & mem_info[reg_b]
        if command_name == 'bani':
            return mem_info[reg_a] & reg_b

        # BOR
        if command_name == 'borr':
            return mem_info[reg_a] | mem_info[reg_b]
        if command_name == 'bori':
            return mem_info[reg_a] | reg_b

        # SET
        if command_name == 'setr':
            return mem_info[reg_a]
        if command_name == 'seti':
            return reg_a

        # Greater-than testing
        if command_name == 'gtir':
            return 1 if reg_a > mem_info[reg_b] else 0
        if command_name == 'gtri':
            return 1 if mem_info[reg_a] > reg_b else 0
        if command_name == 'gtrr':
            return 1 if mem_info[reg_a] > mem_info[reg_b] else 0

        # Equality testing:
        if command_name == 'eqir':
            return 1 if reg_a == mem_info[reg_b] else 0
        if command_name == 'eqri':
            return 1 if mem_info[reg_a] == reg_b else 0
        if command_name == 'eqrr':
            return 1 if mem_info[reg_a] == mem_info[reg_b] else 0

    @staticmethod
    def try_command(command_info, command_name):

        # Register = [A, B, C]
        reg_a_val = command_info.cmd[CommandProcessor.REG_A]
        reg_b_val = command_info.cmd[CommandProcessor.REG_B]
        reg_c_val = command_info.cmd[CommandProcessor.REG_C]

        # All registers should be less than memory size
        if not CommandProcessor.check_registers_value(command_name, command_info.cmd):
            return

        # Memory = [...]
        mem_info = copy.deepcopy(command_info.before)

        # Execute command
        mem_info[reg_c_val] = CommandProcessor.cmd_result(command_name, mem_info, reg_a_val, reg_b_val)

        return mem_info == command_info.after

    @staticmethod
    def run_command(command_name, cmd, mem_info):

        # Register = [A, B, C]
        reg_a_val = cmd[CommandProcessor.REG_A]
        reg_b_val = cmd[CommandProcessor.REG_B]
        reg_c_val = cmd[CommandProcessor.REG_C]

        # # All registers should be less than memory size
        # if not CommandProcessor.check_registers_value(command_name, cmd):
        #     return False

        # Execute command
        mem_info[reg_c_val] = CommandProcessor.cmd_result(command_name, mem_info, reg_a_val, reg_b_val)

        return True

