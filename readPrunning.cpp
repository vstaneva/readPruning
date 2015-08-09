#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct read{
	string name;
	long long int start, end;
	int minCov, maxCov;
	bool immune, needchange, included;
	
};

vector<read> reads;
vector <int> positions(40000000);
read current;
long long int overcount, readNum = 1061903, minthreshold = 5, threshold=10;
int maxcovever;

void assignMinMaxImmunityChange(int readind){
	reads[readind].minCov = reads[readind].maxCov = positions[reads[readind].start];
	for (int i=reads[readind].start+1; i<reads[readind].end; i++){
		reads[readind].minCov = min(reads[readind].minCov, positions[i]);
		reads[readind].maxCov = max(reads[readind].maxCov, positions[i]);
		}
	if(reads[readind].minCov<=minthreshold) reads[readind].immune = 1;
	else reads[readind].immune = 0;
		
	if(reads[readind].maxCov>threshold) reads[readind].needchange = 1;
	else reads[readind].needchange = 0;
	}

int main(){

	for(int r = 0; r<readNum; r++){
		cin>>current.name>>current.start>>current.end;
		current.start--;
		current.end--;
		reads.push_back(current);
		for(int i=current.start; i<current.end; i++){
			positions[i]++;
			}
		}
	
	for(int r=0;r<readNum;r++){
		assignMinMaxImmunityChange(r);
		//maxcovever = max(maxcovever, reads[r].minCov);
		reads[r].included = 1; // initially all reads are included
		}
	//cout<<maxcovever<<endl;	
	for(int r=0;r<readNum;r++){
		//cout<<reads[r].minCov<<" * "<<reads[r].maxCov<<endl;
		if(!reads[r].needchange || reads[r].immune){
			//cout<<reads[r].minCov<<" "<<reads[r].maxCov<<endl;
			//cin.get();
			continue; //either too little coverage, or no need to prune
			}
		//we need to prune this read!
		reads[r].included = 0;
		overcount++;
		for(int i=reads[r].start; i<reads[r].end; i++) positions[i]--;
		//now, what does that mean for the next reads? 
		//take only the reads that overlap with reads[r]:
		for(int nr = r+1; (reads[nr].start<=reads[r].end && nr<readNum); nr++){ //all overlapping reads
			assignMinMaxImmunityChange(nr);
			}
		}
	//cout<<overcount<<endl;
	for(int i=0;i<readNum;i++){ //now output which reads are used
		cout<<reads[i].name<<" "<<reads[i].start+1<<" "<<reads[i].end+1<<" "<<reads[i].included<<endl;
	}
	//cout<<overcount<<" "<<reads[readNum-1].end<<"\n"<<(100*overcount)/reads[readNum-1].end<<endl;
	return 0;
	}