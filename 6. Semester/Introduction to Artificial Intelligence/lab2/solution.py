import sys
import argparse


class Literal:
    def __init__(self, name, flag):
        self.name = name
        self.flag = flag  # True if negated (~)

    def __str__(self):
        return self.name

    def __eq__(self, other):
        return self.name == other.name and self.flag == other.flag

    def __hash__(self):
        return hash((self.name, int(self.flag)))


class Clause:
    def __init__(self):
        self.literals = set()
        self.parents = None

    def __str__(self):
        return " v ".join(
            [
                str(literal) if literal.flag == False else f"~{str(literal)}"
                for literal in self.literals
            ]
        )

    def add_to_set(self, literal):
        self.literals.add(literal)


def read_clause_list(path):
    with open(path, "r") as f:
        lines = f.read().splitlines()

    # remove comments and put everything in lowercase
    lines = [line.lower() for line in lines if not line.startswith("#")]

    return lines


######################################
############# RESOLUTION #############
######################################


def resolution(lines):
    # convert lines to clauses
    clauses, sos, goal_clause = convert_to_clauses(lines, "resolution")
    # apply deletion strategy
    clauses = deletion_strategy(clauses)
    new = []
    resolved_pairs = set()

    while True:
        # select clauses to resolve
        clause_pairs = selectClauses(clauses, sos, resolved_pairs)

        for clause_pair in clause_pairs:
            # resolve pair of clauses
            resolvents = resolve(clause_pair[0], clause_pair[1])

            # check if resolvents is empty => goal clause is true
            if len(resolvents.literals) == 0:
                clause = Clause()
                clause.add_to_set(Literal("NIL", False))
                clause.parents = resolvents.parents
                clauses.append(clause)
                print_results(True, clauses, goal_clause)
                return

            # if resolvents is not empty, add to new list and to resolved pairs
            new.append(resolvents)
            resolved_pairs.add(clause_pair)

        # apply deletion strategy
        new = deletion_strategy(new)

        # check if new clauses are subsets of existing clauses => goal clause is unknown
        if subset_check(new, clauses, sos):
            print_results(False, clauses, goal_clause)
            return

        clauses.extend(new)
        sos.extend(new)
        new = []


def convert_to_clauses(lines, algorithm):
    clauses = []  # initailize list of clauses
    sos = []  # initialize support set

    for line in lines:
        clause = Clause()  # initialize clause

        # split line into literals and remove whitespace
        temp = line.split(" v ")
        temp = [c.strip() for c in temp]  # remove whitespace

        # create literals and add to clause
        for cl in temp:
            lit = Literal(cl[1:], True) if cl.startswith(
                "~") else Literal(cl, False)
            clause.add_to_set(lit)

        clauses.append(clause)

    if algorithm == "resolution":
        goal_clause = clauses[-1]  # save goal clause

        # negate last clause and create new clause(s)
        for lit in clauses.pop().literals:
            lit.flag = not lit.flag
            new_clause = Clause()
            new_clause.add_to_set(lit)
            clauses.append(new_clause)
            sos.append(new_clause)

        return clauses, sos, goal_clause

    elif algorithm == "cooking":
        return clauses


def deletion_strategy(clauses):
    for clause in clauses:

        # tautology deletion, delete clause if it contains a literal and its negation
        deleted_flag = False
        for lit in clause.literals:
            if Literal(lit.name, not lit.flag) in clause.literals:
                clauses.remove(clause)
                deleted_flag = True
                break

        if deleted_flag:
            continue

        # subsumption deletion
        for other_clause in clauses:
            if clause != other_clause and clause.literals.issubset(other_clause.literals):
                clauses.remove(other_clause)

    return clauses


def selectClauses(clauses, sos, resolved_pairs):
    clause_pairs = []

    for clause in sos:
        for other_clause in clauses:

            # skip if clauses are the same
            if clause == other_clause:
                continue

            # skip if clauses have already been resolved
            if ((clause, other_clause) in resolved_pairs or (other_clause, clause) in resolved_pairs
                    or (clause, other_clause) in clause_pairs or (other_clause, clause) in clause_pairs):
                continue

            # check if clauses can be resolved
            for lit in clause.literals:
                if Literal(lit.name, not lit.flag) in other_clause.literals:
                    clause_pairs.append((other_clause, clause))

    return clause_pairs


def resolve(c1, c2):
    new_clause = Clause()
    new_clause.parents = (c1, c2)  # save parents

    # add literals to new clause
    for lit in c1.literals:
        new_clause.add_to_set(lit)

    for lit in c2.literals:
        new_clause.add_to_set(lit)

    # remove literals if they have negations in the same clause
    literals_to_remove = set()
    for lit in new_clause.literals:
        if Literal(lit.name, not lit.flag) in new_clause.literals:
            literals_to_remove.add(lit)
            literals_to_remove.add(Literal(lit.name, not lit.flag))

    for lit in literals_to_remove:
        new_clause.literals.remove(lit)

    return new_clause


