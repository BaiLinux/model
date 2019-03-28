#include"windows.h"
#include"model.h"

int main() {
	MODEL** MAP;
	MAP = new MODEL*[6];

	MAP[0] = new SIN();
	MAP[1] = new COS();
	MAP[2] = new ADD();
	MAP[3] = new SINF();
	MAP[4] = new SINF();
	MAP[5] = new SINK();

	connect(MAP[0], 0, MAP[2], 0);
	connect(MAP[1], 0, MAP[2], 1);
	connect(MAP[2], 0, MAP[3], 0);
	connect(MAP[3], 0, MAP[4], 0);
	connect(MAP[4], 0, MAP[5], 0);

	double t = 0;
	double dt = 0.01;

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 6; j++) {
			if (!MAP[j]->nin) {
				MAP[j]->RUN(t, dt);
			}
		}
		cout << t << '\t' << MAP[3]->out[0] << endl;
		t += dt;
	}

	Sleep(10000);
	return 0;
}