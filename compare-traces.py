# compare_traces.py

truth_path = "./program/nestest.log"
trace_path = "./trace/trace.log"

split_lines_trace = 2

RED = "\033[31m"
RESET = "\033[0m"

def compare_traces(truth_path, trace_path):

    truth = open(truth_path, "r")
    trace = open(trace_path, "r")

    for _ in range(split_lines_trace):
        trace.readline()

    line_num = 1
    while True:
        truth_line = truth.readline()
        trace_line = trace.readline()

        if not truth_line or not trace_line:
            break

        truth_line = truth_line.rstrip("\n")
        trace_line = trace_line.rstrip("\n")

        # Slices: compare first 19 chars, skip next 29, compare next 25
        slices = [(0, 19), (48, 73)]
        line_display = ""

        max_len = min(len(truth_line), len(trace_line))
        for i in range(max_len):
            if i in range(19, 48):
                line_display += truth_line[i]
                continue

            if truth_line[i] == trace_line[i]:
                line_display += truth_line[i]
                continue

            line_display += f"{RED}{trace_line[i]}{RESET}"

        print(f"{line_num:3}: {line_display}")
        line_num += 1

if __name__ == "__main__":
    compare_traces(truth_path, trace_path)
