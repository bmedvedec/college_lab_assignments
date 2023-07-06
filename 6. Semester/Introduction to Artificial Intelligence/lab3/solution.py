import sys
import math
import argparse


class Node:
    def __init__(self, x, subtrees):
        self.x = x
        self.subtrees = subtrees

    def __repr__(self):
        return f"Node({self.x}, {self.subtrees})"


class Leaf:
    def __init__(self, value):
        self.value = value

    def __repr__(self):
        return f"Leaf({self.v})"


class ID3:
    def __init__(self):
        self.decision_tree = None

    def fit(self, train_dataset):
        header = train_dataset[0]
        train_dataset = train_dataset[1:]  # D

        X = header[:-1]  # attributes/features
        y = header[-1]  # target attribute/class label

        self.decision_tree = self.id3(train_dataset, train_dataset, X, y)

    def id3(self, D, D_parent, X, y):
        if len(D) == 0:
            return Leaf(self.most_common_value(D_parent))

        v = self.most_common_value(D)
        if len(X) == 0 or self.same_class(D):
            return Leaf(v)

        x = self.discriminating_attribute(D, X, y)
        subtrees = {}

        for value in [row[X.index(x)] for row in D]:
            x_index = X.index(x)
            D_v = self.examples_with_value(D, x_index, value)
            X.remove(x)
            subtree = self.id3(D_v, D, X, y)
            subtrees[value] = subtree

        return Node(x, subtrees)

    # funkcija za vraćanje najčešće vrijednosti ciljne varijable
    def most_common_value(self, Data):
        counter = {}

        for row in Data:
            value = row[-1]
            counter[value] = counter.get(value, 0) + 1

        return max(counter, key=counter.get)  # vraća ključ s najvećom vrijednošću

    # funkcija za provjeru jesu li sve vrijednosti ciljne varijable jednake,
    # tj. jesu li svi primjeri u čvoru iste klase
    def same_class(self, Data):
        values = {row[-1] for row in Data}
        return len(values) == 1

    # funkcija za vraćanje atributa koji najbolje diskriminira primjere
    def discriminating_attribute(self, D, X, y):
        best = None
        best_ig = -math.inf

        for x_index, x in enumerate(X):
            ig = self.information_gain(D, x, y, x_index)
            if ig > best_ig:
                best_ig = ig
                best = x

        print(f"BEST: {best}")
        return best

    def information_gain(self, D, x, y, x_index):
        value_counter = {}

        for row in D:
            value = row[x_index]
            target_attribute = row[-1]

            if value not in value_counter:
                value_counter[value] = {}

            if target_attribute not in value_counter[value]:
                value_counter[value][target_attribute] = 1
            else:
                value_counter[value][target_attribute] += 1

        print(f"VALUE_COUNTER: {value_counter}")

        E_X = {
            value: (
                self.entropy(target_attribute_counts),
                sum(target_attribute_counts.values()),
            )
            for value, target_attribute_counts in value_counter.items()
        }
        print(f"E_X: {E_X}")

        # entropy for the whole dataset
        temp = {}
        for target_attribute_counts in value_counter.values():
            for target_attribute, count in target_attribute_counts.items():
                temp[target_attribute] = temp.get(target_attribute, 0) + count

        # print(f"TEMP: {temp}")

        E_D = self.entropy(temp)

        print(f"E_D: {E_D}")

        # information gain
        n = len(D)

        ig = E_D - sum((E_X[value][1] / n) * E_X[value][0] for value in E_X)

        print(f"IG: {ig}")

        return ig

    def entropy(self, counter):
        n = sum(counter.values())

        return sum(-(number / n) * math.log2(number / n) for number in counter.values())

    # funkcija za vraćanje dataseta koji nemaju feature x
    def examples_with_value(self, D, x_index, value):
        # remove column x_index from D
        D = [row[:x_index] + row[x_index + 1 :] for row in D if row[x_index] == value]

        print(f"EXAMPLES WITH VALUE {value}:")
        for row in D:
            print(row)

        return D

    def predict(self, X):
        pass


def read_input(path):
    with open(path, "r") as f:
        lines = f.read().splitlines()

    return [line.split(",") for line in lines]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("train_dataset_path", help="Path to the training dataset")
    parser.add_argument("test_dataset_path", help="Path to the test dataset")
    parser.add_argument("depth", nargs="?", type=int, help="Depth of the tree")

    args = parser.parse_args()

    train_dataset_path = args.train_dataset_path
    test_dataset_path = args.test_dataset_path
    depth = args.depth

    train_dataset = read_input(train_dataset_path)
    test_dataset = read_input(test_dataset_path)

    model = ID3()
    model.fit(train_dataset)
    predictions = model.predict(test_dataset)


if __name__ == "__main__":
    main()
