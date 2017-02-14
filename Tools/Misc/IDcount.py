count = {}
sum = 0
for w in open('trip_data_1_cab_ids.txt').read().split():
    if w in count:
        count[w] += 1
    else:
        count[w] = 1
for word, times in count.items():
    sum += 1
	#print ("%s was found %d times" % (word, times))
	
print(sum)