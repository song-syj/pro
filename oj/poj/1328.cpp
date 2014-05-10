#include<iostream>
#include<cmath>

using namespace std;

typedef struct point {
	double l;
	double r;
} Point;

Point pos[1005]; 


int partition(Point pos[], int start, int end)
{
	int i, j;
	Point r, tmp;
	
	i = start - 1;
	j = start;
	r = pos[end];

	for(j = start; j < end; j++)
		if(pos[j].l < r.l) {
			tmp = pos[i + 1];
			pos[i + 1] = pos[j];
			pos[j] = tmp;
			
			i++;
		}
	
	tmp = pos[i + 1];
	pos[i + 1] = pos[j];
	pos[j] = tmp;

	return i + 1;

}

void quicksort(Point pos[], int start, int end)
{
	int q;

	if(start >= end)
		return;
	
	q = partition(pos, start, end);
	quicksort(pos, start, q - 1);
	quicksort(pos, q + 1, end);
}

int radar_install(Point pos[], int n)
{
	int i;
	int size;
	double pr;
	
	quicksort(pos, 0, n - 1);
	//qsort(pos,n,sizeof(pos[0]),cmp);
	size = 1;
	pr = pos[0].r;
	for(i = 1; i < n; i++) {
		if(pos[i].l > pr) {
			pr = pos[i].r;
			size++;
		} else if(pos[i].r < pr) {
			pr = pos[i].r;
		}
	}

	return size;
}

int main()
{
	int n, d, min;
	int px, py;
	int num = 1;
	double xx;
	bool solution;
	
	
	while(cin>> n >> d) {
		if(n == 0 && d == 0)
			break;
		solution = true;
		
		for(int i = 0; i < n; i++) {
			cin >> px >> py;
			if(py > d || py < -d) {
				solution = false; // let the std input all data and no break
			} else {
				xx = sqrt((double)d * d - (double)py * py);
				pos[i].l = (double)px - xx;
				pos[i].r = (double)px + xx;
			}
				
		}
		

		if(solution)
			min = radar_install(pos, n);
		else
			min = -1;
		
			std::cout << "Case "
				 << num++
				 <<": "
				 << min
				 << endl;
	}	
	return 0;
}
