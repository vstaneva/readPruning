import bisect

vcfpr = open("vcfpositions.in", "r")
reads = open("NA12880-b37-chr21-sorted.sam", "r")
outsam = open("NA12880-b37-chr21-sorted-vcfcovered.sam", "w")

vcfposlist = [int(x.strip('\n')) for x in vcfpr.readlines()] #this is amazing. hope it works

for read in reads: #1.read start position; 2. look it up in vcfposlist 3. see if the next vcf snp is covered by the read
	 if read[0]=='@': #header
	 	outsam.write(read)
	 	continue
	 readinfo = read.split()
	 readstart = int(readinfo[3])
	 #print readstart,
	 readend = readstart+1000
	 
	 #how to binary search?
	 ind = bisect.bisect_left(vcfposlist, readstart)
	 if ind+1 >= len(vcfposlist):
		continue
	 #print ind, vcfposlist[ind], vcfposlist[ind+1], readend, (readend>=vcfposlist[ind+1])
	 if readend>vcfposlist[ind+1]:
		#print "*"
	 	outsam.write(read)
	
vcfpr.close()
reads.close()
outsam.close()
		