def subset_check(new, clauses, sos):
    # if all clauses from new are in sos, then there is no new clauses and we can return True
    no_new_clauses = all(clause.literals in [
                         other_clause.literals for other_clause in sos] for clause in new)

    if no_new_clauses:
        return True

    # check if all new clauses are subsets of existing clauses
    return all(clause.literals.issubset(other_clause.literals) for clause in new for other_clause in clauses)


def print_results(found, clauses, goal_clause):
    # goal clause is unknown
    if not found:
        for lit in goal_clause.literals:
            lit.flag = not lit.flag

        print("[CONCLUSION]:", goal_clause, "is unknown")

    # goal clause is true
    else:
        path = [None] * len(clauses)
        parents_list = [clauses[-1].parents]

        path[clauses.index(clauses[-1])] = clauses[-1]

        while parents_list:
            parents = parents_list.pop()
            if parents is None:
                continue

            path[clauses.index(parents[0])] = parents[0]
            path[clauses.index(parents[1])] = parents[1]

            if parents[0].parents is not None:
                parents_list.append(parents[0].parents)

            if parents[1].parents is not None:
                parents_list.append(parents[1].parents)

        # remove None values from path
        path = [clause for clause in path if clause is not None]

        goal = True
        for i, clause in enumerate(path):
            if clause.parents is not None:
                if goal:
                    print("===============")
                    goal = False

                parent_index_1 = path.index(clause.parents[0]) + 1
                parent_index_2 = path.index(clause.parents[1]) + 1

                print(f"{i + 1}. {clause} ({parent_index_1}, {parent_index_2})")
            else:
                print(f"{i + 1}. {clause}")

        for lit in goal_clause.literals:
            lit.flag = not lit.flag

        print("===============")
        print("[CONCLUSION]:", goal_clause, "is true")


#######################################
########## COOKING ASSISTANT ##########
#######################################


def cooking_assistant(clause_path, user_commands_path):
    lines = print_knowledge_base(clause_path)

    # lines = read_clause_list(clause_path)

    user_lines = read_clause_list(user_commands_path)
    commands = convert_to_commands(user_lines)

    for command in commands:
        if command["action"] == "?":
            prompt(command["name"], lines)

        elif command["action"] == "+":
            lines = add_clause(command["name"], lines)
            print("Added " + command["name"] + "\n")

        elif command["action"] == "-":
            lines = remove_clause(command["name"], lines)
            print("Removed " + command["name"] + "\n")


def print_knowledge_base(clause_path):
    base_lines = read_clause_list(clause_path)
    print("Constructed with knowledge:")
    for line in base_lines:
        print(line)
    print()
    return base_lines


def convert_to_commands(user_lines):
    commands = []

    for line in user_lines:
        line = line.rsplit(" ", 1)
        command = {
            "name": line[0].strip(),
            "action": line[1].strip(),
        }
        commands.append(command)

    return commands


def prompt(goal_clause_name, lines):
    lines.append(goal_clause_name)
    print(f"User's command: {goal_clause_name} ?")
    resolution(lines)
    lines.remove(goal_clause_name)
    print()


def add_clause(clause_name, lines):
    print(f"User's command: {clause_name} +")
    # clause = convert_to_clauses(clause_name, "cooking")
    lines.append(clause_name)

    return lines


def remove_clause(clause_name, lines):
    print(f"User's command: {clause_name} -")
    lines.remove(clause_name)

    return lines


#######################################
############## MAIN ###################
#######################################

if __name__ == "__main__":
    # parse command line arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("algorith", choices=["resolution", "cooking"],
                        help="Type of algorithm to use")
    parser.add_argument("clause_path", help="Path to file with clauses")
    parser.add_argument("user_commands_path", nargs="?", default=None,
                        help="Path to file with user commands")

    args = parser.parse_args()

    if args.algorith == "resolution":
        lines = read_clause_list(args.clause_path)
        resolution(lines)
    elif args.algorith == "cooking":
        cooking_assistant(args.clause_path, args.user_commands_path)


# sources used:
# https://stackoverflow.com/questions/4945548/remove-the-first-character-of-a-string
# https://www.programiz.com/python-programming/methods/set/issubset
# https://linuxhint.com/inline-if-else-statement-python/
# https://www.geeksforgeeks.org/python-split-on-last-occurrence-of-delimiter/
