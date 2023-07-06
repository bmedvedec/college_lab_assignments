import os
import argparse
import re


def readStudentData(path):
    with open(path, "r", encoding="utf-8") as f:
        lines = f.read().splitlines()

    studentData = {}

    for line in lines:
        line = line.strip().split(" ")
        jmbag = line[0]
        prezime = line[1]
        ime = line[2]

        studentData[jmbag] = {
            "ime": ime,
            "prezime": prezime,
            "L1": "",
            "L2": "",
            "L3": "",
        }

    return studentData


def readLabData(data, folderpath, filename):
    regex = r"Lab_(\d+)_g\d+.txt"
    lab = int(re.findall(regex, filename)[0])

    with open(f"{folderpath}/{filename}", "r", encoding="utf-8") as f:
        lines = f.read().splitlines()

    for line in lines:
        line = line.strip().split(" ")
        jmbag = line[0]
        bodovi = line[1]

        if jmbag not in data:
            exit(f"Student {jmbag} ne postoji u datoteci studenti.txt")

        if data[jmbag][f"L{lab}"] != "":
            print(f"Student {jmbag} ima više rezultata za labos {lab}")

        data[jmbag][f"L{lab}"] = bodovi


def printResults(data):
    print(f"{'JMBAG':15}{'Prezime, Ime':25}{'L1':7}{'L2':7}{'L3':7}")

    for jmbag in data:
        student = data[jmbag]
        ime = student["ime"]
        prezime = student["prezime"]
        lab1 = student["L1"] if student["L1"] != "" else "-"
        lab2 = student["L2"] if student["L2"] != "" else "-"
        lab3 = student["L3"] if student["L3"] != "" else "-"

        prezime_ime = f"{prezime}, {ime}"

        print(f"{jmbag:15}{prezime_ime:25}{lab1:7}{lab2:7}{lab3:7}")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("folderpath", help="input file path")
    args = parser.parse_args()
    folderpath = args.folderpath

    data = readStudentData(os.path.join(folderpath, "studenti.txt"))

    for filename in os.listdir(folderpath):
        if filename == "studenti.txt":
            continue

        readLabData(data, folderpath, filename)

    printResults(data)


if __name__ == "__main__":
    main()
