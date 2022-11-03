import numpy as np
from itertools import combinations


def outputs(ssp_set):
    all_targets = set()
    for num_of_elements in range(1,len(ssp_set)+1):
        perm = combinations(ssp_set, num_of_elements)
        for options in perm:
            all_targets.add(sum(options))

    return all_targets

def makeSet(set_size, max_number):
    return np.random.randint(max_number, size=set_size)

def printTargets(targets):
    to_print = ""
    for target in targets:
        to_print += str(target)+ "\n"

    return to_print


def main():
    np.random.seed(seed=10)
    max_number = 5000
    for set_size in range(5,40):
        ssp_set= makeSet(set_size, max_number)
        targets = list(outputs(ssp_set))
        with open("/home/hershky1/outputs/set_size:_"+ str(set_size) +".txt", "w")as f:
            f.write(printTargets(targets))


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main()


