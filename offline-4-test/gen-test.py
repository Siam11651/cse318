import sys
import random

dataset_file = open(sys.argv[1])
lines = dataset_file.readlines()

dataset_file.close()

lines_count = len(lines)
learn_partition_size = int(lines_count * 0.8)

random.shuffle(lines)
learn_file = open("learn.dat", mode='w')
test_file = open("test.dat", mode='w')

for i in range(0, learn_partition_size):
    learn_file.write(lines[i])

for i in range(learn_partition_size, lines_count):
    test_file.write(lines[i])

learn_file.close()
test_file.close()