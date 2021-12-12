import pickle

o3file = open("tests_O3_times.pkl", "rb")
brutefile = open("tests_bruteforce_times.pkl", "rb")

o3runtimes = pickle.load(o3file)

brutedata = pickle.load(brutefile)
bruteruntimes = brutedata["opt_runtimes"]
brutefactors = brutedata["opt_factors"]

product = 1

print("file, o3runtime, bruteruntime, speedup, vf, if")

for o3filename in o3runtimes: # other is 'opt_factors'
	o3runtime = o3runtimes[o3filename]
	filename = o3filename.split('/')[-1]

	brutefilename = "./new_rollout_garbage_22233/" + filename

	bruteruntime = bruteruntimes[brutefilename]
	brutefactor = brutefactors[brutefilename]
	speedup = o3runtime / float(bruteruntime)

	product *= speedup

	print(", ".join([filename, str(o3runtime), str(bruteruntime), str(speedup), str(brutefactor[0]), str(brutefactor[1])]))# + str(o3runtime) + ", brute=" + str(bruteruntime) + ", speedup=" + str(speedup) + "x @ VF/IF=" + str(brutefactor))

print("Number of files: " + str(len(o3runtimes)))

geomean = product**(1/float(len(o3runtimes)))

print("Geomean speedup = " + str(geomean) + "x")
