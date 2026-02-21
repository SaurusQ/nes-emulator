import argparse

truth_path = "./program/nestest.log"
trace_path = "./trace/trace.log"

skip_trace_lines_start = 2

RED = "\033[31m"
RESET = "\033[0m"

def compare_traces(truth_path, trace_path, skip_lines, limit):

    truth = open(truth_path, "r")
    trace = open(trace_path, "r")

    for _ in range(skip_trace_lines_start):
        trace.readline()

    line_num = 1
    start_diff = False
    first_diff = True
    previous_line = None
    while limit != 0:
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

            start_diff = True
            line_display += f"{RED}{trace_line[i]}{RESET}"

        line = f"{line_num:3}: {line_display}"
        if start_diff or not skip_lines:
            if first_diff and skip_lines:
                print(previous_line)
                first_diff = False
            print(line)
            limit -= 1
        previous_line = line
        line_num += 1

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Compare two NES .log trace files")
    parser.add_argument(
        "truth",
        nargs="?",
        default=truth_path,
        help="Path to original .log file",
    )
    parser.add_argument(
        "trace",
        nargs="?",
        default=trace_path,
        help="Path to trace file",
    )
    parser.add_argument(
        "-s", "--skip-lines", action="store_true",
        help="Skip lines before first diff"
    )

    parser.add_argument(
        "-l", "--limit", type=int, default=-1,
        help="Limit number of lines after fist diff"
    )

    args = parser.parse_args()
    compare_traces(args.truth, args.trace, args.skip_lines, args.limit)
