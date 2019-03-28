#pragma once
#include"math.h"
#include<iostream>
#include<fstream>

using namespace std;
class MODEL {
public:
	MODEL() {
		for (int i = 0; i < nin; i++)
			in[i] = NULL;
	};
	MODEL(double* par) {
		this->par = par;
		for (int i = 0; i < nin; i++)
			in[i] = NULL;
	};

	int nin = 0, nout = 0, npar = 0;
	double *in, *out, *par;
	MODEL *(*outModel), *(*inModel);
	int *NIN, *NOUT;

	virtual void RUN(double t, double dt) {
		for (int i = 0; i < nout; i++) {
			outModel[i]->in[NIN[i]] = this->out[i];
			bool isOK = true;
			for (int j = 0; j < outModel[i]->nin; j++) {
				if (outModel[i]->in[j] == NULL)
					isOK = false;
			}
			if (isOK)
				outModel[i]->RUN(t, dt);
		}
		for (int i = 0; i < nin; i++)
			in[i] = NULL;
	};
};

void connect(MODEL* a, int na, MODEL* b, int nb) {
	a->outModel[na] = b;
	a->NIN[na] = nb;
}


class SIN :public MODEL {
public:
	SIN() {
		nin = 0;
		nout = 1;
		npar = 0;

		out = new double(nout);

		NIN = new int(nout);

		outModel = new MODEL *[nout];
		MODEL::MODEL();
	};
	void RUN(double t, double dt) {
		this->out[0] = sin(t);
		MODEL::RUN(t, dt);
	};
};

class COS :public MODEL {
public:
	COS() {
		nin = 0;
		nout = 1;
		npar = 0;

		out = new double(nout);

		NIN = new int(nout);

		outModel = new MODEL *[nout];
		MODEL::MODEL();
	};
	void RUN(double t, double dt) {
		this->out[0] = cos(t);
		MODEL::RUN(t, dt);
	};
};

class ADD :public MODEL {
public:
	ADD() {
		nin = 2;
		nout = 1;
		npar = 0;

		in = new double(nin);
		out = new double(nout);

		NIN = new int(nout);
		NOUT = new int(nin);

		outModel = new MODEL *[nout];
		inModel = new MODEL *[nin];
		MODEL::MODEL();
	};
	void RUN(double t, double dt) {
		this->out[0] = this->in[0] + this->in[1];
		MODEL::RUN(t, dt);
	};
};


class SINF :public MODEL {
public:
	SINF() {
		nin = 1;
		nout = 1;
		npar = 0;

		in = new double(nin);
		out = new double(nout);

		NIN = new int(nout);
		NOUT = new int(nin);

		outModel = new MODEL *[nout];
		inModel = new MODEL *[nin];
		MODEL::MODEL();
	};
	void RUN(double t, double dt) {
		this->out[0] = sin(this->in[0] * this->in[0]);
		MODEL::RUN(t, dt);
	};
};

class SINK :public MODEL {
public:
	ofstream outfile;
	SINK() {
		nin = 1;
		nout = 0;
		npar = 0;

		in = new double(nin);

		NOUT = new int(nin);

		inModel = new MODEL *[nin];
		outfile.open("out.out");
		MODEL::MODEL();
	};
	void RUN(double t, double dt) {
		outfile << t << "\t" << this->in[0] << endl;
		MODEL::RUN(t, dt);
	};
};
