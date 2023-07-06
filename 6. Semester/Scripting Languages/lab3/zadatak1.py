import argparse


def writeMatrix(writefile, matrix):
    rows = matrix["rows"]
    cols = matrix["cols"]
    elements = matrix["elements"]

    with open(writefile, "w") as f:
        f.write(f"{rows} {cols}\n")

        for i, j in elements:
            if elements[(i, j)] != 0:
                f.write(f"{i} {j} {elements[(i, j)]:.2f}\n")


def printMatrix(name, matrix):
    rows = matrix["rows"]
    cols = matrix["cols"]
    elements = matrix["elements"]

    print(f"{name}:")
    for i in range(rows):
        for j in range(cols):
            print(f"  {elements.get((i, j), 0):5.2f}", end=" ")
        print()
    print()


def multiplyMatrices(matrixA, matrixB):
    rows_a = matrixA["rows"]
    cols_a = matrixA["cols"]
    elements_a = matrixA["elements"]
    rows_b = matrixB["rows"]
    cols_b = matrixB["cols"]
    elements_b = matrixB["elements"]

    if cols_a != rows_b:
        exit("Matrix dimensions do not match")

    result = {}

    for i in range(rows_a):
        for j in range(cols_b):
            result[(i, j)] = 0

            for k in range(cols_a):
                result[(i, j)] += elements_a.get((i, k), 0) * elements_b.get((k, j), 0)

    return {"rows": rows_a, "cols": cols_b, "elements": result}


def readMatrix(lines):
    if len(lines) < 2:
        exit("Not enough lines in file")

    if len(lines[0]) < 2:
        exit("Matrix dimensions are not defined")

    rows = int(lines[0][0])
    cols = int(lines[0][1])
    sparse = {}

    for line in lines[1:]:
        if len(line) != 3:
            exit("Invalid matrix element")

        row = int(line[0])
        col = int(line[1])
        value = float(line[2])

        if row >= rows or col >= cols:
            exit("Matrix element out of bounds")

        sparse[(row, col)] = value

    return {"rows": rows, "cols": cols, "elements": sparse}


def readFile(filepath):
    with open(filepath, "r") as f:
        lines = f.read().splitlines()

    return [line.split(" ") for line in lines]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("readfile", help="File to read from")
    parser.add_argument("writefile", help="File to write to")
    args = parser.parse_args()

    readfile = args.readfile
    writefile = args.writefile

    matrixA = {}
    matrixB = {}

    lines = readFile(readfile)

    emptyLineIndex = 0
    for i, line in enumerate(lines):
        if line[0] == "":
            emptyLineIndex = i
            break

    matrixA = readMatrix(lines[:emptyLineIndex])
    matrixB = readMatrix(lines[emptyLineIndex + 1 :])

    matrixC = multiplyMatrices(matrixA, matrixB)

    printMatrix("A", matrixA)
    printMatrix("B", matrixB)
    printMatrix("AxB", matrixC)

    writeMatrix(writefile, matrixC)


if __name__ == "__main__":
    main()
