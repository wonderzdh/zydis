import re

def main():
    pat_encoding = re.compile('\{.+, .+, .+, \{ \d+, \d+, \d+ \}, .+, \{ (\.encoding = (.+)) \} \}')
    pat_reg_reg = re.compile('\{.+, .+, .+, \{ \d+, \d+, \d+ \}, .+, \{ (\.reg = \{ (.+), \{ \.reg = (.+) \} \}) \} \}')
    pat_reg_id = re.compile('\{.+, .+, .+, \{ \d+, \d+, \d+ \}, .+, \{ (\.reg = \{ (.+), \{ \.id = (.+) \} \}) \} \}')
    pat_mem = re.compile('\{.+, .+, .+, \{ \d+, \d+, \d+ \}, .+, \{ (\.mem = \{ (.+), (.+) \}) \} \}')

    with open ('OperandDefinitions.inc') as src, open('NewOperandDefinitions.inc', 'w') as dst:
        for line in src.readlines():
            if '{' not in line and '}' not in line:
                dst.write(line)
                continue

            m = pat_encoding.search(line)
            if m:
                # print(line)
                enc = m.group(2)
                expr = '{}'.format(enc)
                newline = line.replace(m.group(1), expr)
                dst.write(newline)
                continue
            m = pat_reg_reg.search(line)
            if m:
                # print(line)

                type = m.group(2)
                reg = m.group(3)
                expr = '{} << 8 | {}'.format(reg, type)
                newline = line.replace(m.group(1), expr)
                dst.write(newline)
                continue
            m = pat_reg_id.search(line)
            if m:
                # print(line)
                type = m.group(2)
                id = m.group(3)
                expr = '{} << 8 | {}'.format(id, type)
                newline = line.replace(m.group(1), expr)
                dst.write(newline)
                continue

            m = pat_mem.search(line)
            if m:
                # print(line)
                seg = m.group(2)
                base = m.group(3)
                expr = '{} << 3 | {}'.format(base, seg)
                newline = line.replace(m.group(1), expr)
                dst.write(newline)
                continue

            # print(line)
            dst.write(line)




if __name__ == '__main__':
    main()