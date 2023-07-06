import argparse


def print_table(table):
    for row in table:
        print("#".join(str(x) for x in row))


def table(lines):
    rowLength = len(lines[0])
    q = int(0.1 * rowLength)

    row = ["Hyp"]
    for i in range(q, rowLength, int(0.1 * rowLength)):
        row.append(f"Q{i:02d}")

    table = [row]

    for i, line in enumerate(lines):
        row = [f"{i+1:03d}"]
        line.sort()

        for j in range(q, rowLength, int(0.1 * rowLength)):
            hd = float(line[j - 1])
            row.append(f"{hd:.1f}")

        table.append(row)

    print_table(table)


def readFile(filepath):
    with open(filepath, "r") as f:
        lines = f.read().splitlines()

    return [line.strip().split(" ") for line in lines]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("filepath", help="input file path")
    args = parser.parse_args()

    lines = readFile(args.filepath)

    table(lines)


if __name__ == "__main__":
    main()
