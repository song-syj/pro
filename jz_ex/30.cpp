void GetLeastNumbers(int* input, int n, int* output, int k)
{
	if(input == NULL || n <= 0 || output == NULL || k <=0 || k > n)
		return;
	
	int start = 0;
	int end = n-1;
	int index = Partition(input, start, end);

	while(index != k-1) {
		if(index > k - 1)
			end = index - 1;
		else
			start = index + 1;
		index = Partition(input, start, end);
	}

	for(int i = 0; i < k; i++)
		output[i] = input[i]
}

int Partiton(int data[], int start, int end)
{
	if(start == end)
		return start;

	int  index  = rand() % (end -start+1) + start;
	swap(data+end, start+index);
	int mid = data[end];
	int small = start - 1;	
	for(int i = start; i < end; i++) {
		if(data[i] < mid) {
			small++;
			swap(data+small, data+i);
		}
	}
	small++;
	swap(data+small, data+end);

	return small;
}


typedef multiset<int, greater<int> > intSet;
typedef multiset<int, greater<int> >:: iterator setInterator;

void GetLeastNumbers(const vector<int>& data, inSet& leastNumbers, int k)
{
	leastNumbers.clear();
	vecotr<int>::const_iterator iter = data.begin();
	for(; iter != data.begin()) {
		if(leastNumbers.size() < k)
			leastNumbers.inset(*iter);
		else {
			setInterator iterGreatest = leastNumbers.begin();

			if(*iter < * (iterGreatest)) {
				leastNumbers.erase(iterGreatest);
				leastNumbers.insert(*iter);
			}
		}
	}
}


