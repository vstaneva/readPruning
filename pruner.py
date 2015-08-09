pr = open("positions.out", "r")
reads = open("NA12880-b37-chr21-sorted-vcfcovered.sam", "r")
outsam = open("prunned-NA12880-b37-chr21-vcfcov.sam", "w")

k=0

for prline in pr:
	pos = prline.split()
	if pos[3] == "0":
		continue
	samline = reads.readline()
	if samline =="":
		break
	if samline[0]=='@':
		outsam.write(samline)
		continue
	samrecord = samline.split()
	while not (samrecord[0]==pos[0] and int(samrecord[3])==int(int(pos[1])+9411192)):
		samline = reads.readline()
		if samline =="":
			break
		if samline[0]=='@':
			outsam.write(samline)
			continue
		samrecord = samline.split()
	if samline =="":
		break
	if samline[0]=='@':
		outsam.write(samline)
		continue
	if samrecord[0]==pos[0] and int(samrecord[3])==int(int(pos[1])+9411192):
		#this read record was left after the pruning! Huzzah!
		samrecord[0]=samrecord[0]+str(k)
		k = k+1
		samline = "\t".join(samrecord)+"\n"
		outsam.write(samline)
		#break
	
pr.close()
reads.close()
outsam.close()
		
