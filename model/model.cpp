#include"windows.h"
#include"model.h"

void solve(MODEL** MAP, int n, double start, double end, double step) {

	for (double t = start; t<=end; t+=step) {
		for (int j = 0; j < n; j++) {
			if (!MAP[j]->nin) {
				MAP[j]->RUN(t, step);
			}
		}
	}

}



int main() {

	MODEL** MAP;
	MAP = new MODEL*[100];
	int n = 8;
	MAP[0] = new SIN();
	MAP[1] = new COS();
	MAP[2] = new ADD();
	MAP[3] = new SINF();
	MAP[4] = new SINF();
	MAP[5] = new SINK();
	MAP[6] = new ADD();
	MAP[7] = new SIN();

	connect(MAP[0], 0, MAP[2], 0);
	connect(MAP[6], 0, MAP[2], 1);
	connect(MAP[1], 0, MAP[6], 0);
	connect(MAP[7], 0, MAP[6], 1);
	connect(MAP[2], 0, MAP[3], 0);
	connect(MAP[3], 0, MAP[4], 0);
	connect(MAP[4], 0, MAP[5], 0);


	solve(MAP, n, 0, 1, 0.01);


	for (int i = 0; i < n; i++)	{
		delete[]MAP[i];
	}
	delete[]MAP;

	Sleep(10000);
	return 0;
}