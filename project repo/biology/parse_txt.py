DIAGONAL = 2 ** (1 / 2)
NUM_OF_AGENTS = 1
ENERGY_PER_UNIT = 2.5*10**(-14)
ENERGY_PER_UNIT = 1

def parse_txt_file(path):

    all_averages = []
    results = []
    with open(path) as f:
        for output in f.readlines():
            results.append(int(output))
        return calculate_avg(results, results[-1])



def calculate_avg(outputs, depth):
    ssp_sum = 0
    for output in outputs:
        ssp_sum += output * DIAGONAL + depth - output
    return ssp_sum/len(outputs)

def main():
	with open ("/home/hershky1/bio_energy/energy.txt","a")as f:
		for i in range(5,37):
		    all_averages = parse_txt_file("/home/hershky1/outputs/set_size:_" + str(i) +".txt")
		    f.write("set size "+ str(i)+ " " + str(all_averages)+ "\n")
		    f.flush()

if __name__ == "__main__":
    main()


